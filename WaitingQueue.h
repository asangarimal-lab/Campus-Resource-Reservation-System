#ifndef WAITINGQUEUE_H
#define WAITINGQUEUE_H

#include <string>
using namespace std;

struct WaitingRequest {
    int studentId;
    string studentName;
    string resourceId;
    string date;
};

class WaitingQueue {
private:
    struct Node {
        int studentId;
        string studentName;
        string resourceId;
        string date;
        Node* next;
    };

    Node* front;
    Node* rear;

public:
    WaitingQueue();
    ~WaitingQueue();

    WaitingQueue(const WaitingQueue&) = delete;
    WaitingQueue& operator=(const WaitingQueue&) = delete;

    bool isEmpty() const;
    int size() const;

    void enqueue(int studentId, string studentName,
                 string resourceId, string date);

    bool peekForResource(string resourceId, string date,
                         WaitingRequest& request) const;

    bool dequeueForResource(string resourceId, string date,
                            WaitingRequest& request);

    void dequeue();
    void displayWaitingList() const;
    int countForResource(string resourceId) const;
};

#endif