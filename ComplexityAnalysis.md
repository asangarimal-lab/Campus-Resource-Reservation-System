# Complexity Analysis (reservation module)

Asanga Rimal — Milestone 1

n = number of active reservations in the linked list

## Reservation insertion

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

## Reservation removal

Cancel starts at head and walks until the reservation ID matches.

Worst case the node is last, or it is not in the list at all, so the
search is O(n). Unlinking the node after that is O(1). If we remove the
last node, tail gets updated too.

Overall cancel/remove is O(n).
