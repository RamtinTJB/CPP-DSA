#include <iostream>
#include <chrono>
#include <iomanip>

struct Node {
    int value;
    Node* next;
    Node(int val) : value(val), next(nullptr) {}
};

class Queue {
private:
    Node* front_ = nullptr;
    Node* rear_ = nullptr;
public:
    void enqueue(int value) {
        Node* tmp = new Node(value);
        if (rear_ == nullptr) {
            front_ = tmp;
            rear_ = tmp;
            return;
        }

        rear_->next = tmp;
        rear_ = tmp;
    }

    void dequeue() {
        if (front_ == nullptr)
            return;

        Node* tmp = front_;
        front_ = front_->next;

        if (front_ == nullptr)
            rear_ = nullptr;

        delete tmp;
    }

    int front() const {
        return front_->value;
    }
};

int main(int argc, const char** argv) {
    auto start = std::chrono::high_resolution_clock::now();

    Queue q;
    for (int i = 0; i < 10000; ++i) {
        q.enqueue(i);
    }

    for (int i = 0; i < 10000; ++i) {
        std::cout << q.front() << " ";
        q.dequeue();
    }
    
    std::cout << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time Take: "
        << std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count()
        << std::setprecision(9)
        << " nanoseconds" << std::endl;


    return 0;
}
