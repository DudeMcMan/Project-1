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

        Reservation newReservation(id, studentId, studentName, resourceId, date);
        reservations.insertReservation(newReservation);

        Resource* temp = resourceManager->searchByID(newReservation.getResourceID());
        if(temp != nullptr){
            temp->bookDate(date);
        }
    }

    file.close();

    return true;
}

bool ReservationManager::validateReservation(int studentID, string studentName, string resourceID, string date){

    if(studentID <= 0){
        cout << "Error: Invalid student ID." << endl;
        return false;
    }

    while(findReservation(nextReservationID) != nullptr){
        nextReservationID++;
    }

    if(date.empty()){
        cout << "Error: Reservation date is required" << endl;
        return false;
    }

    Resource* resource = resourceManager->searchByID(resourceID);

    if(resource == nullptr){
        cout << "Error: Resource ID does not exist." << endl;
        return false;
    }

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

    if(!validateReservation(studentId, studentName, resourceId, date)){
        return;
    }

    Reservation newReservation(nextReservationID, studentId, studentName, resourceId, date);

    reservations.insertReservation(newReservation);

    Resource* resource = resourceManager->searchByID(resourceId);

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
        if(!assigned && resource != nullptr && student.resourceID == removedReservation.resourceId && student.date == removedReservation.date){
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
    return reservations.findReservation(reservationID);
}

void ReservationManager::searchByStudent(string name){
    vector<Reservation*> studentReservations = reservations.findReservationByName(name);

    if(studentReservations.empty()){
        cout << "Student " << name << " has no reservations" << endl;
        return;
    }

    cout << name << "'s Reservations:" << endl;
    for(int i = 0; i < studentReservations.size(); i++){
        studentReservations[i]->display();
    }
}

void ReservationManager::displayActiveReservationsReport() {
    cout << "\n========== Active Reservations Report ==========\n";
    reservations.displayReservations();
    cout << "=================================================\n";
}

void ReservationManager::displayResourceUtilizationReport() {
    cout << "\n========== Resource Utilization Report ==========\n";
    const vector<Resource>& allResources = resourceManager->getResources();
    if (allResources.empty()) {
        cout << "No resources loaded.\n";
    } else {
        for (const Resource& resource : allResources) {
            cout << resource.getID() << " | " << resource.getName()
                 << " | Reservations: " << reservations.countByResource(resource.getID()) << "\n";
        }
    }
    cout << "=================================================\n";
}

void ReservationManager::displayMostRequestedResourcesReport() {
    cout << "\n========== Most Requested Resources ==========\n";
    const vector<Resource>& allResources = resourceManager->getResources();
    if (allResources.empty()) {
        cout << "No resources loaded.\n";
        return;
    }

    vector<bool> printed(allResources.size(), false);
    for (size_t rank = 0; rank < allResources.size(); ++rank) {
        int bestIndex = -1;
        int bestCount = -1;
        for (size_t i = 0; i < allResources.size(); ++i) {
            if (printed[i]) continue;
            int count = reservations.countByResource(allResources[i].getID());
            if (count > bestCount) {
                bestCount = count;
                bestIndex = static_cast<int>(i);
            }
        }
        if (bestIndex >= 0) {
            printed[bestIndex] = true;
            cout << (rank + 1) << ". " << allResources[bestIndex].getName()
                 << " (" << allResources[bestIndex].getID() << ") - "
                 << bestCount << " reservation(s)\n";
        }
    }
    cout << "==============================================\n";
}

void ReservationManager::displayWaitingListStatisticsReport() {
    waitingList.displayStatistics();
}
