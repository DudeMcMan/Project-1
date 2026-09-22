#ifndef WAITING_LIST_H
#define WAITING_LIST_H

#include <iostream>
#include <string>
using namespace std;

struct WaitingStudent {
    int studentID;
    string studentName;
    string resourceID;
    string date;

    WaitingStudent(int id, string name, string resID, string theDate)
        : studentID(id), studentName(name), resourceID(resID), date(theDate) {}
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
