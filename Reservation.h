#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
using namespace std;

// Holds the info for one reservation
class Reservation {
private:
    int reservationId;
    int studentId;
    string studentName;
    string resourceId;
    string date; // MM/DD/YYYY

public:
    Reservation();
    Reservation(int reservationId, int studentId, string studentName,
                string resourceId, string date);

    int getReservationId() const;
    int getStudentId() const;
    string getStudentName() const;
    string getResourceId() const;
    string getDate() const;

    void display() const;
};

#endif
