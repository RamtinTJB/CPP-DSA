#include <iostream>
#include <vector>

class MaxHeap {
private:
    std::vector<int> data_;

    int parent(int i) const {
        return (i-1)/2;
    }

    int left(int i) const {
        return 2*i + 1;
    }

    int right(int i) const {
        return 2*i + 2;
    }

    void heapify_down(int i) {
        int l = left(i);
        int r = right(i);

        int largest = i;

        if (l < size() && data_[l] > data_[largest]) {
            largest = l;
        }

        if (r < size() && data_[r] > data_[largest]) {
            largest = r;
        }

        if (largest != i) {
            std::swap(data_[i], data_[largest]);
            heapify_down(largest);
        }
    }

    void heapify_up(int i) {
        if (i > 0 && data_[parent(i)] < data_[i]) {
            std::swap(data_[i], data_[parent(i)]);
            heapify_up(parent(i));
        }
    }

public:
    constexpr size_t size() const { return data_.size(); }

    bool empty() const { return size() == 0; }

    void push(int key) {
        data_.push_back(key);
        heapify_up(data_.size()-1);
    }

    void pop() {
        if (empty()) return;

        data_[0] = data_.back();
        data_.pop_back();
        heapify_down(0);
    }

    int top() {
        if (empty()) return 0;
        return data_[0];
    }
};

int main(int argc, const char** argv) {
    MaxHeap mh;

    mh.push(15);
    mh.push(3);
    mh.push(2);
    mh.push(40);

    while (!mh.empty()) {
        std::cout << mh.top() << " ";
        mh.pop();
    }

    std::cout << std::endl;

    return 0;
}
