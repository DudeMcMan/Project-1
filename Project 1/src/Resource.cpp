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

string Resource::getID(){
    return id;
}

string Resource::getName(){
    return name;
}

string Resource::getType(){
    return type;
}

bool Resource::isDateAvailable(string date){
    return find(bookedDates.begin(), bookedDates.end(), date) == bookedDates.end();
}

// bool Resource::isAvailable(){
//     return available;
// }
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

void Resource::display(){
    cout << id << "|" << name << "|" << type<< "|";
    // if(available == true){
    //     cout << "Available" << endl;
    // }
    // else{
    //     cout << "Unavailable" << endl;
    // }
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

int Resource::getBookings(){
    return bookedDates.size();
}