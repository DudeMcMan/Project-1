#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Resource.h"

class ResourceManager{
    private:
        vector<Resource> resources;

    public:
        bool loadResources(string fileName);

        void displayResources();

        Resource* searchByID(string resourceID);

        void sortByName();

        void displayAvailableResources(string date);

        const vector<Resource>& getResources() const;

};

#endif
