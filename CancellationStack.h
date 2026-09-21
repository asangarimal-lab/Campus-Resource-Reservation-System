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
    CancellationStack(const CancellationStack&) = delete;
    CancellationStack& operator=(const CancellationStack&) = delete;

    bool isEmpty() const;

    void push(const Reservation& reservation);
    Reservation pop(); // Legacy interface: check isEmpty() first.
    bool pop(Reservation& reservation);
    bool peek(Reservation& reservation) const;
    void displayHistory() const;
};

#endif