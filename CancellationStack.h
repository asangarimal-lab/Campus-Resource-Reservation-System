#ifndef CANCELLATIONSTACK_H
#define CANCELLATIONSTACK_H

#include "Reservation.h"

// Stack used to keep track of cancelled reservations
class CancellationStack {
private:
    struct Node {
        Reservation reservation;
        Node* next;
    };

    Node* top;

public:
    CancellationStack();
    ~CancellationStack();

    bool isEmpty() const;

    void push(const Reservation& reservation);
    Reservation pop();
    void displayHistory() const;
};

#endif