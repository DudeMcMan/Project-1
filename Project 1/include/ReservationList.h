#ifndef RESERVATION_LIST_H
#define RESERVATION_LIST_H

#include <iostream>
#include <string>
using namespace std;

struct Reservation {
    int reservationID;
    string studentID;
    string resourceID;
    string date;
    string startTime;
    string endTime;

    Reservation(int id, string student, string resource,
                string d, string start, string end)
        : reservationID(id),
          studentID(student),
          resourceID(resource),
          date(d),
          startTime(start),
          endTime(end) {}
};

struct ReservationNode {
    Reservation data;
    ReservationNode* next;

    ReservationNode(const Reservation& reservation)
        : data(reservation), next(nullptr) {}
};

class ReservationList {
private:
    ReservationNode* head;

public:
    ReservationList();
    ~ReservationList();

    void insertReservation(const Reservation& reservation);
    bool removeReservation(int reservationID);
    void displayReservations() const;
    bool findReservation(int reservationID) const;
    bool isEmpty() const;
};

#endif
