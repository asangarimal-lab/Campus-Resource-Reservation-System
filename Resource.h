#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
using namespace std;

// Holds the info for one resource
class Resource {
private:
    string resourceId;
    string name;
    string type;
    string status; // Available or Unavailable

public:
    Resource();
    Resource(string resourceId, string name, string type, string status);

    string getResourceId() const;
    string getName() const;
    string getType() const;
    string getStatus() const;

    void display() const;
};

#endif
