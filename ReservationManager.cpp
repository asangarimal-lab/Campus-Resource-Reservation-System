#include "ReservationManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

ReservationManager::ReservationManager() {
    head = NULL;
    tail = NULL;
    reservationCount = 0;
    nextId = 301;
}

ReservationManager::~ReservationManager() {
    clear();
}

// add at the end of the list
void ReservationManager::insertNode(Reservation reservation) {
    Node* node = new Node;
    node->data = reservation;
    node->next = NULL;

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

void ReservationManager::insertReservation(Reservation reservation) {
    insertNode(reservation);
}

// find the node with this id and take it out
bool ReservationManager::removeReservation(int reservationId, Reservation& removed) {
    if (head == NULL) {
        return false;
    }

    Node* current = head;
    Node* previous = NULL;

    while (current != NULL && current->data.getReservationId() != reservationId) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return false; // not in the list
    }

    removed = current->data;

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

// pretty simple date check, just MM/DD/YYYY
bool ReservationManager::checkDate(string date) {
    if (date.length() != 10) {
        return false;
    }
    if (date[2] != '/' || date[5] != '/') {
        return false;
    }

    int month = (date[0] - '0') * 10 + (date[1] - '0');
    int day = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 +
               (date[8] - '0') * 10 + (date[9] - '0');

    if (month < 1 || month > 12) {
        return false;
    }
    if (day < 1 || day > 31) {
        return false;
    }
    if (year < 2020) {
        return false;
    }
    return true;
}

bool ReservationManager::checkFields(Reservation reservation, string& errorMessage) {
    if (reservation.getReservationId() <= 0) {
        errorMessage = "Reservation ID has to be positive.";
        return false;
    }
    if (reservation.getStudentId() <= 0) {
        errorMessage = "Student ID has to be positive.";
        return false;
    }
    if (reservation.getStudentName() == "") {
        errorMessage = "Need a student name.";
        return false;
    }
    if (reservation.getResourceId() == "") {
        errorMessage = "Need a resource ID.";
        return false;
    }
    if (!checkDate(reservation.getDate())) {
        errorMessage = "Date should look like MM/DD/YYYY.";
        return false;
    }
    return true;
}

bool ReservationManager::loadFromFile(string fileName, string& errorMessage) {
    ifstream inFile(fileName.c_str());
    if (!inFile) {
        errorMessage = "Couldn't open " + fileName;
        return false;
    }

    clear();

    string line;
    while (getline(inFile, line)) {
        if (line == "") {
            continue;
        }

        // format: id|studentId|name|resourceId|date
        stringstream ss(line);
        string idText, studentText, name, resourceId, date;

        getline(ss, idText, '|');
        getline(ss, studentText, '|');
        getline(ss, name, '|');
        getline(ss, resourceId, '|');
        getline(ss, date, '|');

        int reservationId;
        int studentId;
        stringstream(idText) >> reservationId;
        stringstream(studentText) >> studentId;

        Reservation temp(reservationId, studentId, name, resourceId, date);
        insertNode(temp);
    }

    inFile.close();
    return true;
}

bool ReservationManager::createReservation(Reservation reservation, string& errorMessage) {
    if (!checkFields(reservation, errorMessage)) {
        return false;
    }

    // no duplicate ids
    if (reservationIdExists(reservation.getReservationId())) {
        errorMessage = "That reservation ID is already used.";
        return false;
    }

    // same resource can't be booked twice on the same day
    if (isResourceReservedOnDate(reservation.getResourceId(), reservation.getDate())) {
        errorMessage = "That resource is already reserved on this date.";
        return false;
    }

    insertNode(reservation);
    return true;
}

bool ReservationManager::cancelReservation(int reservationId, Reservation& cancelled, string& message) {
    if (head == NULL) {
        message = "There are no reservations right now.";
        return false;
    }

    if (!removeReservation(reservationId, cancelled)) {
        message = "Couldn't find that reservation ID.";
        return false;
    }

    message = "Reservation cancelled.";
    return true;
}

bool ReservationManager::restoreReservation(Reservation reservation, string& errorMessage) {
    return createReservation(reservation, errorMessage);
}

bool ReservationManager::reservationIdExists(int reservationId) {
    if (findReservation(reservationId) == NULL) {
        return false;
    }
    return true;
}

bool ReservationManager::isResourceReservedOnDate(string resourceId, string date) {
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

Reservation* ReservationManager::findReservation(int reservationId) {
    Node* current = head;
    while (current != NULL) {
        if (current->data.getReservationId() == reservationId) {
            return &(current->data);
        }
        current = current->next;
    }
    return NULL;
}

void ReservationManager::displayActiveReservations() {
    if (head == NULL) {
        cout << "No active reservations." << endl;
        return;
    }

    cout << "----- Active Reservations -----" << endl;
    Node* current = head;
    while (current != NULL) {
        current->data.display();
        current = current->next;
    }
    cout << "Total: " << reservationCount << endl;
}

int ReservationManager::getReservationCount() {
    return reservationCount;
}

int ReservationManager::getNextReservationId() {
    return nextId;
}

void ReservationManager::clear() {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current->next;
        delete current;
        current = temp;
    }
    head = NULL;
    tail = NULL;
    reservationCount = 0;
}
