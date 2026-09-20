#include "ReservationList.h"

ReservationList::ReservationList() {
    head = nullptr;
}

ReservationList::~ReservationList() {
    ReservationNode* current = head;

    while (current != nullptr) {
        ReservationNode* next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;
}

void ReservationList::insertReservation(const Reservation& reservation) {
    ReservationNode* newNode = new ReservationNode(reservation);

    // Insert at the beginning of the linked list
    newNode->next = head;
    head = newNode;
}

bool ReservationList::removeReservation(int reservationID) {
    if (head == nullptr) {
        return false;
    }

    // Removing the first node
    if (head->data.reservationID == reservationID) {
        ReservationNode* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    ReservationNode* current = head;

    while (current->next != nullptr) {
        if (current->next->data.reservationID == reservationID) {
            ReservationNode* temp = current->next;
            current->next = temp->next;
            delete temp;
            return true;
        }

        current = current->next;
    }

    return false;
}

void ReservationList::displayReservations() const {
    if (head == nullptr) {
        cout << "No active reservations.\n";
        return;
    }

    ReservationNode* current = head;

    cout << "\n===== Active Reservations =====\n";

    while (current != nullptr) {
        cout << "Reservation ID: " << current->data.reservationID << endl;
        cout << "Student ID: " << current->data.studentID << endl;
        cout << "Resource ID: " << current->data.resourceID << endl;
        cout << "Date: " << current->data.date << endl;
        cout << "Time: " << current->data.startTime
             << " - " << current->data.endTime << endl;
        cout << "-----------------------------\n";

        current = current->next;
    }
}

bool ReservationList::findReservation(int reservationID) const {
    ReservationNode* current = head;

    while (current != nullptr) {
        if (current->data.reservationID == reservationID) {
            return true;
        }

        current = current->next;
    }

    return false;
}

bool ReservationList::isEmpty() const {
    return head == nullptr;
}
