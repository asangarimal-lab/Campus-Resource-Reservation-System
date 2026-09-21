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