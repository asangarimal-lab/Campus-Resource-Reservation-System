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

## Regression Tests

| Test | Input/Action | Expected Result | Actual Result |
|---|---|---|---|
| Search by reservation ID | Main menu 9, ID 301 | Alice Smith's reservation found | Pass |
| Sort reservations by date | Main menu 11 | Reservations listed from 09/15/2026 through 09/29/2026 | Pass |
| Waiting list enqueue | Create reservation for unavailable R115 | Student added to the waiting list | Pass |
