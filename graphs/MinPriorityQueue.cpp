#include <bits/stdc++.h>

using namespace std;

// class Vertex : Comparable<Vertex> {
//     int id;
//     public:
//     int key;
//         Vertex(int id, int key) {
//             this->id = id;
//             this->key = key;
//         }
//         int compareTo(Vertex v) {
//             if (key < v.key)
//                 return -1;
//             else if (key > v.key)
//                 return 1;
//             return 0;
//         }
// };

// struct CompareVertex {
//     int compare(Vertex v1, Vertex v2) {
//         if (v1.key < v2.key) {
//             return -1;
//         }
//         else if (v1.key > v2.key) {
//             return 1;
//         }
//         return 0;
//     }
    
//     int getKey(Vertex v) {
//         return v.key;
//     }

//     void setKey(Vertex &v, int newKey) {
//         v.key = newKey;
//     }

// };

struct CompareInt {
    int compare(int v1, int v2) {
        if (v1 < v2) {
            return -1;
        }
        else if (v1 > v2) {
            return 1;
        }
        return 0;
    }
};

template<class T, class F>
class PriorityQueue {
    vector<T> arr;
    F util;
    unordered_map<
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

    int getKey(int index);
    public:
        PriorityQueue(vector<T> arr);      
        T extractMin();
        void decreaseKey(int index, int newKey);
        int compare(T obj1, T obj2);
        
        bool isEmpty();
        void buildMinHeap();
        void minHeapify(int i);

        void printHeap();
};

template<class T, class F>
PriorityQueue<T, F>::PriorityQueue(vector<T> arr) {
    this->arr = arr;
    length = arr.size();
    heapSize = length;
    this->util = util;
    buildMinHeap();
}

template<class T, class F>
int PriorityQueue<T, F>::compare(T v1, T v2) {
    return util.compare(v1, v2);
}

template<class T, class F>
bool PriorityQueue<T, F>::isEmpty() {
    return heapSize == 0;
}

template<class T, class F>
T PriorityQueue<T, F>::extractMin() {
    T minimum = arr[0];
    arr[0] = arr[heapSize - 1];
    heapSize--;
    PriorityQueue::minHeapify(0);
    return minimum;
}

template<class T, class F>
int PriorityQueue<T, F>::getKey(int index) {
    return util.getKey(arr[index]);
}

template<class T, class F>
void PriorityQueue<T, F>::decreaseKey(int index, int newKey) {
    if (getKey(index > newKey)) {
        util.setKey(arr[index], newKey);
        while (index > 0 && compare(arr[getParent(index)], arr[index]) == 1) {
            swap(arr[index], arr[getParent(index)]);
            index = getParent(index);
        }
    }
}

template<class T, class F>
void PriorityQueue<T, F>::buildMinHeap() {
    int len = arr.size();
    for (int i = len/2 - 1; i >= 0; i--) {
        minHeapify(i);
    }
}

template<class T, class F>
void PriorityQueue<T, F>::minHeapify(int i) {
    int len = arr.size();
    int left = getLeft(i);
    int right = getRight(i);
    int smallest = i;
    if (left < len && compare(arr[left], arr[smallest]) == -1 ) {
        smallest = left;
    }
    if (right < len && compare(arr[right], arr[smallest]) == -1 ) {
        smallest = right;
    }
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        minHeapify(smallest);
    }
}

template<class T, class F>
void PriorityQueue<T, F>::printHeap() {
    for (int i = 0; i < heapSize; i++) {
        cout << arr[i].key << " "; 
    }
    cout << endl;
}

// int main() {
//     vector<Vertex> v;
//     for (int i = 0; i < 5; i++) {
//         int key;
//         cin >> key;
//         Vertex vertex(i, key);
//         v.push_back(vertex);
//     }
//     PriorityQueue<Vertex, CompareVertex> que(v);
//     que.printHeap();
//     for (int i = 0; i < 5; i++) {
//         int ind, key;
//         cin >> ind >> key;
//         que.decreaseKey(ind, key);
//         que.printHeap();
//         que.extractMin();
//         que.printHeap();
//     }
//     return 0;
// }