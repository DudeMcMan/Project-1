#include "C:/Users/crisp/Downloads/Project-1-Owen-s-branch/Project-1-Owen-s-branch/Project 1/include/ReservationManager.h"

#include <iostream>
#include <fstream>
#include <sstream>


ReservationManager::ReservationManager(ResourceManager* manager){
    resourceManager = manager;
}

bool ReservationManager::loadReservations(string fileName){
    ifstream file(fileName);

    if(!file.is_open()){
        cout << "Error: Could not open file " << fileName << endl;
        return false;
    }

    string line;

    while(getline(file, line)){
        if(line.empty()){
            continue;
        }

        stringstream ss(line);

        string idString;
        string studentIdString;
        string studentName;
        string resourceId;
        string date;

        getline(ss, idString, '|');
        getline(ss, studentIdString, '|');
        getline(ss, studentName, '|');
        getline(ss, resourceId, '|');
        getline(ss, date);

        int id = stoi(idString);
        int studentId = stoi(studentIdString);

        if(findReservation(id) != nullptr){
            cout << "Warning: Duplicate reservation ID " << id << " skipped." << endl;
            continue;
        }
        Reservation newReservation(id, studentId, studentName, resourceId, date);
        reservations.push_back(newReservation);
    }

    file.close();

    return true;
}

bool ReservationManager::validateReservation(int reservationID, int studentID, string resourceID){
    // Check reservation ID
    if(reservationID <= 0){
        cout << "Error: Invalid reservation ID." << endl;

        return false;
    }

    // Check student ID
    if(studentID <= 0){
        cout << "Error: Invalid student ID." << endl;

        return false;
    }

    // Check for duplicate reservation ID
    for(Reservation reservation : reservations){
        if(reservation.getReservationID() == reservationID){
            cout << "Error: Reservation ID already exists." << endl;

            return false;
        }
    }

    // Check whether resource exists
    Resource* resource = resourceManager->searchByID(resourceID);

    if(resource == nullptr){
        cout << "Error: Resource ID does not exist." << endl;

        return false;
    }

    // Check whether resource is available
    if(!resource->isAvailable()){
        cout << "Error: Resource is unavailable." << endl;

        return false;
    }

    return true;
}

void ReservationManager::createReservation(){
    int id;
    int studentId;
    string studentName;
    string resourceId;
    string date;

    cout << endl << "===== Create Reservation =====" << endl;

    cout << "Student ID: ";
    cin >> studentId;

    cin.ignore();

    cout << "Student Name: ";
    getline(cin, studentName);

    cout << "Resource ID: ";
    cin >> resourceId;

    cout << "Registration Date: ";
    cin >> date;

    id = 321;

    for(Reservation reservation : reservations){
        if(reservation.getReservationID() == id){
            id++;
        }
    }

    if(!validateReservation(id, studentId, resourceId)){
        return;
    }

    Reservation newReservation(id, studentId, studentName, resourceId, date);

    reservations.push_back(newReservation);

    Resource* resource = resourceManager->searchByID(resourceId);

    resource->setAvailable(false);

    cout << endl << "reservation Created Successfully" << endl;

}

void ReservationManager::cancelReservation(int id){
    for(int i = 0; i < reservations.size(); i++){
        if(reservations[i].getReservationID() == id){
            string resourceId = reservations[i].getResourceID();

            Resource* resource = resourceManager->searchByID(resourceId);

            if(resource != nullptr){
                resource->setAvailable(true);
            }

            reservations.erase(reservations.begin() + i);

            cout << "Reservation Cancelled" << endl;

            return;
        }
    }

    cout << "Reservation not found" << endl;
}

void ReservationManager::displayReservations(){
    if (reservations.empty()){
        cout << "No active reservations." << endl;
        return;
    }

    cout << endl << "===== Active Reservations =====" << endl;

    for(int i = 0; i < reservations.size(); i++){
        reservations[i].display();
    }

    cout << "===============================" << endl;
}


Reservation* ReservationManager::findReservation(int reservationID){
    for(Reservation& reservation : reservations){
        if(reservation.getReservationID() == reservationID){
            return &reservation;
        }
    }

    return nullptr;
}