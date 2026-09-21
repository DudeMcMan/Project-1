#include "C:/Users/crisp/Downloads/Project-1-Owen-s-branch/Project-1-Owen-s-branch/Project 1/include/ReservationManager.h"
#include "C:/Users/crisp/Downloads/Project-1-Owen-s-branch/Project-1-Owen-s-branch/Project 1/include/ResourceManager.h"

int main(){

    string resourceFile = "C:/Users/crisp/Downloads/Project-1-Owen-s-branch/Project-1-Owen-s-branch/Project 1/data/resources.txt";
    string reservationFile = "C:/Users/crisp/Downloads/Project-1-Owen-s-branch/Project-1-Owen-s-branch/Project 1/data/reservations.txt";
    
    ResourceManager resourceManager;

    resourceManager.loadResources(resourceFile);

    ReservationManager reservationManager(&resourceManager);

    reservationManager.loadReservations(reservationFile);

    cout << "===== Campus Resource Reservation System =====" << endl << endl;

    int choice;
    int id;

    while(choice != 9){
        cout << "1. View Resources" << endl;
        cout << "2. Create Reservation" << endl;
        cout << "3. Cancel Reservation" << endl;
        cout << "4. View Waiting Lists" << endl;
        cout << "5. Undo Cancellation" << endl;
        cout << "6. Search Reservations" << endl;
        cout << "7. Sort Resources" << endl;
        cout << "8. Generate Report" << endl;
        cout << "9. Exit" << endl;
        cout << endl << "Enter Choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                resourceManager.displayResources();
                break;
            case 2:
                reservationManager.createReservation();
                break;
            case 3:
                cout << "Enter reservation ID: ";
                cin >> id;
                reservationManager.cancelReservation(id);
                break;
            case 4:
                cout << "Not implemented" << endl;
                break;
            case 5:
                cout << "Not implemented" << endl;
                break;
            case 6:
                reservationManager.displayReservations();
                break;
            case 7:
                cout << "Not implemented" << endl;
                break;
            case 8:
                cout << "Not implemented" << endl;
                break;
            case 9:
                cout << "Exiting" << endl;
                break;
            default:
                cout << "Not an option" << endl;
        }
    }


    return 0;
}
