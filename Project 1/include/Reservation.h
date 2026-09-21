#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
using namespace std;

class Reservation{
    private:
        int id;
        int studentId;
        string studentName;
        string resourceId;
        string date;

    public:

    
    Reservation();
    Reservation(int regID, int sID, string name, string resID, string reservationDate);

    int getReservationID();

    int getStudentID();

    string getName();

    string getResourceID();

    string getDate();

    void display();

};





#endif