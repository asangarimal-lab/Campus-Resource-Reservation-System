# Group Contribution Report

Campus Resource Reservation System — Final Project

GitHub: https://github.com/asangarimal-lab/Campus-Resource-Reservation-System

Submit from branch: `final-project`

## Team

- Asanga Rimal — `asanga-rimal` — Reservation Management and Linked List
- Sebastian Balderrama — `sebastian-balderrama` — Resource Management, Merge Sort, Sorting, Reports, User Guide, in charge of merging
- Anugrah Lama — `anugrah-lama` — Waiting List Queue and Cancellation History Stack

## How we used GitHub

Each person only worked on their own name branch. We did not put feature
commits on `final-project` or `main`. When a person's part was ready, that
branch was merged into `final-project`. That combined branch is what we
are turning in.

Sebastian was in charge of the merging process. He reviewed and merged
the pull requests into `final-project`, fixed merge conflicts between
branches, and checked that the combined program still compiled and ran
after each merge.

---

## Contribution table

| Team Member | Component(s) | Specific Tasks Completed | Testing/Debugging | GitHub Contributions |
| --- | --- | --- | --- | --- |
| Asanga Rimal | Reservation management, custom linked list search, reservation sorting, reporting integration, and file load validation. | He developed Reservation and ReservationManager and implemented linked list insertion, deletion, traversal and display; as well as creation, cancellation, restoration, and duplicate ID/date/conflict checks. For the final project he implemented linear search by reservation ID and student ID; sorted reservations by date using MergeSort.h; created an active reservations report; created a reports menu; added a hook for waiting list statistics; and made the program skip invalid lines in reservations.txt. | He checked the file for bad lines (an abc ID, an xyz student ID, and the date 13/45/2026); searched for 301, 9999, and abc; sorted reservations by date; tested the reports menu; tested creating/cancelling reservations; tested the queue; and tested undo. | This work is located on the feature/asanga-final-reservations branch and was previously committed to asanga-rimal. |
| Sebastian Balderrama | Resource management, merge sort, sorting, reports, user guide, and merging. | He developed Resource and ResourceManager that loads resources.txt; stores resources in an array; displays all resources; checks resource availability; and catches bad resource IDs/missing files. resourceExists and isResourceAvailable are used by the reservation code prior to making a booking. For the final project he developed MergeSort.h; sorted resources by name; sorted resources by popularity; and developed ReportManager (utilization/most requested reports). He added the counting loops in ReservationManager and WaitingQueue for reports; developed UserGuide.md; and was in charge of the merge process. | He checked the loading of the file; the display of the file; the availability of the IDs whether they are fake or real; and checked if the file could not be opened Sorting Tests in TestingResults.md. He also developed search, create/cancel/undo, and availability tests. | All of this is in Sebatian-balderrama and includes the commit "Implement Resource and ResourceManager". PRs #3, #4, #6, and #7 were merged into final-project. He was responsible for merging Asanga's PRs #5 and #8, and resolving the merge conflict in ReservationManager. |
| Anugrah Lama | Waiting list queue and cancellation history stack. | He developed WaitingQueue (enqueue/dequeue/display/empty check/FIFO) and CancellationStack (push/pop/display history/empty check/LIFO). He also developed the waiting-list/undo Big-O in the complexity write-up. | He checked an empty queue/stack; enqueued/dequeued (FIFO); pushed/popped (LIFO); displayed; and restored the last canceled item. | All of this is on anugrah-lama under the commits "Add waiting list queue implementation" and "Add cancellation history stack implementation" and was merged into final-project. |

---

## Individual writeups

**Asanga Rimal:** I worked on reservations as asanga-rimal. A reservation is the information for a single booking. The ReservationManager maintains a linked list of active reservations that I created. Insertions occur at the tail of the list. Removals are performed starting at the head of the list. Displaying the contents of the list requires traversal of the entire list. In order to create a reservation, it is necessary to verify the ID, the date format used, duplicate entries, and if there is another reservation using the same resource on the same date. When a reservation is cancelled, the node representing that reservation is removed from the list and returned to Anugrah's stack. Restoration of reservations is handled by undoing. Additionally, I wrote the Big-O for insertion and removal. For the final project, I added search, sort by date, the reports menu, and file validation.

**Sebastian Balderrama:** I worked on campus resources as sebastian-balderrama. A resource contains an ID number, a name, a type, and an availability status (Available/Unavailable). The ResourceManager reads resources.txt and can maintain a maximum of one hundred resources. It can print all of the resources it has loaded and can determine whether a given ID exists and whether that ID is associated with an available resource. Before booking a reservation, the reservation menu will perform both checks. If the requested resource is unavailable, the student will be placed on a waiting list. For the final project, I wrote the merge sort in MergeSort.h which the team uses to sort resources based upon their name and popularity. I also developed ReportManager for the utilization and most requested reports. I included counting loops within ReservationManager and WaitingQueue which are used by the reports. I authored UserGuide.md and added test cases to TestingResults.md. I coordinated the merging process: I merged pull requests into final-project, resolved conflict issues, and ensured that the combined program compiled and executed after each merge.

**Anugrah Lama:** I worked on the waiting list and undo as anugrah-lama. The queue utilizes front and rear pointers to allow for efficient enqueuing/dequeuing while maintaining a First-In-First-Out (FIFO) ordering. The stack utilizes a top pointer to ensure that the most recently cancelled reservation is always undone first. When a reservation is cancelled, main adds that reservation to my stack. Undo removes that reservation from my stack and Asanga's manager adds it back to the active list. I provided the complexities for both the queue and the undo stack.

After the three name branches were merged into `final-project`, we tested
the whole combined program.
