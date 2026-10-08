#ifndef REPORT_MANAGER_H
#define REPORT_MANAGER_H

#include "ResourceManager.h"
#include "ReservationManager.h"
#include "WaitingQueue.h"
#include <string>
using namespace std;

// numbers for one resource that the reports need
struct ResourceStats {
    string resourceId;
    string name;
    int reservations; // active reservations
    int waiting;      // students on the waiting list
};

// Builds the reports from the data the other managers already keep
class ReportManager {
private:
    static const int MAX_STATS = 100;

    // references so the reports always use the current data
    ResourceManager& resources;
    ReservationManager& reservations;
    WaitingQueue& waitingList;

    int buildStats(ResourceStats stats[]);

public:
    ReportManager(ResourceManager& resources,
                  ReservationManager& reservations,
                  WaitingQueue& waitingList);

    void showResourceUtilization();
    void showMostRequested();
    void showResourcesByPopularity();
};

#endif
