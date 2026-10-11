# Campus Resource Reservation System

GitHub: https://github.com/asangarimal-lab/Campus-Resource-Reservation-System

This is our team's project. Students will be able to make reservations for a variety of campus items such as study rooms, laptops, laboratory equipment, and tutoring appointments.

**Please submit/demonstrate the final project using the final-project branch.**

## Team

| Name | Branch (commit only here) | Work |
| --- | --- | --- |
| Asanga Rimal | asanga-rimal | Reservations; Linked List for Reservations; Search Functionality; Sort Functionality Based on Date; Reports Menu; File Loading Error Handling |
| Sebastian Balderrama | sebastian-balderrama | Resource Management; Merge Sort; Sorting Resources by Name and Popularity; Utilization and Most Requested Reports; User Guide |
| Anugrah Lama | anugrah-lama | Waiting List Queue; Cancellation Stack |

## How We Use GitHub

```
asanga-rimal
sebastian-balderrama   --PR-->  final-project    <-- this is the final project
anugrah-lama
```

Guidelines:

1. Only commit and push changes to your designated branch.
2. Do not commit or push to final-project or main. Feature development does not occur on either of these branches.
3. Once your portion of the project has been completed, create a pull request from your branch to final-project.
4. The final-project branch contains the complete program that will be submitted for the final project.
5. The main branch is not intended as a working copy of the project. After all features have been implemented and tested, final-project will be merged into main.

```
git clone https://github.com/asangarimal-lab/Campus-Resource-Reservation-System.git
git checkout final-project
```

## Compiling and Running the Program

On CELL or any other computer:

```
make
./reservation_system
```

Without Make:

```
g++ -Wall -std=c++11 -o reservation_system main.cpp Resource.cpp ResourceManager.cpp Reservation.cpp ReservationManager.cpp WaitingQueue.cpp CancellationStack.cpp ReportManager.cpp
./reservation_system
```

The program requires both `resources.txt` and `reservations.txt` to be located within the same directory.

## Menu Options

1. View all current reservations
2. Create a new reservation
3. Cancel an existing reservation
4. View the waiting list
5. Undo the previous cancellation action
6. View a record of previous cancellations
7. View all resources
8. Determine if a given resource is available for reservation
9. Search for a specific reservation by id number
10. Search for all reservations made by a specific student id number
11. View all reservations sorted chronologically by date
12. Generate various reports regarding campus resource usage
13. View all resources sorted alphabetically by name (using merge sort)
14. View all resources sorted by their popularity (using merge sort)
15. Exit the program

## Searching

The final version of the program utilizes a manually-coded Linear Search algorithm.

When searching for a specific reservation id number, the program begins at the beginning of the active reservation linked list and iterates through each node until either the desired reservation id number is found or the end of the linked list is reached.

Additionally, the program supports searching for all active reservations created by a specific student id number.

None of the standard library search functions are used in this program.

Time Complexity:

- Best Case: O(1)
- Worst Case: O(n)

## Sorting

The team developed a single Merge Sort algorithm in `MergeSort.h` (i.e., no `std::sort`).

Sebastian utilizes this Merge Sort algorithm to sort resources alphabetically by name and by popularity. Reservations are also sorted using this same Merge Sort algorithm on a copy of the active reservation linked list, which is then ordered chronologically based upon date (MM/DD/YYYY is converted to YYYYMMDD for proper chronological ordering). The original active reservation linked list remains in insertion order.

Time Complexity: O(n log n)

## Reporting

The program includes an integrated reporting menu that includes:

- Report on active reservations
- Report on resource utilization
- Report on most frequently requested resources
- Statistics on the waiting list

The report on active reservations is generated from the custom reservation linked list used in the program.

Resource utilization and popularity data are generated from the reservation data collected and stored by the program. Statistics on the waiting list are generated from the waiting list data structure utilized in the program.

## File Format

resources.txt:

```
resourceId|name|type|status
R101|Study Room 101|Study Room|Available
```

reservations.txt:

```
reservationId|studentId|studentName|resourceId|MM/DD/YYYY
301|1001|Alice Smith|R101|09/15/2026
```

Lines that contain errors (i.e., non-numeric IDs, student ID `xyz`, or invalid dates such as `13/45/2026`) are ignored during file loading; however, the program continues to execute. Error-containing records are not added to the database as ID `0`.

## Error Handling

Input provided via menus that is not numeric will be rejected by the program; however, the menu will remain displayed until valid numeric input is received.

Reservation creation/cancellation/search operations require numeric IDs. File loading performs identical validation checks on reservation fields as reservation creation (i.e., positive IDs, name, resource, and valid MM/DD/YYYY date).

## Who Wrote Which Files

- Sebastian (sebastian-balderrama): `Resource.*`, `ResourceManager.*`, `resources.txt`, `MergeSort.h`, `ReportManager.*`, `UserGuide.md`
- Asanga (asanga-rimal): `Reservation.*`, `ReservationManager.*`, `reservations.txt`
- Anugrah (anugrah-lama): `WaitingQueue.*`, `CancellationStack.*`
- After these three branches were merged, `main.cpp` / `Makefile` execute the entire program.

Please refer to `GroupContributionReport.md` and `ComplexityAnalysis.md`.
