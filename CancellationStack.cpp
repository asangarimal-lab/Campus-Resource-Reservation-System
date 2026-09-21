#include "CancellationStack.h"
#include <iostream>
using namespace std;

// Starts with an empty stack
CancellationStack::CancellationStack() {
    top = nullptr;
}

// Deletes all remaining nodes when the stack is destroyed
CancellationStack::~CancellationStack() {
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

bool CancellationStack::isEmpty() const {
    return top == nullptr;
}

// Adds a cancelled reservation to the top of the stack
void CancellationStack::push(const Reservation& reservation) {
    Node* newNode = new Node;

    newNode->reservation = reservation;
    newNode->next = top;

    top = newNode;

    cout << "Reservation "
         << reservation.getReservationId()
         << " was added to cancellation history." << endl;
}

// Removes and returns the most recently cancelled reservation
Reservation CancellationStack::pop() {
    if (isEmpty()) {
        cout << "Cancellation history is empty." << endl;
        return Reservation();
    }

    Node* temp = top;

    Reservation reservationToRestore = top->reservation;

    top = top->next;

    delete temp;

    cout << "Reservation "
         << reservationToRestore.getReservationId()
         << " was removed from cancellation history." << endl;

    return reservationToRestore;
}

// Displays all cancelled reservations
void CancellationStack::displayHistory() const {
    if (isEmpty()) {
        cout << "Cancellation history is empty." << endl;
        return;
    }

    Node* current = top;

    cout << "\nCancellation History:" << endl;

    while (current != nullptr) {
        current->reservation.display();
        current = current->next;
    }
}
// Safe retrieval leaves the output unchanged when history is empty.
bool CancellationStack::peek(Reservation& reservation) const {
    if (isEmpty()) return false;
    reservation = top->reservation;
    return true;
}

bool CancellationStack::pop(Reservation& reservation) {
    if (!peek(reservation)) return false;
    Node* old = top;
    top = top->next;
    delete old;
    return true;
}
