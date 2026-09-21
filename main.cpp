#include "Resource.h"
#include "ResourceManager.h"
#include "Reservation.h"
#include "ReservationManager.h"
#include "WaitingQueue.h"
#include "CancellationStack.h"

#include <iostream>
#include <string>
using namespace std;

void showMenu() {
    cout << "\n===== Campus Resource Reservation System =====\n\n";
    cout << "1. Display all resources\n";
    cout << "2. Check resource availability\n";
    cout << "3. Display active reservations\n";
    cout << "4. Create a reservation\n";
    cout << "5. Cancel a reservation\n";
    cout << "6. Display waiting list\n";
    cout << "7. Undo last cancellation\n";
    cout << "8. Display cancellation history\n";
    cout << "9. Exit\n";
    cout << "Choice: ";
}

void clearBadInput() {
    cin.clear();
    cin.ignore(1000, '\n');
}

void checkAvailability(ResourceManager& resources) {
    string resourceId;
    string message;

    cout << "Resource ID: ";
    cin >> resourceId;

    if (!resources.displayAvailability(resourceId, message)) {
        cout << message << endl;
    }
}

void createReservation(ResourceManager& resources,
                       ReservationManager& reservations,
                       WaitingQueue& waitingList) {
    string resourceId;
    cout << "Resource ID: ";
    cin >> resourceId;

    if (!resources.resourceExists(resourceId)) {
        cout << "No resource with that ID.\n";
        return;
    }

    int studentId;
    string studentName;
    string date;

    cout << "Student ID: ";
    cin >> studentId;
    if (cin.fail()) {
        clearBadInput();
        cout << "Student ID has to be a number.\n";
        return;
    }
    cin.ignore();

    cout << "Student name: ";
    getline(cin, studentName);

    cout << "Date (MM/DD/YYYY): ";
    cin >> date;

    // If the resource is marked unavailable, or someone already has
    // that resource on this date, put the student on the waiting list.
    if (!resources.isResourceAvailable(resourceId) ||
        reservations.isResourceReservedOnDate(resourceId, date)) {
        cout << resourceId << " is not available for that date.\n";
        waitingList.enqueue(studentId, studentName, resourceId);
        return;
    }

    int newId = reservations.getNextReservationId();
    Reservation reservation(newId, studentId, studentName, resourceId, date);

    string errorMessage;
    if (reservations.createReservation(reservation, errorMessage)) {
        cout << "Reservation created. ID is " << newId << ".\n";
    }
    else {
        cout << errorMessage << endl;
    }
}

void cancelReservation(ReservationManager& reservations,
                       CancellationStack& history) {
    int reservationId;
    cout << "Reservation ID to cancel: ";
    cin >> reservationId;
    if (cin.fail()) {
        clearBadInput();
        cout << "Reservation ID has to be a number.\n";
        return;
    }

    Reservation cancelled;
    string message;
    if (reservations.cancelReservation(reservationId, cancelled, message)) {
        cout << message << endl;
        history.push(cancelled);
    }
    else {
        cout << message << endl;
    }
}

void undoCancellation(ReservationManager& reservations,
                      CancellationStack& history) {
    if (history.isEmpty()) {
        cout << "Nothing to undo.\n";
        return;
    }

    Reservation restored = history.pop();
    string errorMessage;
    if (reservations.restoreReservation(restored, errorMessage)) {
        cout << "Reservation " << restored.getReservationId()
             << " was put back on the active list.\n";
    }
    else {
        cout << "Couldn't restore that reservation: " << errorMessage << endl;
        // keep it on the stack if restore failed
        history.push(restored);
    }
}

int main() {
    ResourceManager resources;
    ReservationManager reservations;
    WaitingQueue waitingList;
    CancellationStack history;
    string errorMessage;

    if (!resources.loadFromFile("resources.txt", errorMessage)) {
        cout << errorMessage << endl;
    }
    if (!reservations.loadReservationsFromFile("reservations.txt", errorMessage)) {
        cout << errorMessage << endl;
    }

    int choice = 0;
    while (choice != 9) {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            clearBadInput();
            cout << "Enter a number from the menu.\n";
            continue;
        }

        switch (choice) {
            case 1:
                resources.displayAllResources();
                break;
            case 2:
                checkAvailability(resources);
                break;
            case 3:
                reservations.displayActiveReservations();
                break;
            case 4:
                createReservation(resources, reservations, waitingList);
                break;
            case 5:
                cancelReservation(reservations, history);
                break;
            case 6:
                waitingList.displayWaitingList();
                break;
            case 7:
                undoCancellation(reservations, history);
                break;
            case 8:
                history.displayHistory();
                break;
            case 9:
                cout << "Goodbye.\n";
                break;
            default:
                cout << "That's not a menu option.\n";
        }
    }

    return 0;
}
