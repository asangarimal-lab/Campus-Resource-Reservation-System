# Complexity Analysis

Milestone 1 - Campus Resource Reservation System

n = how many reservations are in the linked list
w = how many people are waiting
r = how many resources we have

## Reservation insertion
Asanga Rimal

I stored the active reservations in a linked list with a head and a tail.

Adding a node at the tail is O(1) because I already have a pointer to the last
node, so I don't have to walk the whole list just to insert.

When we create a reservation I still have to look through the list to see if
the ID is already used and if that resource is already booked on that date.
Those checks are O(n).

So insert by itself is O(1), but createReservation is O(n) overall.

If I didn't keep a tail pointer, insert would also be O(n) because I would
have to find the end every time.

## Reservation removal
Asanga Rimal

To cancel, I start at head and keep going until I find the matching ID.
Worst case I look at every node, so that's O(n).

After I find it, taking the node out and deleting it is O(1). If it was the
last node I also move the tail pointer.

So cancel/remove is O(n) total. That's pretty normal for a linked list when
you search by ID. I still used a list because we add and delete reservations
a lot.

## Waiting-list processing
Anugrah Lama

(Anugrah fill this in)

- add to queue: O(1) if you keep a rear pointer
- take the next person off: O(1) if you keep a front pointer
- print the list: O(w)
- queue makes sense because it's first come first served

## Undo cancellation
Anugrah Lama

(Anugrah fill this in)

- push onto the stack: O(1)
- pop the last cancel: O(1)
- putting it back in my list uses restoreReservation which is O(n)
- stack makes sense because we can only undo the most recent cancel
