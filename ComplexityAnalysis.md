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

When a student joins the waiting list, I put them at the end of the line.
Rather than traversing the entire queue, I don't have to since I maintained a rear pointer.
so the addStudent operation takes O(1) time.

To remove the next student, I remove the first node. Since I
They already have a front pointer, as well, so removing the next student is also O(1).

To show the waiting list, I am going to begin at the front of the list and work my way through each...
node, which is O(w) for w being the number of students waiting.

I used a queue which meant that the waiting list should be first come first served.

## Undo cancellation
Anugrah Lama

For cancelation history, I push each cancel reservation onto the top.
of the stack. If I already have a top pointer, then pushing takes O(1) time.

To cancel, I remove the top of the stack.
Also O(1) - no searching through the stack!

The commands to add the reservation back to the active reservation list are
This takes O(n) time: restoresReservation.

I used a stack for the reason that we only want to undo the last cancelled operation,
so last canceled reservation is first restored.
