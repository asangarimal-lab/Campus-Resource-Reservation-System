#include "WaitingQueue.h"
#include "CancellationWorkflow.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <type_traits>

int main() {
    static_assert(!std::is_copy_constructible<WaitingQueue>::value, "Queue owns nodes");
    static_assert(!std::is_copy_assignable<WaitingQueue>::value, "Queue owns nodes");
    static_assert(!std::is_copy_constructible<CancellationStack>::value, "Stack owns nodes");
    static_assert(!std::is_copy_assignable<CancellationStack>::value, "Stack owns nodes");

    WaitingQueue queue;
    WaitingRequest request;
    request.studentId = 99;
    assert(queue.isEmpty());
    assert(!queue.dequeue(request) && request.studentId == 99);
    assert(!queue.peek(request));
    queue.enqueue(1, "First", "R101", "09/21/2026");
    queue.enqueue(2, "Second", "R102", "09/22/2026");
    assert(queue.peek(request) && request.studentId == 1);
    assert(queue.dequeue(request) && request.studentId == 1);
    assert(request.resourceId == "R101" && request.date == "09/21/2026");
    assert(queue.dequeue(request) && request.studentId == 2);
    assert(queue.isEmpty());
    queue.enqueue(3, "Third", "R103"); // Original API and reuse after emptying.
    assert(queue.dequeue(request) && request.studentId == 3);
    assert(request.date.empty() && queue.isEmpty());

    Reservation first(301, 1, "First", "R101", "09/21/2026");
    Reservation second(302, 2, "Second", "R102", "09/21/2026");
    Reservation result = first;
    CancellationStack history;
    assert(!history.pop(result) && result.getReservationId() == 301);
    assert(!history.peek(result));
    history.push(first);
    history.push(second);
    assert(history.peek(result) && result.getReservationId() == 302);
    assert(history.pop(result) && result.getReservationId() == 302);
    assert(history.pop(result) && result.getReservationId() == 301);
    assert(history.isEmpty());

    ReservationManager manager;
    std::string message;
    assert(!undoCancellation(manager, history, message));
    assert(manager.createReservation(first, message));
    assert(manager.createReservation(second, message));
    assert(!cancelAndRecord(manager, history, 999, message));
    assert(history.isEmpty() && manager.getReservationCount() == 2);
    assert(cancelAndRecord(manager, history, 301, message));
    assert(cancelAndRecord(manager, history, 302, message));
    assert(manager.getReservationCount() == 0);
    assert(undoCancellation(manager, history, message));
    assert(manager.findReservation(302) != nullptr);
    assert(manager.findReservation(301) == nullptr);

    Reservation conflict(303, 3, "Third", "R101", "09/21/2026");
    assert(manager.createReservation(conflict, message));
    assert(!undoCancellation(manager, history, message));
    assert(history.peek(result) && result.getReservationId() == 301);
    assert(manager.cancelReservation(303, result, message));
    assert(undoCancellation(manager, history, message));
    assert(history.isEmpty() && manager.getReservationCount() == 2);

    // A reused reservation ID must also preserve the undo entry.
    assert(cancelAndRecord(manager, history, 301, message));
    Reservation reusedId(301, 4, "Fourth", "R104", "09/22/2026");
    assert(manager.createReservation(reusedId, message));
    assert(!undoCancellation(manager, history, message));
    assert(history.peek(result) && result.getReservationId() == 301);
    assert(manager.cancelReservation(301, result, message));
    assert(undoCancellation(manager, history, message));

    std::ostringstream output;
    std::streambuf* original = std::cout.rdbuf(output.rdbuf());
    queue.displayWaitingList();
    history.displayHistory();
    queue.enqueue(1, "First", "R101", "09/21/2026");
    queue.displayWaitingList();
    history.push(first);
    history.displayHistory();
    std::cout.rdbuf(original);
    assert(output.str().find("The waiting list is empty.") != std::string::npos);
    assert(output.str().find("Cancellation history is empty.") != std::string::npos);
    assert(output.str().find("Date: 09/21/2026") != std::string::npos);
    assert(output.str().find("Reservation ID: 301") != std::string::npos);
    std::cout << "All queue, stack, and cancellation workflow tests passed.\n";
}