#include <iostream>
#include <iomanip>
#include <chrono>
#include <stdexcept>

template <class T>
class Queue {
private:
    size_t head_ = 0, tail_ = 0;
    T* buffer_;
    size_t size_ = 0;
    size_t capacity_;
public:
    Queue(size_t size) : capacity_(size) {
        buffer_ = new T[size];
    }
 
    void enqueue(int value) {
        // If the queue is full, it overwrites the values
        buffer_[tail_] = value;
        tail_ = (tail_+1) % capacity_;
        size_++;
        if (size_ > capacity_) size_ = capacity_;
    }

    void dequeue() {
        if (size_ == 0) return;
        head_ = (head_+1) % capacity_;
        size_--;
    }

    T front() const {
        if (size_ == 0) 
            throw std::logic_error("Queue is empty");

        return buffer_[head_];
    }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    ~Queue() {
        delete[] buffer_;
    }
};

int main(int argc, const char** argv) {
    constexpr size_t NUM_TEST = 10;
    constexpr size_t NUM_ITERATIONS = 100000000;

    double total_time = 0;

    for (size_t test_iter = 0; test_iter < NUM_TEST; ++test_iter) {
        auto start = std::chrono::high_resolution_clock::now();
        Queue<int> q(NUM_ITERATIONS);
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