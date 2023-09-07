#include <vector>
#include <iostream>

using namespace std;

void maxHeapifyDown(vector<int>&, int, int);

void heapSort(vector<int>& v) {
    for (int i = (v.size() / 2) - 1; i >= 0; i--) {
        maxHeapifyDown(v, i, v.size());
    }

    for (int i = v.size()-1; i > 0; i--) {
        std::swap(v[0], v[i]);
        maxHeapifyDown(v, 0, i);
    }
}

void maxHeapifyDown(vector<int>& v, int idx, int heapSize) {
    int left = 2*idx + 1;
    int right = 2*idx + 2;

    int largest = idx;

    if (left < heapSize && v[left] > v[largest]) {
        largest = left;
    }

    if (right < heapSize && v[right] > v[largest]) {
        largest = right;
    }

    if (largest != idx) {
        swap(v[largest], v[idx]);
        maxHeapifyDown(v, largest, heapSize);
    }
}

int main(int argc, const char** argv) {
    vector<int> v {5, 3, 10, 9, 45, 3, 2823, 3, 67};
    heapSort(v);

    for (const auto& n : v) cout << n << " ";
    cout << endl;

    return 0;
}
