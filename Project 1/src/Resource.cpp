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

bool Resource::isAvailable() const{
    return available;
}
void Resource::setAvailable(bool isAvailable){
    available = isAvailable;
}

void Resource::display() const{
    cout << id << "|" << name << "|" << type << "|";
    if(available == true){
        cout << "Available" << endl;
    }
    else{
        cout << "Unavailable" << endl;
    }
}