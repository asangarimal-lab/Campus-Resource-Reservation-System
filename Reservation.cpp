#include "Reservation.h"
#include <iostream>

// Creates an empty/default reservation.
Reservation::Reservation()
    : reservationId(0), studentId(0), studentName(""), resourceId(""), date("") {
}

// Creates a reservation using all required fields.
Reservation::Reservation(int reservationId,
                         int studentId,
                         const std::string& studentName,
                         const std::string& resourceId,
                         const std::string& date)
    : reservationId(reservationId),
      studentId(studentId),
      studentName(studentName),
      resourceId(resourceId),
      date(date) {
}

int Reservation::getReservationId() const {
    return reservationId;
}

int Reservation::getStudentId() const {
    return studentId;
}

const std::string& Reservation::getStudentName() const {
    return studentName;
}

const std::string& Reservation::getResourceId() const {
    return resourceId;
}

const std::string& Reservation::getDate() const {
    return date;
}

// Displays the fields for one reservation.
void Reservation::display() const {
    std::cout << "Reservation ID: " << reservationId
              << " | Student ID: " << studentId
              << " | Student: " << studentName
              << " | Resource ID: " << resourceId
              << " | Date: " << date
              << '\n';
}