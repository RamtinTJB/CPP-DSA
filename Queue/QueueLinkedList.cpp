#include <iostream>
#include <chrono>
#include <iomanip>
#include <stdexcept>

template <class T>
struct Node {
    T value;
    Node* next;
    Node(T val) : value(val), next(nullptr) {}
};

template <class T>
class Queue {
private:
    Node<T>* head_ = nullptr;
    Node<T>* tail_ = nullptr;
    size_t size_ = 0;
public:
    void enqueue(T value) {
        Node<T>* tmp = new Node<T>(value);
        if (tail_ == nullptr) {
            head_ = tmp;
            tail_ = tmp;
            return;
        }

        tail_->next = tmp;
        tail_ = tmp;
        size_++;
    }

    void dequeue() {
        if (head_ == nullptr)
            return;

        Node<T>* tmp = head_;
        head_ = head_->next;

        if (head_ == nullptr)
            tail_ = nullptr;

        delete tmp;
        size_--;
    }

    T front() const { 
        if (head_ == nullptr)
            throw std::logic_error("Queue is empty");

        return head_->value; 
    }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    ~Queue() {
        while (head_ != nullptr) dequeue();
    }
};

int main(int argc, const char** argv) {
    constexpr size_t NUM_TEST = 10;
    constexpr size_t NUM_ITERATIONS = 100000000;

    double total_time = 0;

    for (size_t test_iter = 0; test_iter < NUM_TEST; ++test_iter) {
        auto start = std::chrono::high_resolution_clock::now();
        Queue<int> q;
        for (size_t i = 0; i < NUM_ITERATIONS; ++i) {
            q.enqueue(i);
        }

        for (size_t i = 0; i < NUM_ITERATIONS; ++i) {
            auto _ = q.front();
            q.dequeue();
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() * 1e-9;
        std::cout << "Time Takes to enqueue and dequeue "
            << NUM_ITERATIONS << " items from the queue: "
            << duration
            << std::setprecision(9)
            << " seconds" << std::endl;
        
        total_time += duration;
    }
    
    std::cout << "Average time: "
        << total_time/NUM_TEST << " seconds" << std::endl;

    return 0;
}
