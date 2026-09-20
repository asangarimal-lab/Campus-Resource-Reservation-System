# Complexity Analysis

Campus Resource Reservation System — Milestone 1

n = number of active reservations in the linked list
w = number of students waiting for one resource
r = number of resources

---

## Reservation insertion

Author: Asanga Rimal (Person B)

Active reservations are stored in a singly linked list with both a head pointer
and a tail pointer.

Inserting a new node at the tail does not require walking the list, so the
insert itself is O(1).

Before a new reservation is accepted we still have to:

1. Make sure the reservation ID is not already in the list. That is a linear
   search, O(n).
2. Make sure the same resource is not already reserved on that date. That is
   also a walk down the list, O(n).

So the linked-list insert is O(1), but the full create-reservation function is
O(n) because of the checks.

Using a tail pointer is still useful. Without it, even the insert would be O(n)
because we would have to find the last node every time.

---

## Reservation removal

Author: Asanga Rimal (Person B)

To cancel a reservation we start at the head and move forward until the
reservation ID matches. In the worst case the node is at the end, or it is not
in the list at all, so the search is O(n).

Unlinking the node and deleting it is O(1) after we have found it. We also
update the tail pointer if the last node was removed.

Overall cancel/remove is O(n).

This is normal for a singly linked list when we search by ID. The list is still
a good fit because reservations are added and removed often, and we do not need
random access by index.

---

## Waiting-list processing

Author: Anugrah Lama (Person C)

Please complete this section on `feature/queue-stack` and replace these notes
with your own write-up.

Suggested points to cover:

- enqueue (add student): O(1) if the queue keeps a rear pointer
- dequeue (serve the next student): O(1) if the queue keeps a front pointer
- display waiting list: O(w)
- why a queue is the right structure (FIFO / first come, first served)

---

## Undo cancellation

Author: Anugrah Lama (Person C)

Please complete this section on `feature/queue-stack` and replace these notes
with your own write-up.

Suggested points to cover:

- push cancelled reservation onto the stack: O(1)
- pop the most recent cancellation: O(1)
- restore that reservation into the linked list: uses Person B's restore,
  which is O(n) because of the same ID/date checks
- why a stack is the right structure (LIFO / only the most recent undo)
