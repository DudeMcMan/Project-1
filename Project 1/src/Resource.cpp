#include "../include/Resource.h"

Resource::Resource(){
    id = "";
    name = "";
    type = "";
    available = true;
}

Resource::Resource(string resourceID, string resourceName, string resourceType, bool isAvailable){
    id = resourceID;
    name = resourceName;
    type = resourceType;
    available = isAvailable;
}

string Resource::getID() const{
    return id;
}

string Resource::getName() const{
    return name;
}

string Resource::getType() const{
    return type;
}

bool Resource::isDateAvailable(string date) const{
    return find(bookedDates.begin(), bookedDates.end(), date) == bookedDates.end();
}

void Resource::setAvailable(bool isAvailable){
    available = isAvailable;
}

bool Resource::bookDate(string date){
    if (date.empty() || !isDateAvailable(date)){
        return false;
    }
    bookedDates.push_back(date);
    return true;
}

bool Resource::unbookDate(string date){
    auto it = find(bookedDates.begin(), bookedDates.end(), date);

    if(it == bookedDates.end()){
        return false;
    }

    bookedDates.erase(it);
    return true;
}

void Resource::display() const{
    cout << id << "|" << name << "|" << type << "|";
    if(bookedDates.empty()){
        cout << "Available" << endl;
    }
    else{
        cout << "Unavailable on ";
        for(int i = 0; i < bookedDates.size(); i++){
            cout << bookedDates[i];
            if(i != bookedDates.size()-1){
                cout << ", ";
            }
        }
        cout << endl;
    }
}

int Resource::getBookings() const{
    return bookedDates.size();
}
