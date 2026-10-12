#define main reservationSystemMain
#include "../main.cpp"
#undef main

#include <cassert>
#include <sstream>
#include <type_traits>

void cancelById(ResourceManager& resources, ReservationManager& manager,
                CancellationStack& history, WaitingQueue& queue, int id) {
    std::istringstream input(std::to_string(id) + "\n");
    std::streambuf* original = std::cin.rdbuf(input.rdbuf());

    cancelReservation(resources, manager, history, queue);

    std::cin.rdbuf(original);
    std::cin.clear();
}

void testQueue() {
    static_assert(
        !std::is_copy_constructible<WaitingQueue>::value,
        "Queue owns nodes");

    static_assert(
        !std::is_copy_assignable<WaitingQueue>::value,
        "Queue owns nodes");

    WaitingQueue queue;
    WaitingRequest request = {99, "Unchanged", "R999", "09/21/2026"};

    assert(queue.isEmpty());
    assert(queue.size() == 0);

    queue.dequeue();

    assert(!queue.dequeueForResource("R101", "09/21/2026", request));
    assert(!queue.peekForResource("R101", "09/21/2026", request));
    assert(request.studentId == 99);
    assert(request.studentName == "Unchanged");

    queue.enqueue(1, "Other date", "R101", "09/22/2026");
    queue.enqueue(2, "Other resource", "R103", "09/21/2026");
    queue.enqueue(3, "First", "R101", "09/21/2026");
    queue.enqueue(4, "Second", "R101", "09/21/2026");

    assert(queue.size() == 4);
    assert(queue.countForResource("R101") == 3);

    assert(!queue.dequeueForResource("R999", "09/21/2026", request));
    assert(!queue.dequeueForResource("R101", "09/23/2026", request));
    assert(queue.size() == 4);

    assert(queue.peekForResource("R101", "09/21/2026", request));
    assert(request.studentId == 3);
    assert(queue.size() == 4);

    assert(queue.dequeueForResource("R101", "09/21/2026", request));
    assert(request.studentId == 3);
    assert(request.studentName == "First");
    assert(request.resourceId == "R101");
    assert(request.date == "09/21/2026");
    assert(queue.size() == 3);

    assert(queue.dequeueForResource("R101", "09/21/2026", request));
    assert(request.studentId == 4);
    assert(queue.size() == 2);

    queue.enqueue(5, "New rear", "R103", "09/21/2026");
    queue.dequeue();

    assert(queue.size() == 2);
    assert(queue.countForResource("R101") == 0);

    assert(queue.dequeueForResource("R103", "09/21/2026", request));
    assert(request.studentId == 2);

    assert(queue.dequeueForResource("R103", "09/21/2026", request));
    assert(request.studentId == 5);
    assert(queue.isEmpty());

    queue.enqueue(6, "Reuse", "R101", "09/21/2026");
    assert(queue.size() == 1);

    queue.dequeue();
    assert(queue.isEmpty());
    assert(queue.size() == 0);

    std::ostringstream output;
    std::streambuf* original = std::cout.rdbuf(output.rdbuf());

    queue.displayWaitingList();
    queue.enqueue(1, "First", "R101", "09/21/2026");
    queue.displayWaitingList();

    std::cout.rdbuf(original);

    assert(output.str().find(
        "The waiting list is empty.") != std::string::npos);

    assert(output.str().find(
        "Date: 09/21/2026") != std::string::npos);
}

void testStackAndUndo(ResourceManager& resources) {
    Reservation first(301, 1, "First", "R101", "09/21/2026");
    Reservation second(302, 2, "Second", "R103", "09/21/2026");

    CancellationStack history;

    assert(history.isEmpty());
    assert(history.pop().getReservationId() == 0);

    history.push(first);
    history.push(second);

    assert(history.pop().getReservationId() == 302);
    assert(history.pop().getReservationId() == 301);
    assert(history.isEmpty());

    ReservationManager manager;
    WaitingQueue queue;
    std::string message;

    undoCancellation(manager, history);
    assert(manager.getReservationCount() == 0);

    assert(manager.createReservation(first, message));
    assert(manager.createReservation(second, message));

    cancelById(resources, manager, history, queue, 999);
    assert(history.isEmpty());
    assert(manager.getReservationCount() == 2);

    cancelById(resources, manager, history, queue, 301);
    cancelById(resources, manager, history, queue, 302);
    assert(manager.getReservationCount() == 0);

    undoCancellation(manager, history);

    assert(manager.findReservation(302) != nullptr);
    assert(manager.findReservation(301) == nullptr);

    Reservation conflict(303, 3, "Third", "R101", "09/21/2026");
    assert(manager.createReservation(conflict, message));

    undoCancellation(manager, history);

    assert(!history.isEmpty());
    assert(manager.findReservation(301) == nullptr);

    Reservation result;
    assert(manager.cancelReservation(303, result, message));

    undoCancellation(manager, history);

    assert(history.isEmpty());
    assert(manager.getReservationCount() == 2);

    cancelById(resources, manager, history, queue, 301);

    Reservation reusedId(301, 4, "Fourth", "R105", "09/22/2026");
    assert(manager.createReservation(reusedId, message));

    undoCancellation(manager, history);

    assert(!history.isEmpty());
    assert(manager.findReservation(301)->getStudentId() == 4);

    assert(manager.cancelReservation(301, result, message));

    undoCancellation(manager, history);

    assert(history.isEmpty());
    assert(manager.findReservation(301)->getStudentId() == 1);

    std::ostringstream output;
    std::streambuf* original = std::cout.rdbuf(output.rdbuf());

    history.displayHistory();
    history.push(first);
    history.displayHistory();

    std::cout.rdbuf(original);

    assert(output.str().find(
        "Cancellation history is empty.") != std::string::npos);

    assert(output.str().find(
        "Reservation ID: 301") != std::string::npos);
}

