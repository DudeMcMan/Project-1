#include "../include/ResourceManager.h"
#include "../include/ReservationList.h"
#include "../include/Reservation.h"
#include <cassert>
#include <fstream>
#include <iostream>

int main() {
    // --- Test merge sort via ResourceManager ---
    {
        std::ofstream out("test_resources_tmp.txt");
        out << "R2|Zebra Room|Study Room|Available\n";
        out << "R1|Alpha Room|Study Room|Available\n";
        out << "R3|Mid Room|Study Room|Available\n";
        out.close();

        ResourceManager rm;
        bool loaded = rm.loadResources("test_resources_tmp.txt");
        assert(loaded == true);

        rm.sortByName();

        const vector<Resource>& sorted = rm.getResources();
        assert(sorted.size() == 3);
        assert(sorted[0].getName() == "Alpha Room");
        assert(sorted[1].getName() == "Mid Room");
        assert(sorted[2].getName() == "Zebra Room");

        std::remove("test_resources_tmp.txt");
    }

    // --- Test ReservationList::countByResource ---
    {
        ReservationList list;
        list.insertReservation(Reservation(1, 1001, "Alice", "R101", "10/01/2026"));
        list.insertReservation(Reservation(2, 1002, "Bob", "R101", "10/02/2026"));
        list.insertReservation(Reservation(3, 1003, "Carla", "R102", "10/03/2026"));

        assert(list.countByResource("R101") == 2);
        assert(list.countByResource("R102") == 1);
        assert(list.countByResource("R999") == 0);
    }

    std::cout << "All sort and report tests passed." << std::endl;
    return 0;
}
