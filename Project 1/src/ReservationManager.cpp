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

        // if(findReservation(id) != nullptr && findReservation(id)->getDate() == date){
        //     // cout << "Warning: Duplicate reservation ID " << id << " skipped." << endl;
        //     WaitingStudent student (studentId, studentName, resourceId, date);
        //     waitingList.addStudent(student);
        //     continue;
        // }
        Reservation newReservation(id, studentId, studentName, resourceId, date);
        reservations.insertReservation(newReservation);

        Resource* temp = resourceManager->searchByID(newReservation.getResourceID());
        temp->bookDate(date);

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

    if(date.empty()){
        cout << "Error: Reservation date is required" << endl;
        return false;
    }

    // Check whether resource exists
    Resource* resource = resourceManager->searchByID(resourceID);

    if(resource == nullptr){
        cout << "Error: Resource ID does not exist." << endl;

        return false;
    }

    // Check whether resource is available
    if(!resource->isDateAvailable(date)){
        cout << "Resource is unavailable on " << date << endl;
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
    resource->bookDate(date);

    cout << endl << "Reservation Created Successfully" << endl << endl;

}

void ReservationManager::cancelReservation(int id){

    Reservation removedReservation;

    if(!reservations.removeReservation(id, removedReservation)){
        cout << "Reservation not found" << endl;

        return;
    }

    Resource* resource = resourceManager->searchByID(removedReservation.resourceId);

    if(resource != nullptr){
        resource->unbookDate(removedReservation.date);
    }

    cancellationHistory.push(removedReservation);

    cout << "Reservation " << id << " cancelled" << endl;

    WaitingStudent student(0, "", "", "");
    WaitingList tempQueue;
    bool assigned = false;

    while(waitingList.removeStudent(student)){
        if(!assigned && student.resourceID == removedReservation.resourceId && student.date == removedReservation.date){
            while(findReservation(nextReservationID) != nullptr){
                nextReservationID++;
            }

            Reservation promotedReservation(nextReservationID, student.studentID, student.studentName, student.resourceID, student.date);

            if(resource->bookDate(student.date)){
                reservations.insertReservation(promotedReservation);

                nextReservationID++;
                assigned = true;
            }
            else{
                tempQueue.addStudent(student);
            }
        }
        else{
            tempQueue.addStudent(student);
        }
    }

    while(tempQueue.removeStudent(student)){
        waitingList.addStudent(student);
    }
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

    if(!resource->isDateAvailable(reservation.getDate())){
        cout << "Cannot restore reservation: resource is currently unavailable on " << reservation.getDate() << endl;

        return;
    }

    cancellationHistory.pop(reservation);

    reservations.insertReservation(reservation);

    resource->bookDate(reservation.date);

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

void ReservationManager::searchByStudent(string name){
    vector<Reservation*> studentReservations = reservations.findReservationByName(name);

    if(studentReservations.empty()){
        cout << "Student " << name << " has no reservations" << endl;
        return;
    }

    cout << name << "'s Reservations: ";
    for(int i = 0; i < studentReservations.size(); i++){
        studentReservations[i]->display();
    }

}

void ReservationManager::report(){
    vector<Resource> resources = resourceManager->getResources();
    vector<Resource> temp = resources;
    vector<int> numRes;


    cout << "===== Resource Utilization ====" << endl;
    int amount;
    for(int i = 0; i < resources.size(); i++){
        amount = 0;
        cout << resources[i].getID() << "|" << resources[i].getName() << ": ";
        amount = resources[i].getBookings();
        cout << amount << " reservations" << endl;
    }
    cout << "===============================" << endl;


    vector<Reservation> allReservations = reservations.getAllReservations();

    vector<pair<string, int>> requestCounts;

    for(Resource resource : resources){
        int count = 0;

        for (Reservation reservation : allReservations) {
            if (reservation.resourceId == resource.getID()) {
                count++;
            }
        }

        requestCounts.push_back({resource.getID(), count});
    }

    for(int pass = 0; pass < requestCounts.size() - 1; pass++){
        bool swapped = false;

        for(int i = 0; i < requestCounts.size() - pass - 1; i++){
            if(requestCounts[i].second < requestCounts[i + 1].second){
                swap(requestCounts[i].second, requestCounts[i + 1].second);
                swapped = true;
            }
        }
        if(swapped == false){
            break;
        }
    }

    
    cout << "=== Most Requested Resources ==" << endl;
    // for(int i = 0; i < resources.size(); i++){
    //     numRes[i] = cancellationHistory.findResourceCount(resources[i].getID()) + reservations.findResourceCount(resources[i].getID()) + waitingList.findResourceCount(resources[i].getID());
    // }

    // for(int i = 0; i < resources.size(); i++){
    //     cout << temp[i].getID() << ": " << numRes[i] << " total requests" << endl;
    // }
    
    for(int i = 0; i < requestCounts.size(); i++){
        Resource* resource = resourceManager->searchByID(requestCounts[i].first);

        if(resource != nullptr){
            cout << (i + 1) << ". " << resource->getID() << "|" << resource->getName() << "|" << "Reservations: " << requestCounts[i].second << endl;
        }
    }

    cout << "===============================" << endl;
}