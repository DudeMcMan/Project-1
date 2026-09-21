#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include "ResourceManager.h"
#include "Reservation.h"

#include <string>
#include <queue>
#include <stack>

class ReservationManager{
    private:
        vector<Reservation> reservations;

        ResourceManager* resourceManager;

    public:
        // Constructor
        ReservationManager(ResourceManager* manager);

        bool loadReservations(string fileName);

        void createReservation();

        void cancelReservation(int id);

        void displayReservations();

        bool validateReservation(int id, int studentId, string resourceId);

        Reservation* findReservation(int id);
};




#endif