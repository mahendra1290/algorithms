#include <iostream>

using namespace std;

class MaxHeap {
    int *heap;
    int maxSize;
    int size;
    MaxHeap(int arr[], int n);
    MaxHeap(int maxSize);
    int getParent(int i);
    int getLeftChild(int i);
    int getRightChild(int i);
    bool isLeaf(int i);
    void insert(int val);
    void maxHeapify(int i);
};

MaxHeap::MaxHeap(int maxSize) {
    this->maxSize = maxSize;
    size = 0;
    heap = nullptr;
}

MaxHeap::MaxHeap(int arr[], int n) {
    heap = new int[n+1];
    for (int i = 0; i < n; i++) {
        heap[i+1] = arr[i];
    }
}

inline int MaxHeap::getParent(int i) {
    int parent = i / 2;
    if (parent < 1) {
        return -1;
    }
    return parent;
}

inline int MaxHeap::getLeftChild(int i) {
    int left = 2 * i;
    if 
}

inline int left(int i) {
    return 2 * i;
}

inline int right(int i) {
    return 2 * i + 1;
}

inline int parent(int i) {
    return i/2;
}

void buildMaxHeap(int arr[], int n);

void maxHeapify(int arr[], int i, int n);

int main() {
    return 0;
}

void buildMaxHeap(int arr[], int n) {
    int mid = n/2;
    for (int i = mid; i >= 0; i--) {
        maxHeapify(arr, i, n);
    }
}

void maxHeapify(int arr[], int i, int n) {
    int left = left(i);
    int right = right(i);
    int lower = i;
    if (left <= n && arr[left-1] > arr[i-1]) {
        lower = left;
    }
}