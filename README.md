# Campus Resource Reservation System

GitHub repository:
https://github.com/asangarimal-lab/Campus-Resource-Reservation-System

This is a group project for Milestone 1. Students can reserve campus resources
such as study rooms, laptops, calculators, lab equipment, and tutoring times.
The program also needs waiting lists, cancellation history, and a simple menu.

## Team

| Person | Name | GitHub branch | Responsibility |
| --- | --- | --- | --- |
| Person A | Obed Balderrama | `feature/resource-management` | Resource management |
| Person B | Asanga Rimal | `feature/reservation-management` | Reservations and linked list |
| Person C | Anugrah Lama | `feature/queue-stack` | Waiting-list queue and cancellation stack |

## How to clone and make your branch

```bash
git clone https://github.com/asangarimal-lab/Campus-Resource-Reservation-System.git
cd Campus-Resource-Reservation-System
```

Obed:
```bash
git checkout main
git checkout -b feature/resource-management
```

Anugrah:
```bash
git checkout main
git checkout -b feature/queue-stack
```

Please commit from your own GitHub account. When your part is done, push the
branch and open a Pull Request into `main`. Do not email finished files for
someone else to upload.

## What is in this branch right now (Asanga)

- `Reservation.h` / `Reservation.cpp`
- `ReservationManager.h` / `ReservationManager.cpp`
- `reservations.txt`
- `README.md`
- `ComplexityAnalysis.md` (insertion and removal; queue/undo still need Person C)

ReservationManager stores active reservations in a custom singly linked list
with head and tail pointers. It can insert, remove, traverse, display, load
from a file, create a reservation, cancel a reservation, and restore one for
undo.

After Person A merges, `main` should call:

```cpp
bool resourceExists(string resourceId);
bool isResourceAvailable(string resourceId);
```

before creating a new reservation. If the resource is not available, Person C
should add the student to the waiting queue.

When a reservation is cancelled, ReservationManager returns the Reservation
object so Person C can push it onto the cancellation stack. Undo should pop
that record and call:

```cpp
reservationManager.restoreReservation(...)
```

## File formats

`resources.txt` (Person A)

```text
resourceId|name|type|status
R101|Study Room 101|Study Room|Available
```

`reservations.txt`

```text
reservationId|studentId|studentName|resourceId|MM/DD/YYYY
301|1001|Alice Smith|R101|09/15/2026
```

## Compile (after all three parts are merged)

On CELL / a lab machine, from the project folder:

```bash
g++ -std=c++11 main.cpp Resource.cpp ResourceManager.cpp Reservation.cpp ReservationManager.cpp WaitingList.cpp CancellationStack.cpp -o reservation_system
./reservation_system
```

If your files are named a little differently, just list the actual `.cpp`
files in that same command.

## Menu (full program)

```text
===== Campus Resource Reservation System =====

1. View Resources
2. Create Reservation
3. Cancel Reservation
4. View Waiting Lists
5. Undo Cancellation
6. Search Reservations
7. Sort Resources
8. Generate Report
9. Exit
```

Milestone 1 only needs resource viewing, create/cancel reservations, waiting
lists, undo, and basic error handling. Search, sort, and extra reports can wait
until the final submission if we run out of time.

## Error handling we already have on Person B's side

- Duplicate reservation IDs are rejected
- Empty names / bad dates are rejected
- Same resource on the same date is rejected
- Cancel on a missing ID is rejected
- Reservation file open failure is reported
