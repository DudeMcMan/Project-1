#include "C:/Users/crisp/Downloads/Project-1-Owen-s-branch/Project-1-Owen-s-branch/Project 1/include/ResourceManager.h"


bool ResourceManager::loadResources(string fileName){
    ifstream file(fileName);

    if(!file.is_open()){
        cout << "Error: Could not open file " << fileName << endl;
        return false;
    }

    string line;

    while(getline(file, line)){
        // Skip empty lines
        if(line.empty()){
            continue;
        }

        stringstream ss(line);

        string id;
        string name;
        string type;
        string status;

        // Read each field separated by |
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, status, '|');

        bool available = (status == "Available");

        Resource resource(id, name, type, available);

        resources.push_back(resource);
    }

    file.close();

    return true;
}


// Displays all resources
void ResourceManager::displayResources(){
    if(resources.empty()){
        cout << "No resources found." << endl;
        return;
    }

    cout << endl << "========== Campus Resources ==========" << endl;

    for(int i = 0; i < resources.size(); i++){
        resources[i].display();
    }

    cout << "======================================" << endl;
}

void ResourceManager::displayAvailableResources(){
    cout << endl << "========== Available Resources ==========" << endl;

    bool found = false;

    for(int i = 0; i < resources.size(); i++){
        if(resources[i].isAvailable()){
            resources[i].display();
            found = true;
        }
    }

    if(!found){
        cout << "No resources are currently available." << endl;
    }

    cout << "=========================================" << endl;
}

Resource* ResourceManager::searchByID(string resourceID){
    for(int i = 0; i < resources.size(); i++){
        if(resources[i].getID() == resourceID){
            return &resources[i];
        }
    }

    return nullptr;
}