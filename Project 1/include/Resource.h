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

        string getID() const;

        string getName() const;

        string getType() const;

        bool isAvailable() const;
        void setAvailable(bool isAvailable);

        void display() const;
};




#endif