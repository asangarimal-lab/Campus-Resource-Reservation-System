#include "WaitingQueue.h"
#include <iostream>
using namespace std;

// Starts with an empty queue
WaitingQueue::WaitingQueue() {
    front = nullptr;
    rear = nullptr;
}

// Deletes all remaining nodes when the queue is destroyed
WaitingQueue::~WaitingQueue() {
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }

    rear = nullptr;
}

bool WaitingQueue::isEmpty() const {
    return front == nullptr;
}

void WaitingQueue::enqueue(int studentId, string studentName,
                           string resourceId, string date) {
    Node* newNode = new Node;

    newNode->studentId = studentId;
    newNode->studentName = studentName;
    newNode->resourceId = resourceId;
    newNode->date = date;
    newNode->next = nullptr;

    if (isEmpty()) {
        front = newNode;
        rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }

    cout << studentName << " was added to the waiting list." << endl;
}

int WaitingQueue::size() const {
    int count = 0;
    Node* current = front;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}

bool WaitingQueue::peekForResource(string resourceId, string date,
                                   WaitingRequest& request) const {
    Node* current = front;

    while (current != nullptr) {
        if (current->resourceId == resourceId && current->date == date) {
            request = {current->studentId, current->studentName,
                       current->resourceId, current->date};
            return true;
        }

        current = current->next;
    }

    return false;
}

bool WaitingQueue::dequeueForResource(string resourceId, string date,
                                      WaitingRequest& request) {
    Node* current = front;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->resourceId == resourceId && current->date == date) {
            request = {current->studentId, current->studentName,
                       current->resourceId, current->date};

            if (previous == nullptr) {
                front = current->next;
            }
            else {
                previous->next = current->next;
            }

            if (current == rear) {
                rear = previous;
            }

            delete current;
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

// Removes the student at the front of the waiting list
void WaitingQueue::dequeue() {
    if (isEmpty()) {
        cout << "The waiting list is empty." << endl;
        return;
    }

    Node* temp = front;

    cout << front->studentName
         << " was removed from the waiting list." << endl;

    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
}

// Goes from front to rear and counts the students waiting for this resource
int WaitingQueue::countForResource(string resourceId) const {
    int count = 0;
    Node* current = front;

    while (current != nullptr) {
        if (current->resourceId == resourceId) {
            count++;
        }

        current = current->next;
    }

    return count;
}

// Displays everyone currently in the waiting list
void WaitingQueue::displayWaitingList() const {
    if (isEmpty()) {
        cout << "The waiting list is empty." << endl;
        return;
    }

    Node* current = front;

    cout << "\nWaiting List:" << endl;

    while (current != nullptr) {
        cout << "Student ID: " << current->studentId
             << " | Student: " << current->studentName
             << " | Resource ID: " << current->resourceId
             << " | Date: " << current->date
             << endl;

        current = current->next;
    }
}