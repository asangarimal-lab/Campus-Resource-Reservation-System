#include "CancellationWorkflow.h"

bool cancelAndRecord(ReservationManager& manager, CancellationStack& history,
                     int reservationId, std::string& message) {
    Reservation cancelled;
    if (!manager.cancelReservation(reservationId, cancelled, message)) {
        return false;
    }
    history.push(cancelled);
    return true;
}

bool undoCancellation(ReservationManager& manager, CancellationStack& history,
                      std::string& message) {
    Reservation cancelled;
    if (!history.peek(cancelled)) {
        message = "Cancellation history is empty.";
        return false;
    }
    if (!manager.restoreReservation(cancelled, message)) {
        return false;
    }
    history.pop(cancelled);
    message = "Reservation restored.";
    return true;
}