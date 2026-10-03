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

1. Display active reservations (linked list)
2. Create a reservation (unavailable / date conflict goes on the waiting-list queue)
3. Cancel a reservation (pushes onto the cancellation stack)
4. Display waiting list (queue)
5. Undo last cancellation (pops the stack)
6. Display cancellation history (stack)
7. Display all resources
8. Check resource availability
9. Exit

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
