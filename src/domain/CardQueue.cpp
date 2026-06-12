#include "domain/CardQueue.h"

#include <stdexcept>

CardQueue::CardQueue()
    : head_(nullptr),
      tail_(nullptr),
      size_(0) {
}

CardQueue::CardQueue(const CardQueue& other)
    : head_(nullptr),
      tail_(nullptr),
      size_(0) {
    copyFrom(other);
}

CardQueue& CardQueue::operator=(const CardQueue& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }

    return *this;
}

CardQueue::~CardQueue() {
    clear();
}

void CardQueue::push(int card) {
    Node* newNode = new Node{card, nullptr};

    if (tail_ == nullptr) {
        head_ = newNode;
        tail_ = newNode;
    } else {
        tail_->next = newNode;
        tail_ = newNode;
    }

    ++size_;
}

int CardQueue::pop() {
    if (empty()) {
        throw std::runtime_error("Нельзя извлечь карту из пустой очереди.");
    }

    Node* oldHead = head_;
    int card = oldHead->card;
    head_ = head_->next;

    if (head_ == nullptr) {
        tail_ = nullptr;
    }

    delete oldHead;
    --size_;

    return card;
}

bool CardQueue::empty() const {
    return size_ == 0;
}

int CardQueue::size() const {
    return size_;
}

void CardQueue::clear() {
    while (!empty()) {
        pop();
    }
}

void CardQueue::copyFrom(const CardQueue& other) {
    Node* current = other.head_;

    while (current != nullptr) {
        push(current->card);
        current = current->next;
    }
}
