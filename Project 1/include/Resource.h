#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Resource{
    private:
        string id;
        string name;
        string type;
        bool available;

        vector<string> bookedDates;

    public:
        Resource();
        Resource(string resourceID, string resourceName, string resourceType, bool isAvailable);

        string getID();

        string getName();

        string getType();

        bool isDateAvailable(string date);

        //bool isAvailable();
        void setAvailable(bool isAvailable);

        bool bookDate(string date);
        bool unbookDate(string date);

        int getBookings();

        void display();
};




#endif