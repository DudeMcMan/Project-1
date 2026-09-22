#ifndef RESERVATION_LIST_H
#define RESERVATION_LIST_H

#include <iostream>
#include <string>
#include "Reservation.h"

using namespace std;

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
    bool removeReservation(int id, Reservation& removedReservation);
    void displayReservations() const;
    Reservation* findReservation(int id);
    const Reservation* findReservation(int id) const;
    bool isEmpty() const;
};

#endif
