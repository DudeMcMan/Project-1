#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include "ResourceManager.h"
#include "Reservation.h"
#include "ReservationList.h"
#include "WaitingList.h"
#include "CancellationHistory.h"

#include <string>
#include <queue>
#include <stack>

class ReservationManager{
    private:
        ReservationList reservations;

        WaitingList waitingList;

        CancellationHistory cancellationHistory;

        ResourceManager* resourceManager;

        int nextReservationID;

    public:
        // Constructor
        ReservationManager(ResourceManager* manager);

        bool loadReservations(string fileName);

        void createReservation();

        void cancelReservation(int id);

        void displayReservations();
        
        void displayWaitingList();

        void displayCancellationHistory();

        void undoCancellation();

        bool validateReservation(int studentID, string studentName, string resourceID, string date);

        Reservation* findReservation(int id);
};




#endif