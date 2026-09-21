#include "C:/Users/crisp/Downloads/Project-1-Owen-s-branch/Project-1-Owen-s-branch/Project 1/include/ReservationManager.h"
#include "C:/Users/crisp/Downloads/Project-1-Owen-s-branch/Project-1-Owen-s-branch/Project 1/include/ResourceManager.h"

int main(){

    string resourceFile = "C:/Users/crisp/Downloads/Project-1-Owen-s-branch/Project-1-Owen-s-branch/Project 1/data/resources.txt";
    string reservationFile = "C:/Users/crisp/Downloads/Project-1-Owen-s-branch/Project-1-Owen-s-branch/Project 1/data/reservations.txt";
    
    ResourceManager resourceManager;

    resourceManager.loadResources(resourceFile);

    ReservationManager reservationManager(&resourceManager);

    reservationManager.loadReservations(reservationFile);

    cout << "===== Campus Resource Reservation System =====" << endl;


    return 0;
}