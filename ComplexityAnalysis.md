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

When a student joins the waiting list, I put them at the end of the line.
Rather than traversing the entire queue, I don't have to since I maintained a rear pointer.
so the addStudent operation takes O(1) time.

To remove the next student, I remove the first node. Since I
They already have a front pointer, as well, so removing the next student is also O(1).

To show the waiting list, I am going to begin at the front of the list and work my way through each...
node, which is O(w) for w being the number of students waiting.

I used a queue which meant that the waiting list should be first come first served.

## Undo cancellation

Author: Anugrah Lama (Person C)

For cancelation history, I push each cancel reservation onto the top.
of the stack. If I already have a top pointer, then pushing takes O(1) time.

To cancel, I remove the top of the stack.
Also O(1) - no searching through the stack!

The commands to add the reservation back to the active reservation list are
This takes O(n) time: restoresReservation.

I used a stack for the reason that we only want to undo the last cancelled operation,
so last canceled reservation is first restored.
