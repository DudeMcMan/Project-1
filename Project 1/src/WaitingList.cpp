#include "../include/WaitingList.h"

WaitingList::WaitingList() {
    front = nullptr;
    rear = nullptr;
}

WaitingList::~WaitingList() {
    WaitingStudent student("", "");

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
        cout << "-----------------------\n";

        current = current->next;
        position++;
    }
}

bool WaitingList::isEmpty() const {
    return front == nullptr;
}
