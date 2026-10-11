# User Guide

## How to run

You need to have`resources.txt` and `reservations.txt` in the same folder 

make
./reservation_system

Type the number of an option and press Enter.

## Main menu

| Option | What it does | What you type |
|---|---|---|
| 1 | Shows all active reservations | Nothing |
| 2 | Creates a reservation. If the resource is taken or unavailable, the student goes on the waiting list | Resource ID, student ID, name, date (MM/DD/YYYY) |
| 3 | Cancels a reservation | Reservation ID |
| 4 | Shows the waiting list | Nothing |
| 5 | Undoes the last cancellation | Nothing |
| 6 | Shows the cancellation history | Nothing |
| 7 | Shows all resources | Nothing |
| 8 | Checks if a resource is available | Resource ID |
| 9 | Finds a reservation by ID | Reservation ID |
| 10 | Finds all reservations for a student | Student ID |
| 11 | Shows reservations sorted by date | Nothing |
| 12 | Opens the reports menu | Nothing |
| 13 | Shows resources sorted by name | Nothing |
| 14 | Shows resources sorted by popularity | Nothing |
| 15 | Exits | Nothing |

## Reports menu (option 12)

| Option | What it does |
|---|---|
| 1 | Active reservations report |
| 2 | Resource utilization (reservations per resource) |
| 3 | Most requested resources (ranked by reservations + waiting) |
| 4 | Waiting-list statistics |
| 5 | Back to the main menu |

## Sample output

Option 13:

```
----- Resources (sorted by name) -----
Resource ID: R113 | Name: Chemistry Lab Kit | Type: Lab Equipment | Status: Available
Resource ID: R111 | Name: Graphing Calculator Set | Type: Calculator | Status: Available

Total: 10
```

Option 14 (after reserving R105):

```
----- Resources (sorted by popularity)
R105 | Study Room 105 | Reservations: 3
R111 | Graphing Calculator Set | Reservations: 2
```

## If a reservation file line is bad

The program still starts. It prints that the line was skipped and why.
Those records are not loaded.

Examples that get skipped:

```
abc|1001|Alice Smith|R101|09/15/2026
301|xyz|Alice Smith|R101|09/15/2026
301|1001|Alice Smith|R101|13/45/2026
```

## Tips

- IDs are case sensitive
- Dates must be MM/DD/YYYY
- Changes are not saved to the files. 
