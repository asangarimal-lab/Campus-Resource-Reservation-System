#include "Resource.h"
#include <iostream>
using namespace std;

Resource::Resource() {
    resourceId = "";
    name = "";
    type = "";
    status = "";
}

Resource::Resource(string resourceId, string name, string type, string status) {
    this->resourceId = resourceId;
    this->name = name;
    this->type = type;
    this->status = status;
}

string Resource::getResourceId() const {
    return resourceId;
}

string Resource::getName() const {
    return name;
}

string Resource::getType() const {
    return type;
}

string Resource::getStatus() const {
    return status;
}

void Resource::display() const {
    cout << "Resource ID: " << resourceId
         << " | Name: " << name
         << " | Type: " << type
         << " | Status: " << status << endl;
}
