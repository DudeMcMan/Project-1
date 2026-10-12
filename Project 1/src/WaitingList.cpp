#include "../include/WaitingList.h"

WaitingList::WaitingList() {
    front = nullptr;
    rear = nullptr;
}

WaitingList::~WaitingList() {
    WaitingStudent student(0, "", "", "");

    while (!isEmpty()) {
        removeStudent(student);
    }
}

void WaitingList::addStudent(const WaitingStudent& student) {
    WaitingNode* newNode = new WaitingNode(student);

    // If queue is empty, front and rear point to new node
    if (rear == nullptr) {
        front = rear = newNode;
        return;
    }

    // Add new student to the rear
    rear->next = newNode;
    rear = newNode;
}

bool WaitingList::removeStudent(WaitingStudent& student) {
    if (front == nullptr) {
        return false;
    }

    // Save the student's information
    student = front->data;

    // Remove from the front
    WaitingNode* temp = front;
    front = front->next;

    // If queue becomes empty, update rear
    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    return true;
}

void WaitingList::displayWaitingList() const {
    if (front == nullptr) {
        cout << "Waiting list is empty.\n";
        return;
    }

    WaitingNode* current = front;

    cout << "\n===== Waiting List =====\n";

    int position = 1;

    while (current != nullptr) {
        cout << "Position: " << position << endl;
        cout << "Student ID: " << current->data.studentID << endl;
        cout << "Student Name: " << current->data.studentName << endl;
        cout << "Resource ID: " << current->data.resourceID << endl;
        cout << "Date: " << current->data.date << endl;
        cout << "-----------------------\n";

        current = current->next;
        position++;
    }
}

bool WaitingList::isEmpty() const {
    return front == nullptr;
}

void WaitingList::displayStatistics() const {
    if (front == nullptr) {
        cout << "Waiting list is empty.\n";
        cout << "Total students waiting: 0\n";
        return;
    }

    cout << "\n===== Waiting-List Statistics =====\n";
    int total = 0;
    for (const WaitingNode* current = front; current != nullptr; current = current->next) {
        ++total;
        bool alreadyCounted = false;
        for (const WaitingNode* prior = front; prior != current; prior = prior->next) {
            if (prior->data.resourceID == current->data.resourceID) {
                alreadyCounted = true;
                break;
            }
        }
        if (!alreadyCounted) {
            int resourceCount = 0;
            for (const WaitingNode* scan = current; scan != nullptr; scan = scan->next) {
                if (scan->data.resourceID == current->data.resourceID) ++resourceCount;
            }
            cout << "Resource " << current->data.resourceID << ": "
                 << resourceCount << " student(s) waiting\n";
        }
    }
    cout << "Total students waiting: " << total << "\n";
    cout << "===================================\n";
}
