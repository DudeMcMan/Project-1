#include "../include/ResourceManager.h"


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

// Merge two sorted portions of the resources vector by resource name.
static void mergeResources(vector<Resource>& items, vector<Resource>& temp,
                           int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (items[i].getName() <= items[j].getName()) {
            temp[k++] = items[i++];
        } else {
            temp[k++] = items[j++];
        }
    }
    while (i <= mid) temp[k++] = items[i++];
    while (j <= right) temp[k++] = items[j++];
    for (int index = left; index <= right; ++index) items[index] = temp[index];
}

// Top-down merge sort; deliberately does not use std::sort.
static void mergeSortResources(vector<Resource>& items, vector<Resource>& temp,
                               int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortResources(items, temp, left, mid);
    mergeSortResources(items, temp, mid + 1, right);
    mergeResources(items, temp, left, mid, right);
}

void ResourceManager::sortByName() {
    if (resources.size() > 1) {
        vector<Resource> temp(resources.size());
        mergeSortResources(resources, temp, 0, static_cast<int>(resources.size()) - 1);
    }
    cout << "Resources sorted by name using Merge Sort.\n";
    displayResources();
}

const vector<Resource>& ResourceManager::getResources() const {
    return resources;
}
