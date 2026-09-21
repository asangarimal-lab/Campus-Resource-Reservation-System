# Complexity Analysis

Campus Resource Reservation System — Milestone 1

n = number of active reservations in the linked list

w = number of students currently on the waiting list

---

## Reservation insertion

Asanga Rimal

I stored active reservations in a singly linked list with a head pointer
and a tail pointer.

Putting a new node at the tail is O(1), because I do not walk the list.
I just hook it onto tail and move tail forward.

Before we insert, createReservation still has to search the list:

- make sure the reservation ID is not already there (O(n))
- make sure that resource is not already booked on the same date (O(n))

So the insert itself is O(1), but creating a reservation overall is O(n)
because of those checks. The tail pointer still matters. Without it,
even a plain insert at the end would be O(n).

---

## Reservation removal

Asanga Rimal

Cancel starts at head and walks until the reservation ID matches.

Worst case the node is last, or it is not in the list at all, so the
search is O(n). Unlinking the node after that is O(1). If we remove the
last node, tail gets updated too.

Overall cancel/remove is O(n).

---

## Waiting-list processing

Anugrah Lama

The waiting list is a queue with front and rear pointers.

Enqueue adds at the rear, so that is O(1). Dequeue removes from the
front, also O(1). Printing the list starts at front and visits every
node, so that is O(w).

A queue is the right structure here because the waiting list is FIFO.
Whoever got in line first should get the resource first.

---

## Undo cancellation

Anugrah Lama

Cancelled reservations go on a stack. Push is O(1) because we only
touch the top pointer. Pop is also O(1).

After we pop, putting the reservation back through ReservationManager
can take O(n), since the linked list still does the usual ID / date
checks.

A stack is LIFO, which is what we want for undo: the last cancel is the
first one we restore.
