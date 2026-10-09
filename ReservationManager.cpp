#include "ReservationManager.h"
#include "MergeSort.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

ReservationManager::ReservationManager()
    : head(NULL), tail(NULL), reservationCount(0), nextId(301) {
}

ReservationManager::~ReservationManager() {
    clear();
}

void ReservationManager::insertNode(const Reservation& reservation) {
    Node* node = new Node(reservation);

    if (head == NULL) {
        head = node;
        tail = node;
    }
    else {
        tail->next = node;
        tail = node;
    }

    reservationCount++;

    if (reservation.getReservationId() >= nextId) {
        nextId = reservation.getReservationId() + 1;
    }
}

void ReservationManager::insertReservation(const Reservation& reservation) {
    insertNode(reservation);
}

bool ReservationManager::removeReservation(int reservationId,
                                           Reservation& removedReservation) {
    if (head == NULL) {
        return false;
    }

    Node* current = head;
    Node* previous = NULL;

    while (current != NULL &&
           current->data.getReservationId() != reservationId) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return false;
    }

    removedReservation = current->data;

    if (previous == NULL) {
        head = current->next;
    }
    else {
        previous->next = current->next;
    }

    if (current == tail) {
        tail = previous;
    }

    delete current;
    reservationCount--;

    return true;
}

bool ReservationManager::isValidDate(const string& date) const {
    // Expected format: MM/DD/YYYY
    if (date.length() != 10) {
        return false;
    }

    if (date[2] != '/' || date[5] != '/') {
        return false;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            continue;
        }

        if (date[i] < '0' || date[i] > '9') {
            return false;
        }
    }

    int month = (date[0] - '0') * 10 + (date[1] - '0');
    int day = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 +
               (date[7] - '0') * 100 +
               (date[8] - '0') * 10 +
               (date[9] - '0');

    if (year < 2020 || year > 2100) {
        return false;
    }

    if (month < 1 || month > 12) {
        return false;
    }

    int daysInMonth[] = {
        0, 31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    bool leap =
        (year % 4 == 0 && year % 100 != 0) ||
        (year % 400 == 0);

    if (leap) {
        daysInMonth[2] = 29;
    }

    if (day < 1 || day > daysInMonth[month]) {
        return false;
    }

    return true;
}

bool ReservationManager::validateBasicFields(
    const Reservation& reservation,
    string& errorMessage) const {

    if (reservation.getReservationId() <= 0) {
        errorMessage = "Reservation ID must be a positive number.";
        return false;
    }

    if (reservation.getStudentId() <= 0) {
        errorMessage = "Student ID must be a positive number.";
        return false;
    }

    if (reservation.getStudentName().empty()) {
        errorMessage = "Student name cannot be empty.";
        return false;
    }

    if (reservation.getResourceId().empty()) {
        errorMessage = "Resource ID cannot be empty.";
        return false;
    }

    if (!isValidDate(reservation.getDate())) {
        errorMessage = "Date must be a real date in MM/DD/YYYY format.";
        return false;
    }

    return true;
}

bool ReservationManager::loadReservationsFromFile(
    const string& fileName,
    string& errorMessage) {

    ifstream inFile(fileName.c_str());

    if (!inFile.is_open()) {
        errorMessage = "Could not open reservation file: " + fileName;
        return false;
    }

    clear();

    string line;
    int lineNumber = 0;

    while (getline(inFile, line)) {
        lineNumber++;

        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string idText;
        string studentIdText;
        string name;
        string resourceId;
        string date;

        if (!getline(ss, idText, '|') ||
            !getline(ss, studentIdText, '|') ||
            !getline(ss, name, '|') ||
            !getline(ss, resourceId, '|') ||
            !getline(ss, date, '|')) {

            cout << "Skipping bad reservation line "
                 << lineNumber << endl;
            continue;
        }

        int reservationId = 0;
        int studentId = 0;

        stringstream idStream(idText);
        stringstream studentStream(studentIdText);

        idStream >> reservationId;
        studentStream >> studentId;

        insertNode(
            Reservation(
                reservationId,
                studentId,
                name,
                resourceId,
                date
            )
        );
    }

    inFile.close();
    return true;
}

bool ReservationManager::createReservation(
    const Reservation& reservation,
    string& errorMessage) {

    if (!validateBasicFields(reservation, errorMessage)) {
        return false;
    }

    if (reservationIdExists(reservation.getReservationId())) {
        errorMessage = "That reservation ID is already in use.";
        return false;
    }

    if (isResourceReservedOnDate(
            reservation.getResourceId(),
            reservation.getDate())) {

        errorMessage =
            "That resource is already reserved on this date.";
        return false;
    }

    insertNode(reservation);
    return true;
}