void testAssignment(ResourceManager& resources) {
    ReservationManager manager;
    CancellationStack history;
    WaitingQueue queue;
    std::string message;

    assert(manager.createReservation(
        Reservation(301, 1, "Original", "R101", "09/21/2026"),
        message));

    queue.enqueue(2, "Other date", "R101", "09/22/2026");
    queue.enqueue(3, "Other resource", "R103", "09/21/2026");
    queue.enqueue(4, "First eligible", "R101", "09/21/2026");
    queue.enqueue(5, "Second eligible", "R101", "09/21/2026");

    cancelById(resources, manager, history, queue, 999);

    assert(queue.size() == 4);
    assert(history.isEmpty());

    cancelById(resources, manager, history, queue, 301);

    const Reservation* assigned = manager.findReservation(302);

    assert(assigned != nullptr);
    assert(assigned->getStudentId() == 4);
    assert(assigned->getDate() == "09/21/2026");
    assert(assigned->getResourceId() == "R101");
    assert(queue.size() == 3);
    assert(manager.getReservationCount() == 1);

    undoCancellation(manager, history);

    assert(manager.findReservation(301) == nullptr);
    assert(!history.isEmpty());

    cancelById(resources, manager, history, queue, 302);
    assert(manager.findReservation(303)->getStudentId() == 5);

    cancelById(resources, manager, history, queue, 303);

    assert(queue.size() == 2);
    assert(manager.getReservationCount() == 0);

    WaitingRequest request;

    assert(queue.dequeueForResource("R101", "09/22/2026", request));
    assert(request.studentId == 2);

    assert(queue.dequeueForResource("R103", "09/21/2026", request));
    assert(request.studentId == 3);

    assert(manager.createReservation(
        Reservation(304, 1, "Original", "R101", "09/21/2026"),
        message));

    queue.enqueue(-1, "Invalid student", "R101", "09/21/2026");
    queue.enqueue(6, "Later student", "R101", "09/21/2026");

    cancelById(resources, manager, history, queue, 304);

    assert(manager.getReservationCount() == 0);
    assert(queue.size() == 2);

    assert(queue.dequeueForResource("R101", "09/21/2026", request));
    assert(request.studentId == -1);

    assert(queue.dequeueForResource("R101", "09/21/2026", request));
    assert(request.studentId == 6);

    assert(manager.createReservation(
        Reservation(305, 1, "Original", "R115", "09/21/2026"),
        message));

    queue.enqueue(7, "Unavailable resource", "R115", "09/21/2026");

    cancelById(resources, manager, history, queue, 305);

    assert(queue.size() == 1);
    assert(manager.getReservationCount() == 0);

    manager.insertReservation(
        Reservation(306, 1, "Duplicate one", "R101", "09/21/2026"));

    manager.insertReservation(
        Reservation(307, 2, "Duplicate two", "R101", "09/21/2026"));

    queue.enqueue(8, "Still waiting", "R101", "09/21/2026");

    cancelById(resources, manager, history, queue, 306);

    assert(queue.size() == 2);
    assert(manager.getReservationCount() == 1);
    assert(queue.peekForResource("R101", "09/21/2026", request));
    assert(request.studentId == 8);
}

void testCreateAndCancel(ResourceManager& resources) {
    ReservationManager manager;
    CancellationStack history;
    WaitingQueue queue;
    std::string message;

    assert(manager.createReservation(
        Reservation(301, 1, "Original", "R101", "09/21/2026"),
        message));

    std::istringstream input(
        "R101\n2\nWaiting Student\n09/21/2026\n");

    std::streambuf* original = std::cin.rdbuf(input.rdbuf());

    createReservation(resources, manager, queue);

    std::cin.rdbuf(original);
    std::cin.clear();

    WaitingRequest request;

    assert(queue.size() == 1);
    assert(queue.peekForResource("R101", "09/21/2026", request));
    assert(request.studentId == 2);
    assert(request.studentName == "Waiting Student");

    cancelById(resources, manager, history, queue, 301);

    assert(queue.isEmpty());
    assert(manager.findReservation(302)->getStudentId() == 2);
    assert(manager.findReservation(302)->getDate() == "09/21/2026");
}

void testReports(ResourceManager& resources) {
    ReservationManager manager;
    WaitingQueue queue;
    ReportManager reports(resources, manager, queue);

    std::ostringstream output;
    std::streambuf* original = std::cout.rdbuf(output.rdbuf());

    reports.showWaitingListStatistics();

    assert(output.str().find(
        "The waiting list is empty.") != std::string::npos);

    output.str("");

    queue.enqueue(1, "First", "R115", "09/21/2026");
    reports.showWaitingListStatistics();

    assert(output.str().find(
        "Longest waiting list: R115 (1 student)") != std::string::npos);

    output.str("");

    queue.enqueue(2, "Second", "R115", "09/22/2026");
    queue.enqueue(3, "Third", "R101", "09/21/2026");

    reports.showWaitingListStatistics();

    assert(output.str().find(
        "Longest waiting list: R115 (2 students)") != std::string::npos);

    output.str("");

    ResourceManager emptyResources;
    ReportManager emptyReports(emptyResources, manager, queue);

    emptyReports.showWaitingListStatistics();

    assert(output.str().find(
        "No resources loaded.") != std::string::npos);

    std::cout.rdbuf(original);
}

int main() {
    ResourceManager resources;
    std::string message;

    assert(resources.loadFromFile("resources.txt", message));

    testQueue();
    testStackAndUndo(resources);
    testAssignment(resources);
    testCreateAndCancel(resources);
    testReports(resources);

    std::cout
        << "All queue, stack, cancellation workflow, and report tests passed.\n";
}