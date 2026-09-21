#include "C:/Users/crisp/Downloads/Project-1-Owen-s-branch/Project-1-Owen-s-branch/Project 1/include/Reservation.h"

Reservation::Reservation(){
    id = 0;
    studentId = 0;
    studentName = "";
    resourceId = "";
    date = "";
}

Reservation::Reservation(int regID, int sID, string name, string resID, string reservationDate){
    id = regID;
    studentId = sID;
    studentName = name;
    resourceId = resID;
    date = reservationDate;
}

int Reservation::getReservationID(){
    return id;
}

int Reservation::getStudentID(){
    return studentId;
}

string Reservation::getName(){
    return studentName;
}

string Reservation::getResourceID(){
    return resourceId;
}

string Reservation::getDate(){
    return date;
}

void Reservation::display(){
    cout << id << "|" << studentId << "|" << studentName << "|" << resourceId << "|" << date << endl;
}