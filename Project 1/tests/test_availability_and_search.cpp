#include "../include/Resource.h"
#include "../include/ReservationList.h"
#include "../include/Reservation.h"
#include "../include/ResourceManager.h"
#include "../include/ReservationManager.h"
#include <cassert>
#include <fstream>
#include <iostream>

int main() {
    // --- Test Resource per-date availability ---
    {
        Resource r("R101", "Study Room 101", "Study Room", true);
        assert(r.isDateAvailable("10/15/2026") == true);
        assert(r.bookDate("10/15/2026") == true);
        assert(r.isDateAvailable("10/15/2026") == false);
        assert(r.bookDate("10/15/2026") == false);
        assert(r.isDateAvailable("10/16/2026") == true);
        assert(r.getBookings() == 1);
        assert(r.unbookDate("10/15/2026") == true);
        assert(r.isDateAvailable("10/15/2026") == true);
        assert(r.getBookings() == 0);
    }

    // --- Test ReservationList::findReservationByName ---
    {
        ReservationList list;
        list.insertReservation(Reservation(1, 1001, "Alice Test", "R101", "10/15/2026"));
        list.insertReservation(Reservation(2, 1002, "Bob Test", "R102", "10/16/2026"));
        list.insertReservation(Reservation(3, 1003, "Alice Test", "R103", "10/17/2026"));

        vector<Reservation*> aliceReservations = list.findReservationByName("Alice Test");
        assert(aliceReservations.size() == 2);

        vector<Reservation*> noneFound = list.findReservationByName("Nobody Here");
        assert(noneFound.empty());
    }


    // --- Integration test: cancellation promotes a waiting student ---
    {
        std::ofstream resOut("test_resources_avail_tmp.txt");
        resOut << "R201|Test Room|Study Room|Available\n";
        resOut.close();

        std::ofstream resvOut("test_reservations_avail_tmp.txt");
        resvOut << "321|2001|Carla Test|R201|11/01/2026\n";
        resvOut.close();

        ResourceManager rm;
        rm.loadResources("test_resources_avail_tmp.txt");

        ReservationManager resMgr(&rm);
        resMgr.loadReservations("test_reservations_avail_tmp.txt");

        Resource* resource = rm.searchByID("R201");
        assert(resource != nullptr);
        assert(resource->isDateAvailable("11/01/2026") == false);

        bool created2 = resMgr.validateReservation(2002, "Derek Test", "R201", "11/01/2026");
        assert(created2 == false);

        resMgr.cancelReservation(321);

        Reservation* promoted = resMgr.findReservation(322);
        assert(promoted != nullptr);
        assert(promoted->getName() == "Derek Test");
        assert(resource->isDateAvailable("11/01/2026") == false);

        std::remove("test_resources_avail_tmp.txt");
        std::remove("test_reservations_avail_tmp.txt");
    }

    std::cout << "All availability, search, and waiting-list promotion tests passed." << std::endl;
    return 0;
}
