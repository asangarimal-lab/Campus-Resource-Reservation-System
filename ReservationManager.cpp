#include "ReservationManager.h"
#include <iostream>
using namespace std;

ReservationManager::ReservationManager()
    : head(NULL), tail(NULL), reservationCount(0) {
}

ReservationManager::~ReservationManager() {
    clear();
}

// Adds a reservation node at the end of the list.
void ReservationManager::insertNode(const Reservation& reservation) {
    Node* node = new Node(reservation);

    if (head == NULL) {
        head = node;
        tail = node;
    } else {
        tail->next = node;
        tail = node;
    }

    reservationCount++;
}

void ReservationManager::insertReservation(const Reservation& reservation) {
    insertNode(reservation);
}

// Walks the list, unlinks the matching node, and copies it out.
bool ReservationManager::removeReservation(int reservationId, Reservation& removedReservation) {
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
        return false;
    }

    removedReservation = current->data;

    if (previous == NULL) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    if (current == tail) {
        tail = previous;
    }

    delete current;
    reservationCount--;
    return true;
}

// Prints every active reservation from head to tail.
void ReservationManager::displayActiveReservations() const {
    if (head == NULL) {
        cout << "No active reservations." << endl;
        return;
    }

    cout << endl << "----- Active Reservations -----" << endl;
    Node* current = head;
    while (current != NULL) {
        current->data.display();
        current = current->next;
    }
    cout << "Total active reservations: " << reservationCount << endl;
}

size_t ReservationManager::getReservationCount() const {
    return reservationCount;
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
