#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Resource.h"
#include <string>
using namespace std;

// Keeps the list of all resources loaded from the file
class ResourceManager {
private:
    static const int MAX_RESOURCES = 100;
    Resource resources[MAX_RESOURCES];
    int resourceCount;

    int findIndex(string resourceId);

public:
    ResourceManager();

    bool loadFromFile(string fileName, string& errorMessage);
    void displayAllResources();
    bool displayAvailability(string resourceId, string& message);

    bool resourceExists(string resourceId);
    bool isResourceAvailable(string resourceId);

    int getResourceCount();
};

#endif
