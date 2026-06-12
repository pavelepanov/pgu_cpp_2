#ifndef DOMAIN_CARD_QUEUE_H
#define DOMAIN_CARD_QUEUE_H

class CardQueue {
public:
    CardQueue();
    CardQueue(const CardQueue& other);
    CardQueue& operator=(const CardQueue& other);
    ~CardQueue();

    void push(int card);
    int pop();
    bool empty() const;
    int size() const;
    void clear();

private:
    struct Node {
        int card;
        Node* next;
    };

    Node* head_;
    Node* tail_;
    int size_;

    void copyFrom(const CardQueue& other);
};

#endif
