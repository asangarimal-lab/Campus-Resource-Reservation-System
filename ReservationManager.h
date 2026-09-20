#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include "Reservation.h"
#include <cstddef>

// Stores active reservations in a custom singly linked list.
// std::list is not used because the assignment asks us to build the list ourselves.
class ReservationManager {
private:
    struct Node {
        Reservation data;
        Node* next;

        explicit Node(const Reservation& reservation)
            : data(reservation), next(nullptr) {
        }
    };

    Node* head; // first reservation in the list
    Node* tail; // last reservation, so we can insert at the end quickly
    std::size_t reservationCount;

    void insertNode(const Reservation& reservation);

public:
    ReservationManager();
    ~ReservationManager();

    ReservationManager(const ReservationManager&) = delete;
    ReservationManager& operator=(const ReservationManager&) = delete;

    // Linked list operations
    void insertReservation(const Reservation& reservation);
    bool removeReservation(int reservationId, Reservation& removedReservation);
    void displayActiveReservations() const;
    std::size_t getReservationCount() const;
    void clear();
};

#endif
