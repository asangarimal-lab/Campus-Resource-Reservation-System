#ifndef WAITINGQUEUE_H
#define WAITINGQUEUE_H

#include <string>

// One student's request; date is optional for existing callers.
struct WaitingRequest {
    int studentId = 0;
    std::string studentName;
    std::string resourceId;
    std::string date;
};

class WaitingQueue {
private:
    struct Node {
        WaitingRequest request;
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
    void enqueue(int studentId, std::string studentName,
                 std::string resourceId, std::string date = "");
    // On an empty queue, return false and leave request unchanged.
    bool dequeue(WaitingRequest& request);
    bool peek(WaitingRequest& request) const;
    void dequeue(); // Compatibility with the original display-only operation.
    void displayWaitingList() const;
};
#endif