bool ReservationManager::cancelReservation(
    int reservationId,
    Reservation& cancelledReservation,
    string& message) {

    if (head == NULL) {
        message = "There are no active reservations.";
        return false;
    }

    if (!removeReservation(
            reservationId,
            cancelledReservation)) {

        message = "No reservation found with that ID.";
        return false;
    }

    message = "Reservation cancelled.";
    return true;
}

bool ReservationManager::restoreReservation(
    const Reservation& reservation,
    string& errorMessage) {

    return createReservation(reservation, errorMessage);
}

bool ReservationManager::reservationIdExists(
    int reservationId) const {

    return findReservation(reservationId) != NULL;
}

bool ReservationManager::isResourceReservedOnDate(
    const string& resourceId,
    const string& date) const {

    Node* current = head;

    while (current != NULL) {
        if (current->data.getResourceId() == resourceId &&
            current->data.getDate() == date) {
            return true;
        }

        current = current->next;
    }

    return false;
}

const Reservation* ReservationManager::findReservation(
    int reservationId) const {

    Node* current = head;

    // LINEAR SEARCH:
    // Start at the first node and examine each reservation
    // one at a time until the requested ID is found.
    while (current != NULL) {
        if (current->data.getReservationId() == reservationId) {
            return &(current->data);
        }

        current = current->next;
    }

    // We reached the end of the linked list without a match.
    return NULL;
}

void ReservationManager::searchReservationsByStudentId(
    int studentId) const {

    Node* current = head;
    bool found = false;

    cout << "\n----- Reservations for Student "
         << studentId << " -----\n";

    // LINEAR SEARCH:
    // Every reservation is examined because one student
    // may have more than one active reservation.
    while (current != NULL) {

        if (current->data.getStudentId() == studentId) {
            current->data.display();
            found = true;
        }

        current = current->next;
    }

    if (!found) {
        cout << "No active reservations found for this student."
             << endl;
    }
}

// walk the whole list and count the ones for this resource
int ReservationManager::countReservationsForResource(
    const string& resourceId) const {

    int count = 0;
    Node* current = head;

    while (current != NULL) {
        if (current->data.getResourceId() == resourceId) {
            count++;
        }

        current = current->next;
    }

    return count;
}

void ReservationManager::displayActiveReservations() const {
    if (head == NULL) {
        cout << "No active reservations." << endl;
        return;
    }

    cout << endl
         << "----- Active Reservations -----"
         << endl;

    Node* current = head;

    while (current != NULL) {
        current->data.display();
        current = current->next;
    }

    cout << "Total active reservations: "
         << reservationCount << endl;
}

// Turn MM/DD/YYYY into YYYYMMDD so 09/15/2026 comes before 10/01/2026.
int reservationDateKey(const string& date) {
    if (date.length() != 10) {
        return 0;
    }

    int month = (date[0] - '0') * 10 + (date[1] - '0');
    int day = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 +
               (date[7] - '0') * 100 +
               (date[8] - '0') * 10 +
               (date[9] - '0');

    return year * 10000 + month * 100 + day;
}

bool reservationDateComesBefore(const Reservation& a, const Reservation& b) {
    return reservationDateKey(a.getDate()) < reservationDateKey(b.getDate());
}

void ReservationManager::displayReservationsSortedByDate() const {
    if (head == NULL) {
        cout << "No active reservations." << endl;
        return;
    }

    int n = static_cast<int>(reservationCount);
    Reservation* sorted = new Reservation[n];

    Node* current = head;
    int index = 0;
    while (current != NULL) {
        sorted[index] = current->data;
        index++;
        current = current->next;
    }

    // MERGE SORT (MergeSort.h):
    // Same algorithm Sebastian uses for resources. We only supply
    // the "comes before" function for reservation dates.
    mergeSort(sorted, n, reservationDateComesBefore);

    cout << "\n----- Reservations sorted by date -----\n";
    for (int i = 0; i < n; i++) {
        sorted[i].display();
    }
    cout << "Total active reservations: " << n << endl;

    delete[] sorted;
}

size_t ReservationManager::getReservationCount() const {
    return reservationCount;
}

int ReservationManager::getNextReservationId() const {
    return nextId;
}

void ReservationManager::clear() {
    Node* current = head;

    while (current != NULL) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = NULL;
    tail = NULL;
    reservationCount = 0;
}