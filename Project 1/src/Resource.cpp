#include "C:/Users/crisp/Downloads/Project-1-Owen-s-branch/Project-1-Owen-s-branch/Project 1/include/Resource.h"

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

bool Resource::isAvailable(){
    return available;
}
void Resource::setAvailable(bool isAvailable){
    available = isAvailable;
}

void Resource::display(){
    cout << id << "|" << name << "|" << type << "|";
    if(available == true){
        cout << "Available" << endl;
    }
    else{
        cout << "Unavailable" << endl;
    }
}