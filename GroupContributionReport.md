# Group Contribution Report

Campus Resource Reservation System — Milestone 1

GitHub: https://github.com/asangarimal-lab/Campus-Resource-Reservation-System

## Team

- Person A: Obed Balderrama — Resource Management
- Person B: Asanga Rimal — Reservation Management and Linked List
- Person C: Anugrah Lama — Waiting List Queue and Cancellation History Stack

---

## Contribution table

| Team Member | Component(s) | Specific Tasks Completed | Testing/Debugging | GitHub Contributions |
| --- | --- | --- | --- | --- |
| Obed Balderrama | Resource Management | Implement Resource and ResourceManager. Load resources.txt, store resources, display all resources, display/check availability, and handle invalid resource IDs / file input. Provide resourceExists and isResourceAvailable for ReservationManager. | Test resource file loading, display, availability checks, and bad resource IDs. | Branch `feature/resource-management`. Add commits and a pull request into main when finished. |
| Asanga Rimal | Reservation Management and Linked List | Implemented Reservation and ReservationManager. Built a custom singly linked list for active reservations. Implemented insert, remove, traverse, display, file loading, create, cancel, restore, duplicate-ID checks, date checks, and resource/date conflict checks. | Tested loading reservations.txt, valid insert, duplicate IDs, bad dates, date conflicts, cancellation of missing IDs, traversal/display, and restore for undo integration. | Created `feature/reservation-management`. Commits: Implement Reservation class; Add custom linked list for active reservations; Add reservation validation and cancellation; README and complexity analysis. Pull request into main. |
| Anugrah Lama | Queue and Stack | Implemented a custom waiting-list queue with enqueue, dequeue, display, and empty-check operations. Implemented a custom cancellation-history stack with push, pop, display history, and empty-check operations. The queue follows FIFO order and the stack follows LIFO order. Wrote the complexity analysis for waiting-list processing and undo cancellation. | Tested enqueue/dequeue, FIFO behavior, empty queue, push/pop, LIFO behavior, empty stack, and restoring the most recently cancelled reservation. | Branch `feature/queue-stack`. Implemented and tested the waiting-list queue and cancellation-history stack. Commits and pull request will be added after pushing the branch.  |


---

## Individual paragraphs

**Obed Balderrama:** I implemented the Resource Management portion of the Campus Resource Reservation System. I created the Resource class to store resource records and the ResourceManager class to keep the inventory. Resources are loaded from resources.txt, stored, displayed, and checked for availability. Invalid resource IDs and file-open errors are handled in this module. I also provided resourceExists and isResourceAvailable so the reservation code can validate requests. My work is on the feature/resource-management GitHub branch.

*(Obed: edit this paragraph so it matches what you actually coded and tested.)*

**Asanga Rimal:** I implemented the Reservation Management portion of the Campus Resource Reservation System. I created the Reservation class to represent reservation records and the ReservationManager class to manage active reservations. Active reservations are stored using a custom singly linked list with head and tail pointers rather than std::list. I implemented insertion, removal, traversal, searching, display, reservation creation, cancellation, duplicate-ID prevention, date validation, and checks for conflicting reservations on the same resource and date. Cancelled reservations are returned so they can be stored on Person C's stack, and restoreReservation supports undo. I tested the reservation module with reservations.txt and wrote the Big-O analysis for reservation insertion and removal. My work is on the feature/reservation-management GitHub branch and was submitted through GitHub commits and a pull request.

**Anugrah Lama:** I implemented the waiting-list queue and cancellation-history stack. The queue adds students when a resource is unavailable and removes them in FIFO order when a slot opens. The stack stores cancelled reservations and restores only the most recent cancellation. I also wrote the complexity analysis for waiting-list processing and undo cancellation. My work is on the feature/queue-stack GitHub branch.

*(Anugrah: edit this paragraph so it matches what you actually coded and tested.)*
