#include <bits/stdc++.h>

using namespace std;

void mergeSort(int arr[], int start, int end);

void merge(int arr[], int start, int mid, int end);

void copyArray(int source[], int destination[], int fromIndex, int upToIndex);

int main() {
    int len;
    cin >> len;
    int arr[len];
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }
    mergeSort(arr, 3, 7);
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
}

void mergeSort(int arr[], int start, int end) {
    if (end - start > 1) {
        int mid = (end + start) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid, end);
        merge(arr, start, mid, end);
    }
}

void merge(int arr[], int start, int mid, int end) {
    int lengthOfLeft = mid - start;
    int lengthOfRight = end - mid;
    int leftSubArr[lengthOfLeft + 1];
    int rightSubArr[lengthOfRight + 1];
    leftSubArr[lengthOfLeft] = INT32_MAX;
    rightSubArr[lengthOfRight] = INT32_MAX;
    copyArray(arr, leftSubArr, start, mid);
    copyArray(arr, rightSubArr, mid, end);
    int i = 0;
    int j = 0;
    int k = start;
    while (k < end) {
        if (leftSubArr[i] <= rightSubArr[j]) {
            arr[k++] = leftSubArr[i++];
        }
        else {
            arr[k++] = rightSubArr[j++];
        }
    }
}

void copyArray(int source[], int destination[], int fromIndex, int upToIndex) {
    for (int i = fromIndex; i < upToIndex; i++) {
        destination[i - fromIndex] = source[i];
    }
}