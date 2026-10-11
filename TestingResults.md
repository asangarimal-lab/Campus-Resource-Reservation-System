# Project 1 Testing Results

## Reporting Tests

| Test | Input/Action | Expected Result | Actual Result |
|---|---|---|---|
| Active reservation report | Select Reports > Active Reservations | All active reservations and total displayed | Pass |
| Resource utilization | Select Reports > Resource Utilization | Each resource and reservation count displayed | Pass |
| Most requested resources | Select Reports > Most Requested Resources | Resource request counts displayed/ranked | Pass |
| Waiting-list statistics | Select Reports > Waiting-List Statistics | Waiting count shown for each relevant resource | Pass |
| Invalid report option | Enter invalid menu option | Error displayed and menu remains active | Pass |
| Return from reports | Select Return to main menu | Goes back to the main menu | Pass |
| Waiting list after enqueue | Add a student to R115 wait list, then waiting-list report | R115 shows 1 student waiting | Pass |

## Sorting Tests

| Test | Input/Action | Expected Result | Actual Result |
|---|---|---|---|
| Sort by name | Main menu 13 | Resources listed A to Z | Pass |
| Sort by popularity (ties) | Main menu 14 | Ties listed A to Z | Pass |
| Popularity after new reservation | Reserve R105, then 14 | R105 moves to top | Pass |
| Popularity after cancel | Cancel 307, then 14 | R113 moves to bottom | Pass |
| Most requested after new reservation | Reserve R105, then Reports > 3 | R105 ranked 1 | Pass |
| No data files | Run without the .txt files, then 13, 14 | "No resources loaded." shown, no crash | Pass |
| Bad menu input | Type abc, then 99 | Error shown, menu keeps running | Pass |

## File load error handling

| Test | Input/Action | Expected Result | Actual Result |
|---|---|---|---|
| Non-numeric reservation ID | Line `abc\|1001\|Alice Smith\|R101\|09/15/2026` | Line skipped; program starts; ID 0 is not inserted | Pass |
| Non-numeric student ID | Line `301\|xyz\|Alice Smith\|R101\|09/15/2026` | Line skipped; program starts | Pass |
| Impossible date | Line `301\|1001\|Alice Smith\|R101\|13/45/2026` | Line skipped; program starts | Pass |
| Good records still load | Same file also has valid lines 301–320 | 20 active reservations; search 301 still finds Alice | Pass |

## Regression Tests

| Test | Input/Action | Expected Result | Actual Result |
|---|---|---|---|
| Search by reservation ID | Main menu 9, ID 301 | Alice Smith's reservation found | Pass |
| Sort reservations by date | Main menu 11 | Reservations listed from 09/15/2026 through 09/29/2026 | Pass |
| Waiting list enqueue | Create reservation for unavailable R115 | Student added to the waiting list | Pass |
