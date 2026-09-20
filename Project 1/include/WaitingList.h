#ifndef WAITING_LIST_H
#define WAITING_LIST_H

#include <iostream>
#include <string>
using namespace std;

struct WaitingStudent {
    string studentID;
    string studentName;

    WaitingStudent(string id, string name)
        : studentID(id), studentName(name) {}
};

struct WaitingNode {
    WaitingStudent data;
    WaitingNode* next;

    WaitingNode(const WaitingStudent& student)
        : data(student), next(nullptr) {}
};

class WaitingList {
private:
    WaitingNode* front;
    WaitingNode* rear;

public:
    WaitingList();
    ~WaitingList();

    void addStudent(const WaitingStudent& student);
    bool removeStudent(WaitingStudent& student);
    void displayWaitingList() const;
    bool isEmpty() const;
};

#endif
