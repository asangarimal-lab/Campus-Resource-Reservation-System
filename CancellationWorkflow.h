#ifndef CANCELLATION_WORKFLOW_H
#define CANCELLATION_WORKFLOW_H

#include "CancellationStack.h"
#include "ReservationManager.h"
#include <string>

// Record history only when the reservation exists and cancellation succeeds.
bool cancelAndRecord(ReservationManager& manager, CancellationStack& history,
                     int reservationId, std::string& message);

// A rejected restoration leaves cancellation history unchanged.
bool undoCancellation(ReservationManager& manager, CancellationStack& history,
                      std::string& message);
#endif