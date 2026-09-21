#include "../include/ReservationList.h"

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

bool ReservationList::removeReservation(int id) {
    if (head == nullptr) {
        return false;
    }

    // Removing the first node
    if (head->data.id == id) {
        ReservationNode* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    ReservationNode* current = head;

    while (current->next != nullptr) {
        if (current->next->data.id == id) {
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
        cout << "Reservation ID: " << current->data.id << endl;
        cout << "Student ID: " << current->data.studentId << endl;
         cout << "Student Name: " << current->data.studentName << endl;
        cout << "Resource ID: " << current->data.resourceId << endl;
        cout << "Date: " << current->data.date << endl;
        cout << "-----------------------------\n";

        current = current->next;
    }
}

bool ReservationList::findReservation(int id) const {
    ReservationNode* current = head;

    while (current != nullptr) {
        if (current->data.id == id) {
            return true;
        }

        current = current->next;
    }

    return false;
}

bool ReservationList::isEmpty() const {
    return head == nullptr;
}
