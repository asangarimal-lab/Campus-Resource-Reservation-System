# Group Contribution Report

Campus Resource Reservation System — Milestone 1

GitHub: https://github.com/asangarimal-lab/Campus-Resource-Reservation-System

## Team

- Person A: Obed Balderrama — Resource Management
- Person B: Asanga Rimal — Reservation Management and Linked List
- Person C: Anugrah Lama — Waiting List Queue and Cancellation History Stack

---

## Contribution Table

| Team Member | Component(s) | Specific Tasks Completed | Testing/Debugging | GitHub Contributions |
| --- | --- | --- | --- | --- |
| Obed Balderrama | Resource Management | Implement Resource and ResourceManager. Load resources.txt, store resources, display all resources, display/check availability, and handle invalid resource IDs/file input. Provide resourceExists and isResourceAvailable for ReservationManager. | Test resource file loading, display, availability checks, and invalid resource IDs. | Branch `feature/resource-management`. |
| Asanga Rimal | Reservation Management and Linked List | Implemented Reservation and ReservationManager. Built a custom singly linked list for active reservations. Implemented insert, remove, traverse, display, file loading, create, cancel, restore, duplicate-ID checks, date checks, and resource/date conflict checks. | Tested loading reservations.txt, valid insert, duplicate IDs, invalid dates, date conflicts, cancellation of missing IDs, traversal/display, and restore for undo integration. | Branch `feature/reservation-management`. Commits include Reservation class, custom linked list, reservation validation, cancellation, README, and complexity analysis. |
| Anugrah Lama | Waiting List Queue and Cancellation History Stack | Implemented a custom waiting-list queue with enqueue, dequeue, display, and empty-check operations. Implemented a custom cancellation-history stack with push, pop, display history, and empty-check operations. The queue follows FIFO order and the stack follows LIFO order. Wrote the complexity analysis for waiting-list processing and undo cancellation. | Tested enqueue/dequeue, FIFO behavior, empty queue, push/pop, LIFO behavior, empty stack, and restoring the most recently cancelled reservation. | Branch `feature/queue-stack`. Commits: `Add waiting list queue implementation`, `Add cancellation history stack implementation`, and `Add queue and stack documentation`. Opened Pull Request #2 into `main`. |

---

## Individual Paragraphs

**Obed Balderrama:** I implemented the Resource Management portion of the Campus Resource Reservation System. I created the Resource class to store resource records and the ResourceManager class to keep the inventory. Resources are loaded from resources.txt, stored, displayed, and checked for availability. Invalid resource IDs and file-open errors are handled in this module. I also provided resourceExists and isResourceAvailable so the reservation code can validate requests. My work is on the feature/resource-management GitHub branch.

**Asanga Rimal:** I implemented the Reservation Management portion of the Campus Resource Reservation System. I created the Reservation class to represent reservation records and the ReservationManager class to manage active reservations. Active reservations are stored using a custom singly linked list with head and tail pointers rather than std::list. I implemented insertion, removal, traversal, searching, display, reservation creation, cancellation, duplicate-ID prevention, date validation, and checks for conflicting reservations on the same resource and date. Cancelled reservations are returned so they can be stored on Person C's stack, and restoreReservation supports undo. I tested the reservation module with reservations.txt and wrote the Big-O analysis for reservation insertion and removal. My work is on the feature/reservation-management GitHub branch and was submitted through GitHub commits and a pull request.

**Anugrah Lama:** I implemented the waiting-list queue and cancellation-history stack. I created the queue using front and rear pointers and implemented enqueue, dequeue, display, and empty-check operations. The queue follows FIFO order so the first student added is the first student removed. I also created the cancellation-history stack using a top pointer and implemented push, pop, display history, and empty-check operations. The stack follows LIFO order so the most recently cancelled reservation is the first one available for restoration. I tested the queue and stack operations, including FIFO and LIFO behavior and empty queue/stack cases. I also wrote the complexity analysis for waiting-list processing and undo cancellation. My work was completed on the `feature/queue-stack` branch and submitted through GitHub commits and Pull Request #2.