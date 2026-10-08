#include "ResourceManager.h"
#include "MergeSort.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

ResourceManager::ResourceManager() {
    resourceCount = 0;
}

// look through the array for this id, or -1 if not there
int ResourceManager::findIndex(string resourceId) {
    for (int i = 0; i < resourceCount; i++) {
        if (resources[i].getResourceId() == resourceId) {
            return i;
        }
    }
    return -1;
}

bool ResourceManager::loadFromFile(string fileName, string& errorMessage) {
    ifstream inFile(fileName.c_str());
    if (!inFile) {
        errorMessage = "Couldn't open " + fileName;
        return false;
    }

    resourceCount = 0;

    string line;
    while (getline(inFile, line)) {
        if (line == "") {
            continue;
        }
        if (resourceCount >= MAX_RESOURCES) {
            break;
        }

        // format: resourceId|name|type|status
        stringstream ss(line);
        string resourceId, name, type, status;

        getline(ss, resourceId, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, status, '|');

        Resource temp(resourceId, name, type, status);
        resources[resourceCount] = temp;
        resourceCount++;
    }

    inFile.close();
    return true;
}

void ResourceManager::displayAllResources() {
    if (resourceCount == 0) {
        cout << "No resources loaded." << endl;
        return;
    }

    cout << "----- Resources -----" << endl;
    for (int i = 0; i < resourceCount; i++) {
        resources[i].display();
    }
    cout << "Total: " << resourceCount << endl;
}

// compare function for mergeSort, A to Z by name
bool nameComesBefore(const Resource& a, const Resource& b) {
    return a.getName() < b.getName();
}

void ResourceManager::displaySortedByName() {
    if (resourceCount == 0) {
        cout << "No resources loaded." << endl;
        return;
    }

    // sort a copy so the original order from the file stays the same
    Resource sorted[MAX_RESOURCES];
    for (int i = 0; i < resourceCount; i++) {
        sorted[i] = resources[i];
    }

    mergeSort(sorted, resourceCount, nameComesBefore);

    cout << "----- Resources (sorted by name) -----" << endl;
    for (int i = 0; i < resourceCount; i++) {
        sorted[i].display();
    }
    cout << "Total: " << resourceCount << endl;
}

bool ResourceManager::displayAvailability(string resourceId, string& message) {
    int index = findIndex(resourceId);
    if (index == -1) {
        message = "No resource with that ID.";
        return false;
    }

    cout << resources[index].getResourceId() << " (" << resources[index].getName()
         << ") is " << resources[index].getStatus() << endl;
    return true;
}

bool ResourceManager::resourceExists(string resourceId) {
    return findIndex(resourceId) != -1;
}

bool ResourceManager::isResourceAvailable(string resourceId) {
    int index = findIndex(resourceId);
    if (index == -1) {
        return false;
    }
    return resources[index].getStatus() == "Available";
}

int ResourceManager::getResourceCount() {
    return resourceCount;
}

Resource ResourceManager::getResource(int index) {
    // bad index, just send back an empty resource
    if (index < 0 || index >= resourceCount) {
        return Resource();
    }
    return resources[index];
}
