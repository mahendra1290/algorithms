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
        MaxHeap() {
            arr = new int[DEFAULT_SIZE];
            length = 0;
            heapSize = 0;
        }

        MaxHeap(int *arr, int len) {
            this->arr = new int[len];
            for (int i = 0; i < len; i++) {
                this->arr[i] = arr[i];
            }
            MaxHeap::buildMaxHeap(this->arr, len);
            length = len;
            heapSize = len;
        }

        void static buildMaxHeap(int *arr, int len);

        void static maxHeapify(int *arr, int i, int len);

        ~MaxHeap() {
            delete[] arr;
        }
};

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

void heapSort(int *arr, int len);


int main() {
    int len;
    cin >> len;
    int arr[len];
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }
    heapSort(arr, len);
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
}

void heapSort(int *arr, int len) {
    MaxHeap::buildMaxHeap(arr, len);
    for (int i = len - 1; i >= 1; i--) {
        swap(arr[0], arr[i]);
        MaxHeap::maxHeapify(arr, 0, --len);
    }
}