#include <bits/stdc++.h>

using namespace std;

template<class T>
class PriorityQueue {
    vector<T> arr;
    int length;
    int heapSize;
    bool (*compareFunc)(T &elem1, T &elem2);
    bool (*equalityFunc)(T &elem1, T &elem2);
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
        PriorityQueue(vector<T> arr, 
                    bool (*compare)(T &v1, T &v2),
                    bool (*equal)(T &v1, T &v2));
        void setCompareFunction(bool (*compare)(T &elem1, T &elem2));
        void setEqualityFunction(bool (*equal)(T &elem1, T &elem2));       
        T extractMin();
        //int maximum();
        void decreaseKey(T elem, T newElem);
        bool compare(T v1, T v2);
        
        bool isEmpty();
        void buildMinHeap();
        void minHeapify(int i);

        void printHeap(void (*printFunc)(T &v));
};

template<class T>
PriorityQueue<T>::PriorityQueue(vector<T> arr, 
        bool (*compare)(T &v1, T &v2),
        bool (*equal)(T &v1, T &v2)) {
    compareFunc = compare;
    equalityFunc = equal;
    this->arr = arr;
    length = arr.size();
    heapSize = length;
    buildMinHeap();
}

template<class T>
void PriorityQueue<T>::setCompareFunction(bool (*compare)(T &elem1, T &elem2)) {
    compareFunc = compare;
}

template<class T>
void PriorityQueue<T>::setEqualityFunction(bool (*equal)(T &elem1, T &elem2)) {
    equalityFunc = equal;
}



template<class T>
bool PriorityQueue<T>::compare(T v1, T v2) {
    return (*compareFunc)(v1, v2);
}

template<class T>
bool PriorityQueue<T>::isEmpty() {
    return heapSize == 0;
}

template<class T>
T PriorityQueue<T>::extractMin() {
    T minimum = arr[0];
    arr[0] = arr[heapSize - 1];
    heapSize--;
    PriorityQueue::minHeapify(0);
    return minimum;
}

// int PriorityQueue::maximum() {
//     return arr[0];
// }


template<class T>
void PriorityQueue<T>::decreaseKey(T elem, T newElem) {
    if (compareFunc(newElem, elem)) {
        int i = 0;
        for (i = 0; i < arr.size(); i++) {
            if (equalityFunc(elem, arr[i])) {
                arr[i] = newElem;
                break;
            }
        }
        while (i > 0 && !compareFunc(arr[getParent(i)], arr[i])) {
            swap(arr[getParent(i)], arr[i]);
            i = getParent(i);
        }
    }
}

template<class T>
void PriorityQueue<T>::buildMinHeap() {
    int len = arr.size();
    for (int i = len/2 - 1; i >= 0; i--) {
        minHeapify(i);
    }
}

template<class T>
void PriorityQueue<T>::minHeapify(int i) {
    int len = arr.size();
    int left = getLeft(i);
    int right = getRight(i);
    int smallest = i;
    if (left < len && compare(arr[left], arr[right]) ) {
        smallest = left;
    }
    if (right < len && compare(arr[right], arr[smallest]) ) {
        smallest = right;
    }
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        minHeapify(smallest);
    }
}

template<class T>
void PriorityQueue<T>::printHeap(void (*printFunc)(T &v)) {
    for (int i = 0; i < heapSize; i++) {
        (*printFunc)(arr[i]);
    }
    cout << endl;
}

