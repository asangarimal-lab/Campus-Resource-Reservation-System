# Campus Resource Reservation System

GitHub repository:

https://github.com/asangarimal-lab/Campus-Resource-Reservation-System

This is a group project for Milestone 1. Students can reserve campus resources
such as study rooms, laptops, calculators, lab equipment, and tutoring times.

The system includes resource management, active reservations, waiting lists,
cancellation history, and reservation restoration.

## Team

| Person | Name | GitHub Branch | Responsibility |
| --- | --- | --- | --- |
| Person A | Obed Balderrama | `feature/resource-management` | Resource Management |
| Person B | Asanga Rimal | `feature/reservation-management` | Reservation Management and Linked List |
| Person C | Anugrah Lama | `feature/queue-stack` | Waiting List Queue and Cancellation History Stack |

## GitHub Workflow

Each team member works on their own feature branch.

- `feature/resource-management`
- `feature/reservation-management`
- `feature/queue-stack`

Each member commits their own work, pushes the feature branch to GitHub, and
opens a pull request into `main`.

## Reservation Management

`Reservation.h` and `Reservation.cpp` represent individual reservation records.

`ReservationManager.h` and `ReservationManager.cpp` manage active reservations.

Active reservations are stored using a custom singly linked list with head and
tail pointers.

Reservation management supports:

- Creating reservations
- Cancelling reservations
- Displaying active reservations
- Loading reservations from a file
- Duplicate reservation ID validation
- Date validation
- Resource/date conflict validation
- Restoring cancelled reservations

## Waiting List Queue

`WaitingQueue.h` and `WaitingQueue.cpp` implement the waiting list.

The queue uses front and rear pointers and supports:

- Enqueue
- Dequeue
- Display waiting list
- Empty queue checking

The waiting list follows FIFO (First In, First Out) order.

## Cancellation History Stack

`CancellationStack.h` and `CancellationStack.cpp` implement cancellation
history.

The stack supports:

- Push cancelled reservation
- Pop most recently cancelled reservation
- Display cancellation history
- Empty stack checking

The cancellation history follows LIFO (Last In, First Out) order.

When a reservation is cancelled, the cancelled Reservation object can be pushed
onto the cancellation stack.

To undo a cancellation, the most recently cancelled reservation is popped from
the stack and can be restored through ReservationManager.

## Resource Management Integration

Resource management is responsible for loading and storing campus resources,
displaying resources, and checking resource availability.

Before creating a reservation, the system should verify that the requested
resource exists and is available.

If a requested resource is unavailable, the student can be added to the waiting
list.

## File Formats

`resources.txt`

```text
resourceId|name|type|status
R101|Study Room 101|Study Room|Available
```

## Anugrah's queue and stack integration

The queue supports the original three-argument enqueue and an optional fourth
argument for the requested date. Use dequeue(WaitingRequest&) to retrieve a
request, or peek(WaitingRequest&) to inspect it without removal. Both return
false on an empty queue and leave the output unchanged. Entries remain FIFO.
Resource existence and availability checks belong to the calling resource module.

CancellationStack provides bool pop(Reservation&) and bool peek(Reservation&).
Both report empty history without returning a dummy reservation. The original
no-argument pop remains available for existing callers.

Include CancellationWorkflow.h to use cancelAndRecord(manager, history, id,
message) and undoCancellation(manager, history, message). Successful
cancellation records history; failed cancellation does not. Undo restores the
latest cancelled reservation through ReservationManager's validation. If the
resource/date or reservation ID conflicts, undo returns false and keeps history
so it can be retried. These helpers do not automatically promote waiting students.

### Run Anugrah's tests

With a C++ compiler installed, run from the repository directory:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic Reservation.cpp ReservationManager.cpp WaitingQueue.cpp CancellationStack.cpp CancellationWorkflow.cpp QueueStackTests.cpp -o queue_stack_tests.exe
.\queue_stack_tests.exe
```

QueueStackTests.cpp is a standalone test program, not the application menu.
When the team adds its application main, build that separately from this test.
Tests cover FIFO/LIFO, empty operations, reuse after emptying, displays,
successful cancellation/undo, missing IDs, and conflicts that preserve history.
