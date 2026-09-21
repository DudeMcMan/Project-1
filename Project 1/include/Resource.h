#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>
using namespace std;

class Resource{
    private:
        string id;
        string name;
        string type;
        bool available;

    public:
        Resource();
        Resource(string resourceID, string resourceName, string resourceType, bool isAvailable);

        string getID();

        string getName();

        string getType();

        bool isAvailable();
        void setAvailable(bool isAvailable);

        void display();
        void displayAvailability();
};




#endif