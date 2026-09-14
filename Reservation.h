#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

// Reservation represents one active reservation in the system.
// It only stores reservation data; linked-list behavior belongs to ReservationManager.
class Reservation {
private:
    int reservationId;
    int studentId;
    std::string studentName;
    std::string resourceId;
    std::string date; // Expected format: MM/DD/YYYY

public:
    // Default constructor is useful when a Reservation object must be created
    // before data is loaded into it (for example, during cancellation).
    Reservation();

    // Main constructor used when creating a complete reservation.
    Reservation(int reservationId,
                int studentId,
                const std::string& studentName,
                const std::string& resourceId,
                const std::string& date);

    // Read-only accessors. The manager can inspect reservation data without
    // exposing private member variables directly.
    int getReservationId() const;
    int getStudentId() const;
    const std::string& getStudentName() const;
    const std::string& getResourceId() const;
    const std::string& getDate() const;

    // Displays one reservation in a readable format.
    void display() const;
};

#endif