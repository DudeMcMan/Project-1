#include "../include/ReservationManager.h"
#include "../include/ResourceManager.h"

int main(){
    string resourceFile = "data/resources.txt";
    string reservationFile = "data/reservations.txt";
    ResourceManager resourceManager;
    resourceManager.loadResources(resourceFile);
    ReservationManager reservationManager(&resourceManager);
    reservationManager.loadReservations(reservationFile);
    cout << "===== Campus Resource Reservation System =====" << endl;
    int choice = 0;
    int id;
    while(choice != 9){
        cout << endl;
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
            case 1: resourceManager.displayResources(); break;
            case 2: reservationManager.createReservation(); break;
            case 3:
                cout << "Enter reservation ID: ";
                cin >> id;
                reservationManager.cancelReservation(id);
                break;
            case 4: reservationManager.displayWaitingList(); break;
            case 5: reservationManager.undoCancellation(); break;
            case 6: reservationManager.displayReservations(); break;
            case 7: resourceManager.sortByName(); break;
            case 8: {
                int reportChoice = 0;
                cout << "\n1. Active Reservations\n";
                cout << "2. Resource Utilization\n";
                cout << "3. Most Requested Resources\n";
                cout << "4. Waiting-List Statistics\n";
                cout << "5. Cancellation History\n";
                cout << "Select report: ";
                cin >> reportChoice;
                switch (reportChoice) {
                    case 1: reservationManager.displayActiveReservationsReport(); break;
                    case 2: reservationManager.displayResourceUtilizationReport(); break;
                    case 3: reservationManager.displayMostRequestedResourcesReport(); break;
                    case 4: reservationManager.displayWaitingListStatisticsReport(); break;
                    case 5: reservationManager.displayCancellationHistory(); break;
                    default: cout << "Not a valid report option" << endl;
                }
                break;
            }
            case 9: cout << "Exiting" << endl; break;
            default: cout << "Not an option" << endl;
        }
    }
    return 0;
}
