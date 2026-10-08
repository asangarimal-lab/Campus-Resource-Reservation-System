#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include "Reservation.h"
#include <cstddef>
#include <string>

// Manages active reservations with a custom singly linked list.
class ReservationManager {
private:
    struct Node {
        Reservation data;
        Node* next;

        explicit Node(const Reservation& reservation)
            : data(reservation), next(nullptr) {
        }
    };

    Node* head;
    Node* tail;
    std::size_t reservationCount;
    int nextId;

    void insertNode(const Reservation& reservation);
    bool validateBasicFields(const Reservation& reservation,
                             std::string& errorMessage) const;
    bool isValidDate(const std::string& date) const;

public:
    ReservationManager();
    ~ReservationManager();

    ReservationManager(const ReservationManager&) = delete;
    ReservationManager& operator=(const ReservationManager&) = delete;

    // Loads seed data:
    // reservationId|studentId|studentName|resourceId|MM/DD/YYYY
    bool loadReservationsFromFile(const std::string& fileName,
                                  std::string& errorMessage);

    // Checks IDs, date format, duplicate reservation IDs, and date conflicts.
    bool createReservation(const Reservation& reservation,
                           std::string& errorMessage);

    // Removes the reservation from the linked list.
    // The cancelled record can be pushed onto the cancellation stack.
    bool cancelReservation(int reservationId,
                           Reservation& cancelledReservation,
                           std::string& message);

    // Restores a cancelled reservation for undo.
    bool restoreReservation(const Reservation& reservation,
                            std::string& errorMessage);

    bool reservationIdExists(int reservationId) const;

    bool isResourceReservedOnDate(const std::string& resourceId,
                                  const std::string& date) const;

    // Performs a manual linear search through the linked list
    // to locate a reservation by reservation ID.
    //
    // Best case: O(1)
    // Worst case: O(n)
    const Reservation* findReservation(int reservationId) const;

    // Performs a linear search through the active reservation list
    // and displays all reservations belonging to one student.
    void searchReservationsByStudentId(int studentId) const;

    void insertReservation(const Reservation& reservation);

    bool removeReservation(int reservationId,
                           Reservation& removedReservation);

    void displayActiveReservations() const;

    std::size_t getReservationCount() const;
    int getNextReservationId() const;

    void clear();
};

#endif