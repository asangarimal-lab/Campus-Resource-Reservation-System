# Complexity Analysis

Campus Resource Reservation System - Final Project

n = number of active reservations in the linked list

w = number of students on the waiting list

r = number of resources (maximum of 100)

---

## Insertion of a reservation

Asanga Rimal

I have stored all active reservations as nodes within a singly linked list. The head pointer points to the first node in the list and the tail pointer points to the last node. When I add a new node to the end of the list I simply "hook" it to the current tail node and update the tail pointer to point to the new node. This operation is O(1) as I do not traverse the list.

However, prior to adding a new node to the list I must check two things:

1. Is there an existing reservation with the same ID? (O(n))
2. Is the resource being requested available on the specified date? (O(n))

Therefore, although the actual addition of a node to the list is O(1), the overall creation of a new reservation is O(n) due to these checks. If I did not use a tail pointer for my linked list then adding a new node to the end of the list would be O(n).

---

## Removal of a reservation

Asanga Rimal

Canceling or removing a reservation involves traversing the linked list starting from the head pointer and continuing until a match is found for the reservation ID. In the worst case scenario the node containing the matching reservation ID is either the last node in the list or is not present at all.

Thus, searching for a matching reservation ID is O(n). Once the matching node has been located and removed from the list, the removal process is completed by unlinking the node and updating any associated pointers. If the last node in the list is removed then the tail pointer will need to be updated accordingly.

Overall canceling/removing a reservation is O(n).

---

## Waiting-list processing

Anugrah Lama

The waiting list is structured as a queue and includes front and rear pointers. Adding an element to the rear of the queue (enqueue) requires O(1) time. Removing an element from the front of the queue (dequeue) requires O(1) time. Printing the contents of the waiting list involves traversing the queue from front to rear.

Therefore, printing the contents of the waiting list requires O(w) time. The queue data structure is appropriate for this application as the waiting list operates under a FIFO policy. The student who was placed on the waiting list first should receive priority when allocating available resources.

---

## Undoing cancellation

Anugrah Lama

When a reservation is canceled it is placed on a stack. Pushing an element onto the stack requires O(1) time as only the top pointer is affected. Popping an element off the stack also requires O(1) time. Following the popping of a canceled reservation from the stack, restoring the reservation via ReservationManager may require O(n) time as ReservationManager performs ID/date checks prior to restoring the reservation. Stacks operate under a LIFO policy; thus, the last canceled reservation will be restored first when performing an undo operation.

---

## Searching

Anugrah Lama

Searching for a reservation based on reservation ID is a Linear Search. The search begins at the head pointer and proceeds through each node until a match is identified for reservation ID.

- Best-case scenario: Reservation ID matches with first node in list; O(1)
- Worst-case scenario: Reservation ID matches with last node in list or is not found in list; O(n)

Searching for a reservation based on student ID will always require O(n) time as a single student may have multiple reservations; therefore, each node in the list will need to be examined.

---

## Merge Sort

Anugrah Lama

Sebastian created a merge sort algorithm in `MergeSort.h` which is utilized by all members of our team. Merge Sort divides an array into two halves repeatedly until each half contains only one element. Then merge sort combines these halves back together into sorted order.

- Each division into two halves yields log n levels
- Each level combines n elements

Therefore, Merge Sort will always run in O(n log n) time regardless of whether it runs in best, average or worst-case scenarios. Merge sort uses O(n) additional space for temporary arrays during the merging process. Merge Sort is also stable; therefore, elements that share equal values maintain their original relative ordering within the sorted output.

---

## Sorting Resources and Reservations

Anugrah Lama

Sorting resources alphabetically requires creating a copy of the resource array (O(r)) and using merge sort to sort this copy alphabetically. The original resource array will retain its original file-ordering characteristics.

Sorting reservations chronologically requires copying the reservation linked list into an array (O(n)) and using merge sort to sort this array chronologically. The original reservation linked list will retain its original insertion-ordering characteristics.

So sorting resources is O(r log r) and sorting reservations is O(n log n).

---

## Reports

Anugrah Lama

For each resource listed in the reports section, the number of reservations associated with that particular resource is determined by traversing the reservation linked list (O(n)). Similarly, for each resource listed in the reports section, the number of waiting students associated with that particular resource is determined by traversing the waiting-list queue (O(w)). Determining these values for each resource in the reports section will require O(r * (n + w)) time.

- Resource Utilization & Waiting-List Statistics: O(r * (n + w))
- Most Requested & Sort by Popularity: O(r * (n + w)) + O(r log r)
- Active Reservations Report: O(n)

---

## Lookup & Availability of Resources

Sebastian Balderrama

Resources are stored in an array. Locating a resource based on ID requires checking each slot in the array until a match is identified for ID.

Therefore, locating a resource based on ID requires O(r) time. Checking availability of a resource requires first locating that particular resource based on its ID.

Therefore, checking availability of a resource also requires O(r) time.
