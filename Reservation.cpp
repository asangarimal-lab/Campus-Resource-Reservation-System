#include "Reservation.h"
#include <iostream>
using namespace std;

Reservation::Reservation() {
    reservationId = 0;
    studentId = 0;
    studentName = "";
    resourceId = "";
    date = "";
}

Reservation::Reservation(int reservationId, int studentId, string studentName,
                         string resourceId, string date) {
    this->reservationId = reservationId;
    this->studentId = studentId;
    this->studentName = studentName;
    this->resourceId = resourceId;
    this->date = date;
}

int Reservation::getReservationId() const {
    return reservationId;
}

int Reservation::getStudentId() const {
    return studentId;
}

string Reservation::getStudentName() const {
    return studentName;
}

string Reservation::getResourceId() const {
    return resourceId;
}

string Reservation::getDate() const {
    return date;
}

void Reservation::display() const {
    cout << "Reservation ID: " << reservationId
         << " | Student ID: " << studentId
         << " | Student: " << studentName
         << " | Resource ID: " << resourceId
         << " | Date: " << date << endl;
}
