#include "ReportManager.h"
#include "MergeSort.h"
#include <iostream>
#include <iomanip>
using namespace std;

// compare functions for mergeSort

// most reservations first, ties go A to Z by name
bool morePopular(const ResourceStats& a, const ResourceStats& b) {
    if (a.reservations != b.reservations) {
        return a.reservations > b.reservations;
    }
    return a.name < b.name;
}

// most requests (reservations + waiting) first, ties go A to Z by name
bool moreRequested(const ResourceStats& a, const ResourceStats& b) {
    int totalA = a.reservations + a.waiting;
    int totalB = b.reservations + b.waiting;

    if (totalA != totalB) {
        return totalA > totalB;
    }
    return a.name < b.name;
}

ReportManager::ReportManager(ResourceManager& resources,
                             ReservationManager& reservations,
                             WaitingQueue& waitingList)
    : resources(resources), reservations(reservations),
      waitingList(waitingList) {
}

// fills the array with the numbers for every resource, returns how many
int ReportManager::buildStats(ResourceStats stats[]) {
    int count = resources.getResourceCount();
    if (count > MAX_STATS) {
        count = MAX_STATS;
    }

    for (int i = 0; i < count; i++) {
        Resource r = resources.getResource(i);

        stats[i].resourceId = r.getResourceId();
        stats[i].name = r.getName();
        stats[i].reservations =
            reservations.countReservationsForResource(r.getResourceId());
        stats[i].waiting = waitingList.countForResource(r.getResourceId());
    }

    return count;
}

// each resource with how many reservations it has
void ReportManager::showResourceUtilization() {
    ResourceStats stats[MAX_STATS];
    int count = buildStats(stats);

    if (count == 0) {
        cout << "No resources loaded." << endl;
        return;
    }

    int totalReservations = 0;
    for (int i = 0; i < count; i++) {
        totalReservations += stats[i].reservations;
    }

    cout << "\n----- Resource Utilization Report -----" << endl;
    cout << left << setw(8) << "ID"
         << setw(26) << "Name"
         << setw(14) << "Reservations"
         << "Share" << endl;

    for (int i = 0; i < count; i++) {
        // share of all reservations, avoid dividing by 0
        double share = 0.0;
        if (totalReservations > 0) {
            share = 100.0 * stats[i].reservations / totalReservations;
        }

        cout << left << setw(8) << stats[i].resourceId
             << setw(26) << stats[i].name
             << setw(14) << stats[i].reservations
             << fixed << setprecision(1) << share << "%" << endl;
    }

    cout << "Total reservations: " << totalReservations << endl;
}

// resources ranked by reservations + students waiting
void ReportManager::showMostRequested() {
    ResourceStats stats[MAX_STATS];
    int count = buildStats(stats);

    if (count == 0) {
        cout << "No resources loaded." << endl;
        return;
    }

    mergeSort(stats, count, moreRequested);

    cout << "\n----- Most Requested Resources -----" << endl;
    cout << left << setw(6) << "Rank"
         << setw(8) << "ID"
         << setw(26) << "Name"
         << setw(14) << "Reservations"
         << setw(9) << "Waiting"
         << "Total" << endl;

    for (int i = 0; i < count; i++) {
        cout << left << setw(6) << (i + 1)
             << setw(8) << stats[i].resourceId
             << setw(26) << stats[i].name
             << setw(14) << stats[i].reservations
             << setw(9) << stats[i].waiting
             << (stats[i].reservations + stats[i].waiting) << endl;
    }
}

// resources sorted by how many reservations they have
void ReportManager::showResourcesByPopularity() {
    ResourceStats stats[MAX_STATS];
    int count = buildStats(stats);

    if (count == 0) {
        cout << "No resources loaded." << endl;
        return;
    }

    mergeSort(stats, count, morePopular);

    cout << "\n----- Resources (sorted by popularity) -----" << endl;
    for (int i = 0; i < count; i++) {
        cout << stats[i].resourceId << " | " << stats[i].name
             << " | Reservations: " << stats[i].reservations << endl;
    }
}
