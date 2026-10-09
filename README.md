# Campus Resource Reservation System

GitHub: https://github.com/asangarimal-lab/Campus-Resource-Reservation-System

This is our group project. Students can reserve campus stuff like study
rooms, laptops, lab kits, and tutoring slots.

**Submit / demo Milestone 1 from the `milestone-1` branch.**

## Team

| Name | Branch (commit only here) | Milestone 1 work |
| --- | --- | --- |
| Asanga Rimal | `asanga-rimal` | Reservations and the linked list |
| Sebastian Balderrama | `sebastian-balderrama` | Resource management |
| Anugrah Lama | `anugrah-lama` | Waiting list queue and cancellation stack |

## How we use GitHub

```
asanga-rimal
sebastian-balderrama   --PR-->  milestone-1    <-- this is Milestone 1
anugrah-lama
```

Rules:

1. Each person only commits and pushes on their own name branch.
2. Do not commit on `milestone-1` or `main`. Feature work does not go
   there.
3. When your part is ready, open a pull request from your name branch
   into `milestone-1`.
4. `milestone-1` is the combined program we turn in for this milestone.
5. `main` is not the working copy of the project. Later we can merge a
   finished milestone into `main` if we want a default branch with
   everything. For now leave `main` alone.

```
git clone https://github.com/asangarimal-lab/Campus-Resource-Reservation-System.git
git checkout milestone-1
```

## How to compile and run

On CELL or a regular computer:

```
make
./reservation_system
```

Without make:

```
g++ -Wall -std=c++11 -o reservation_system main.cpp Resource.cpp ResourceManager.cpp Reservation.cpp ReservationManager.cpp WaitingQueue.cpp CancellationStack.cpp
./reservation_system
```

Needs `resources.txt` and `reservations.txt` in the same folder.

## Menu

1. Display active reservations
2. Create a reservation
3. Cancel a reservation
4. Display waiting list
5. Undo last cancellation
6. Display cancellation history
7. Display all resources
8. Check resource availability
9. Search reservation by ID
10. Search reservations by student ID
11. Display reservations sorted by date
12. Exit

## Searching

The final system uses a manually implemented Linear Search.

Reservation search starts at the head of the active-reservation
linked list and checks each node until the requested reservation
ID is found or the end of the list is reached.

The system also supports searching all active reservations
associated with a particular student ID.

No library search function is used.

Time complexity:

- Best case: O(1)
- Worst case: O(n)

## Sorting

The team wrote one merge sort in `MergeSort.h` (no `std::sort`).

Sebastian uses it to sort resources by name. Reservation sorting uses
the same merge sort on a copy of the active-reservation linked list,
ordered by date (MM/DD/YYYY converted to YYYYMMDD so the order is
chronological). The original linked list stays in insert order.

Time complexity: O(n log n)

## File format

`resources.txt`

```
resourceId|name|type|status
R101|Study Room 101|Study Room|Available
```

`reservations.txt`

```
reservationId|studentId|studentName|resourceId|MM/DD/YYYY
301|1001|Alice Smith|R101|09/15/2026
```

## Who wrote which files

- Sebastian (`sebastian-balderrama`): `Resource.*`, `ResourceManager.*`, `resources.txt`
- Asanga (`asanga-rimal`): `Reservation.*`, `ReservationManager.*`, `reservations.txt`
- Anugrah (`anugrah-lama`): `WaitingQueue.*`, `CancellationStack.*`
- After those three branches were merged, `main.cpp` / `Makefile` run the whole thing

See `GroupContributionReport.md` and `ComplexityAnalysis.md`.
