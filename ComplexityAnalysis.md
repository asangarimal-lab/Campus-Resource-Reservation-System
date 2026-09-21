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

Inserting a new node at the tail does not require walking through the list, so
the insertion itself is O(1).

Before a new reservation is accepted, we still have to:

1. Make sure the reservation ID is not already in the list. This requires a
   linear search, O(n).

2. Make sure the same resource is not already reserved on that date. This also
   requires walking through the list, O(n).

So the linked-list insertion is O(1), but the full create-reservation operation
is O(n) because of the validation checks.

Using a tail pointer is useful because without it, even inserting at the end
would require walking through the list and would take O(n).

---

## Reservation removal

Author: Asanga Rimal (Person B)

To cancel a reservation, we start at the head and move forward until the
reservation ID matches.

In the worst case, the reservation is at the end of the list or is not in the
list, so the search takes O(n).

Once the reservation is found, unlinking and deleting the node takes O(1).
The tail pointer is also updated if the last node is removed.

Therefore, the overall cancellation/removal operation is O(n).

---

## Waiting-list processing

Author: Anugrah Lama (Person C)

When a student joins the waiting list, I add them to the end of the queue.

Since the queue keeps a rear pointer, I do not need to traverse the entire
queue to find the last node. Therefore, enqueue takes O(1) time.

To remove the next student, I remove the node at the front of the queue.
Since the queue also keeps a front pointer, dequeue takes O(1) time.

To display the waiting list, I start at the front and visit every node in the
queue. Therefore, displaying the waiting list takes O(w), where w is the
number of students currently waiting.

I used a queue because the waiting list needs to follow FIFO
(First In, First Out) order. The first student added to the waiting list is
the first student removed.

---

## Undo cancellation

Author: Anugrah Lama (Person C)

For cancellation history, each cancelled reservation is pushed onto the top
of the stack.

Since the stack keeps a top pointer, pushing a cancelled reservation takes
O(1) time.

To undo a cancellation, the most recently cancelled reservation is popped
from the top of the stack. The pop operation also takes O(1) time because
there is no need to search through the stack.

After the reservation is popped, restoring it to the active reservation
system may require the normal reservation validation checks. Those checks can
take O(n) time because the active reservation linked list may need to be
searched.

I used a stack because cancellation undo needs to follow LIFO
(Last In, First Out) order. This means the most recently cancelled reservation
is the first one available to be restored.