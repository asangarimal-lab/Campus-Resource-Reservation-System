# Group Contribution Report

Campus Resource Reservation System — Milestone 1

GitHub: https://github.com/asangarimal-lab/Campus-Resource-Reservation-System

Submit from branch: `milestone-1`

## Team

- Asanga Rimal — `asanga-rimal` — Reservation Management and Linked List
- Sebastian Balderrama — `sebastian-balderrama` — Resource Management
- Anugrah Lama — `anugrah-lama` — Waiting List Queue and Cancellation History Stack

## How we used GitHub

Each person only worked on their own name branch. We did not put feature
commits on `milestone-1` or `main`. When a person's part was ready, that
branch was merged into `milestone-1`. That combined branch is what we
are turning in.

---

## Contribution table

| Team Member | Component(s) | Specific Tasks Completed | Testing/Debugging | GitHub Contributions |
| --- | --- | --- | --- | --- |
| Asanga Rimal | Reservation management, custom linked list | Wrote `Reservation` (id, student id, name, resource id, date). Wrote `ReservationManager` with a singly linked list (head and tail). Insert, remove, traverse, display, load `reservations.txt`, create, cancel, restore, duplicate ID check, date check, same-resource/same-date conflict. Reservation insert/remove Big-O in the complexity writeup. | Loaded the sample reservation file. Tried a normal insert, a duplicate ID, a bad date, a date conflict, canceling an id that is not there, display/traverse, and restore after a cancel. | All of this is on `asanga-rimal`. Merged into `milestone-1`. |
| Sebastian Balderrama | Resource management | Wrote `Resource` and `ResourceManager`. Load `resources.txt`, store resources in an array, display all resources, check availability, catch a bad resource id / missing file. `resourceExists` and `isResourceAvailable` are what the reservation code uses before creating a booking. | File load, display, availability for a real id and a fake id, and what happens if the file cannot be opened. | All of this is on `sebastian-balderrama`. Commit: `Implement Resource and ResourceManager`. Merged into `milestone-1`. |
| Anugrah Lama | Waiting list queue, cancellation stack | Wrote `WaitingQueue` (enqueue, dequeue, display, empty check, FIFO). Wrote `CancellationStack` (push, pop, display history, empty check, LIFO). Waiting-list and undo Big-O in the complexity writeup. | Empty queue/stack, enqueue then dequeue (FIFO), push then pop (LIFO), display, and restore of the most recent cancel. | All of this is on `anugrah-lama`. Commits: `Add waiting list queue implementation`, `Add cancellation history stack implementation`. Merged into `milestone-1`. |

---

## Individual writeups

**Asanga Rimal:** I handled reservations on `asanga-rimal`. `Reservation`
is the data for one booking. `ReservationManager` keeps the active ones
in a linked list I wrote myself (not `std::list`). Insert goes on the
tail, remove walks from the head, and display walks the whole list.
Create checks IDs, the date format, duplicates, and whether that
resource is already taken on that day. Cancel takes the node out and
hands the Reservation object back so it can go on Anugrah's stack.
`restoreReservation` is what undo uses. I also wrote the Big-O for
insert and remove.

**Sebastian Balderrama:** I handled campus resources on
`sebastian-balderrama`. `Resource` stores id, name, type, and
Available/Unavailable. `ResourceManager` reads `resources.txt`, keeps
up to 100 resources, prints them, and answers whether an id exists and
whether it is available. The reservation menu uses those two checks
before it books anything. If the resource is not available, the student
gets sent to the waiting list instead.

**Anugrah Lama:** I handled the waiting list and undo on `anugrah-lama`.
The queue uses front and rear pointers so enqueue/dequeue stay cheap
and stay in FIFO order. The stack uses a top pointer so we always undo
the latest cancel first. When someone cancels, `main` pushes that
reservation onto my stack. Undo pops it and Asanga's manager puts it
back on the active list. I wrote the complexity parts for the queue and
the undo stack.

After the three name branches were merged into `milestone-1`, we ran
create, cancel, waiting list, and undo on the combined program.
