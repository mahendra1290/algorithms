#include <bits/stdc++.h>

using namespace std;

void quickSort(int arr[], int start, int end);

int main() {
    int len;
    cin >> len;
    int arr[len];
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }
    quickSort(arr, 3, 7);
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
}

void quickSort(int arr[], int start, int end) {
    if (end - start > 1) {
        int pivotIndex = end - 1;
        int i = start - 1;
        int j = start;
        for (j = start; j < end - 1; j++) {
            if (arr[j] <= arr[pivotIndex]) {
                i += 1;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[pivotIndex]);
        int newPivot = i + 1;
        quickSort(arr, start, newPivot);
        quickSort(arr, newPivot + 1, end);
    }
}