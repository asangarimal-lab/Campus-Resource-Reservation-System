#include "WaitingQueue.h"
#include <iostream>

WaitingQueue::WaitingQueue() : front(nullptr), rear(nullptr) {}

WaitingQueue::~WaitingQueue() {
    while (front != nullptr) {
        Node* old = front;
        front = front->next;
        delete old;
    }
}

bool WaitingQueue::isEmpty() const {
    return front == nullptr;
}

void WaitingQueue::enqueue(int studentId, std::string studentName,
                           std::string resourceId, std::string date) {
    Node* node = new Node{{studentId, studentName, resourceId, date}, nullptr};
    if (rear != nullptr) {
        rear->next = node;
    } else {
        front = node;
    }
    rear = node;
    std::cout << studentName << " was added to the waiting list.\n";
}

bool WaitingQueue::peek(WaitingRequest& request) const {
    if (isEmpty()) return false;
    request = front->request;
    return true;
}

bool WaitingQueue::dequeue(WaitingRequest& request) {
    if (!peek(request)) return false;
    Node* old = front;
    front = front->next;
    if (front == nullptr) rear = nullptr;
    delete old;
    return true;
}

void WaitingQueue::dequeue() {
    WaitingRequest request;
    if (!dequeue(request)) {
        std::cout << "The waiting list is empty.\n";
        return;
    }
    std::cout << request.studentName << " was removed from the waiting list.\n";
}

void WaitingQueue::displayWaitingList() const {
    if (isEmpty()) {
        std::cout << "The waiting list is empty.\n";
        return;
    }
    std::cout << "\nWaiting List:\n";
    for (Node* node = front; node != nullptr; node = node->next) {
        const WaitingRequest& request = node->request;
        std::cout << "Student ID: " << request.studentId
                  << " | Student: " << request.studentName
                  << " | Resource ID: " << request.resourceId;
        if (!request.date.empty()) std::cout << " | Date: " << request.date;
        std::cout << '\n';
    }
}