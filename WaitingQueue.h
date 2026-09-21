#ifndef WAITINGQUEUE_H
#define WAITINGQUEUE_H

#include <string>
using namespace std;

// Queue used to keep track of students waiting for a resource
class WaitingQueue {
private:
    struct Node {
        int studentId;
        string studentName;
        string resourceId;
        Node* next;
    };

    Node* front;
    Node* rear;

public:
    WaitingQueue();
    ~WaitingQueue();

    bool isEmpty() const;

    void enqueue(int studentId, string studentName, string resourceId);
    void dequeue();
    void displayWaitingList() const;
};

#endif