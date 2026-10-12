#include "Resource.h"
#include "ResourceManager.h"
#include "Reservation.h"
#include "ReservationManager.h"
#include "WaitingQueue.h"
#include "CancellationStack.h"
#include "ReportManager.h"

#include <iostream>
#include <string>
using namespace std;

void showMenu() {
    cout << "\n===== Campus Resource Reservation System =====\n\n";
    cout << "1. Display active reservations\n";
    cout << "2. Create a reservation\n";
    cout << "3. Cancel a reservation\n";
    cout << "4. Display waiting list (queue)\n";
    cout << "5. Undo last cancellation (stack)\n";
    cout << "6. Display cancellation history (stack)\n";
    cout << "7. Display all resources\n";
    cout << "8. Check resource availability\n";
    cout << "9. Search reservation by ID\n";
    cout << "10. Search reservations by student ID\n";
    cout << "11. Display reservations sorted by date\n";
    cout << "12. Reports\n";
    cout << "13. Display resources sorted by name\n";
    cout << "14. Display resources sorted by popularity\n";
    cout << "15. Exit\n";
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

    // Queue connection: if the resource is unavailable, or that
    // resource/date is already booked, the student goes on the waiting list.
    if (!resources.isResourceAvailable(resourceId) ||
        reservations.isResourceReservedOnDate(resourceId, date)) {
        cout << resourceId << " is not available for that date.\n";
        cout << "Adding the student to the waiting list queue.\n";
        waitingList.enqueue(studentId, studentName, resourceId, date);
        return;
    }

    int newId = reservations.getNextReservationId();

    Reservation reservation(
        newId, studentId, studentName, resourceId, date);

    string errorMessage;

    if (reservations.createReservation(reservation, errorMessage)) {
        cout << "Reservation created. ID is " << newId << ".\n";
    }
    else {
        cout << errorMessage << endl;
    }
}

void cancelReservation(ResourceManager& resources,
                       ReservationManager& reservations,
                       CancellationStack& history,
                       WaitingQueue& waitingList) {
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

        // Stack connection: cancelled record is pushed so undo can pop it.
        history.push(cancelled);

        WaitingRequest request;

        if (resources.isResourceAvailable(cancelled.getResourceId()) &&
            waitingList.peekForResource(cancelled.getResourceId(),
                                        cancelled.getDate(), request)) {
            int newId = reservations.getNextReservationId();

            Reservation reservation(
                newId, request.studentId, request.studentName,
                request.resourceId, request.date);

            // Keep the student's place if reservation creation fails.
            if (reservations.createReservation(reservation, message)) {
                waitingList.dequeueForResource(
                    request.resourceId, request.date, request);

                cout << "Reservation automatically assigned to "
                     << request.studentName
                     << ". ID is " << newId << ".\n";
            }
            else {
                cout << "Couldn't assign the waiting student: "
                     << message << endl;
            }
        }
    }
    else {
        cout << message << endl;
    }
}

void searchReservationById(
    const ReservationManager& reservations) {

    int reservationId;

    cout << "Reservation ID to search: ";
    cin >> reservationId;

    if (cin.fail()) {
        clearBadInput();
        cout << "Reservation ID has to be a number.\n";
        return;
    }

    const Reservation* result =
        reservations.findReservation(reservationId);

    if (result == NULL) {
        cout << "No reservation found with that ID.\n";
        return;
    }

    cout << "\nReservation found:\n";
    result->display();
}

void searchReservationsByStudent(
    const ReservationManager& reservations) {

    int studentId;

    cout << "Student ID to search: ";
    cin >> studentId;

    if (cin.fail()) {
        clearBadInput();
        cout << "Student ID has to be a number.\n";
        return;
    }

    reservations.searchReservationsByStudentId(studentId);
}

void showReportsMenu() {
    cout << "\n===== System Reports =====\n";
    cout << "1. Active reservations report\n";
    cout << "2. Resource utilization report\n";
    cout << "3. Most requested resources report\n";
    cout << "4. Waiting-list statistics\n";
    cout << "5. Return to main menu\n";
    cout << "Choice: ";
}

void runReportsMenu(ReportManager& reports,
                    ReservationManager& reservations) {
    int reportChoice = 0;

    while (reportChoice != 5) {
        showReportsMenu();
        cin >> reportChoice;

        if (cin.fail()) {
            clearBadInput();
            cout << "Please enter a valid number.\n";
            continue;
        }

        switch (reportChoice) {
            case 1:
                reservations.displayActiveReservationsReport();
                break;
            case 2:
                reports.showResourceUtilization();
                break;
            case 3:
                reports.showMostRequested();
                break;
            case 4:
                reports.showWaitingListStatistics();
                break;
            case 5:
                cout << "Returning to main menu.\n";
                break;
            default:
                cout << "Invalid report option.\n";
        }
    }
}

void undoCancellation(ReservationManager& reservations,
                      CancellationStack& history) {
    if (history.isEmpty()) {
        cout << "Cancellation stack is empty. Nothing to undo.\n";
        return;
    }

    Reservation restored = history.pop();
    string errorMessage;

    if (reservations.restoreReservation(restored, errorMessage)) {
        cout << "Reservation " << restored.getReservationId()
             << " was put back on the active list.\n";
    }
    else {
        cout << "Couldn't restore that reservation: "
             << errorMessage << endl;

        history.push(restored);
    }
}

int main() {
    ResourceManager resources;
    ReservationManager reservations;
    WaitingQueue waitingList;
    CancellationStack history;
    ReportManager reports(resources, reservations, waitingList);
    string errorMessage;

    if (!resources.loadFromFile("resources.txt", errorMessage)) {
        cout << errorMessage << endl;
    }

    if (!reservations.loadReservationsFromFile(
            "reservations.txt", errorMessage)) {
        cout << errorMessage << endl;
    }

    int choice = 0;

    while (choice != 15) {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            clearBadInput();
            cout << "Enter a number from the menu.\n";
            continue;
        }

        switch (choice) {
            case 1:
                reservations.displayActiveReservations();
                break;
            case 2:
                createReservation(resources, reservations, waitingList);
                break;
            case 3:
                cancelReservation(
                    resources, reservations, history, waitingList);
                break;
            case 4:
                waitingList.displayWaitingList();
                break;
            case 5:
                undoCancellation(reservations, history);
                break;
            case 6:
                history.displayHistory();
                break;
            case 7:
                resources.displayAllResources();
                break;
            case 8:
                checkAvailability(resources);
                break;
            case 9:
                searchReservationById(reservations);
                break;
            case 10:
                searchReservationsByStudent(reservations);
                break;
            case 11:
                reservations.displayReservationsSortedByDate();
                break;
            case 12:
                runReportsMenu(reports, reservations);
                break;
            // my merge sort, both sort a copy so the file order stays the same
            case 13:
                resources.displaySortedByName();
                break;
            case 14:
                reports.showResourcesByPopularity();
                break;
            case 15:
                cout << "Goodbye.\n";
                break;
            default:
                cout << "That's not a menu option.\n";
        }
    }

    return 0;
}