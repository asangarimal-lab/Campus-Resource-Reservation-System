#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include "Reservation.h"
#include <string>
using namespace std;

// Linked list of all active reservations
class ReservationManager {
private:
    struct Node {
        Reservation data;
        Node* next;
    };

    Node* head;
    Node* tail;
    int reservationCount;
    int nextId;

    void insertNode(Reservation reservation);
    bool checkFields(Reservation reservation, string& errorMessage);
    bool checkDate(string date);

public:
    ReservationManager();
    ~ReservationManager();

    bool loadFromFile(string fileName, string& errorMessage);
    bool createReservation(Reservation reservation, string& errorMessage);
    bool cancelReservation(int reservationId, Reservation& cancelled, string& message);

    // used when Person C undoes a cancel
    bool restoreReservation(Reservation reservation, string& errorMessage);

    bool reservationIdExists(int reservationId);
    bool isResourceReservedOnDate(string resourceId, string date);
    Reservation* findReservation(int reservationId);

    void insertReservation(Reservation reservation);
    bool removeReservation(int reservationId, Reservation& removed);
    void displayActiveReservations();
    int getReservationCount();
    int getNextReservationId();
    void clear();
};

#endif
