#include <bits/stdc++.h>

using namespace std;

void insertionSort(int *arr, int len);

int main() {
    int len;
    cin >> len;
    int arr[len];
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }
    insertionSort(arr, len);
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
}

void insertionSort(int *arr, int len) {
    for (int i = 1; i < len; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}