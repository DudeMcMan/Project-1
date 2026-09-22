#include "../include/ReservationManager.h"

#include <iostream>
#include <fstream>
#include <sstream>


ReservationManager::ReservationManager(ResourceManager* manager){
    resourceManager = manager;
    nextReservationID = 321;
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
        reservations.insertReservation(newReservation);
    }

    file.close();

    return true;
}

bool ReservationManager::validateReservation(int studentID, string studentName, string resourceID, string date){

    // Check student ID
    if(studentID <= 0){
        cout << "Error: Invalid student ID." << endl;

        return false;
    }

    // Check for duplicate reservation ID
    while(findReservation(nextReservationID) != nullptr){
        nextReservationID++;
    }

    // Check whether resource exists
    Resource* resource = resourceManager->searchByID(resourceID);

    if(resource == nullptr){
        cout << "Error: Resource ID does not exist." << endl;

        return false;
    }

    // Check whether resource is available
    if(!resource->isAvailable()){
        cout << "Resource is unavailable." << endl;
        WaitingStudent student (studentID, studentName, resourceID, date);
        waitingList.addStudent(student);
        cout << "Student added to waiting list" << endl;

        return false;
    }

    return true;
}

void ReservationManager::createReservation(){
    //int id;
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

    //id = 321;

    // for(Reservation reservation : reservations){
    //     if(reservation.getReservationID() == id){
    //         id++;
    //     }
    // }

    if(!validateReservation(studentId, studentName, resourceId, date)){
        return;
    }

    Reservation newReservation(nextReservationID, studentId, studentName, resourceId, date);

    reservations.insertReservation(newReservation);

    Resource* resource = resourceManager->searchByID(resourceId);

    resource->setAvailable(false);

    cout << endl << "Reservation Created Successfully" << endl << endl;

}

void ReservationManager::cancelReservation(int id){
    // for(int i = 0; i < reservations.size(); i++){
    //     if(reservations[i].getReservationID() == id){
    //         string resourceId = reservations[i].getResourceID();

    //         Resource* resource = resourceManager->searchByID(resourceId);

    //         if(resource != nullptr){
    //             resource->setAvailable(true);
    //         }

    //         reservations.erase(reservations.begin() + i);

    //         cout << "Reservation Cancelled" << endl;

    //         return;
    //     }
    // }

    // cout << "Reservation not found" << endl;

    Reservation removedReservation;

    if(!reservations.removeReservation(id, removedReservation)){
        cout << "Reservation not found" << endl;

        return;
    }

    Resource* resource = resourceManager->searchByID(removedReservation.resourceId);

    if(resource != nullptr){
        resource->setAvailable(true);
    }

    cancellationHistory.push(removedReservation);

    cout << "Reservation " << id << " cancelled" << endl;
}

void ReservationManager::undoCancellation(){
    Reservation reservation;

    if(!cancellationHistory.peek(reservation)){
        cout << "No cancellation to undo" << endl;

        return;
    }

    if(findReservation(reservation.getReservationID()) != nullptr){
        cout << "Cannot restore reservation: Reservation ID already exists" << endl;

        return;
    }

    Resource* resource = resourceManager->searchByID(reservation.resourceId);

    if(resource == nullptr){
        cout << "Cannot restore reservation: resource does not exist" << endl;

        return;
    }

    if(!resource->isAvailable()){
        cout << "Cannot restore reservation: resource is currently unavailable" << endl;

        return;
    }

    cancellationHistory.pop(reservation);

    reservations.insertReservation(reservation);

    resource->setAvailable(false);

    cout << "Reservation " << reservation.getReservationID() << " restored" << endl;
}

void ReservationManager::displayReservations(){

    cout << endl << "===== Active Reservations =====" << endl;

    reservations.displayReservations();

    cout << "===============================" << endl;
}

void ReservationManager::displayWaitingList() {
    waitingList.displayWaitingList();
}

void ReservationManager::displayCancellationHistory() {
    cancellationHistory.display();
}


Reservation* ReservationManager::findReservation(int reservationID){
    // for(Reservation& reservation : reservations){
    //     if(reservation.getReservationID() == reservationID){
    //         return &reservation;
    //     }
    // }

    // return nullptr;

    return reservations.findReservation(reservationID);
}