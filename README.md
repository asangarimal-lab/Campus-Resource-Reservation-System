# Campus Resource Reservation System — Asanga Rimal

This branch (`asanga-rimal`) is my reservation / linked list work.

I also hooked it up to Sebastian's resources and Anugrah's queue/stack
so the program actually runs. Cancelled reservations go on the stack.
If a resource is not available, the student goes on the waiting list
queue. Menu option 1 prints the active reservations from the linked list.

## Compile and run

```
make
./reservation_system
```

## Menu

1. Display active reservations
2. Create a reservation
3. Cancel a reservation (pushes onto the cancellation stack)
4. Display waiting list (queue)
5. Undo last cancellation (pops the stack)
6. Display cancellation history
7. Display all resources
8. Check resource availability
9. Exit
