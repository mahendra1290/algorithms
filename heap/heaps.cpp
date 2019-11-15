#include <bits/stdc++.h>

using namespace std;

class MaxHeap {
    int *arr;
    int length;
    int heapSize;
    
    static const int DEFAULT_SIZE = 100;
    
    static int getParent(int i) {
        i++;
        return (i / 2) - 1;
    }

    static int getLeft(int i) {
        i++;
        return (2 * i) - 1;
    }

    static int getRight(int i) {
        i++;
        return (2 * i + 1) - 1;
    }

    public:
        MaxHeap();
        MaxHeap(int *arr, int len);
        MaxHeap(int length);
        
        void insert(int key);
        int extractMax();
        int maximum();
        void increaseKey(int i, int newKey);
        
        void static buildMaxHeap(int *arr, int len);
        void static maxHeapify(int *arr, int i, int len);

        void printHeap();

        ~MaxHeap() {
            delete[] arr;
        }
};

MaxHeap::MaxHeap() {
    arr = new int[DEFAULT_SIZE];
    length = 0;
    heapSize = 0;
}

MaxHeap::MaxHeap(int *arr, int len) {
    this->arr = new int[len];
    for (int i = 0; i < len; i++) {
        this->arr[i] = arr[i];
    }
    MaxHeap::buildMaxHeap(this->arr, len);
    length = len;
    heapSize = len;
}

MaxHeap::MaxHeap(int length) {
    arr = new int[length];
    this->length = length;
    heapSize = 0;
}

void MaxHeap::insert(int key) {
    heapSize++;
    arr[heapSize - 1] = INT32_MIN;
    increaseKey(heapSize - 1, key);
}

int MaxHeap::extractMax() {
    int maximum = arr[0];
    arr[0] = arr[heapSize - 1];
    heapSize--;
    MaxHeap::maxHeapify(arr, 0, heapSize);
    return maximum;
}

int MaxHeap::maximum() {
    return arr[0];
}

void MaxHeap::increaseKey(int i, int newKey) {
    if (newKey > arr[i]) {
        arr[i] = newKey;
        while (i > 0 && arr[getParent(i)] < arr[i]) {
            swap(arr[getParent(i)], arr[i]);
            i = getParent(i);
        }
    }
}

void MaxHeap::buildMaxHeap(int *arr, int len) {
    for (int i = len/2 - 1; i >= 0; i--) {
        maxHeapify(arr, i, len);
    }
}

void MaxHeap::maxHeapify(int *arr, int i, int len) {
    int left = getLeft(i);
    int right = getRight(i);
    int largest = i;
    if (left < len && arr[left] > arr[i] ) {
        largest = left;
    }
    if (right < len && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, largest, len);
    }
}

void MaxHeap::printHeap() {
    for (int i = 0; i < heapSize; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    MaxHeap priorityQueue(10);
    for (int i = 0; i < 10; i++) {
        int elem;
        cin >> elem;
        priorityQueue.insert(elem);
        priorityQueue.printHeap();
    }
    for (int i = 0; i < 5; i++) {
        cout << "extravted" << priorityQueue.extractMax() << endl;
        priorityQueue.printHeap();
    }
    return 0;
}