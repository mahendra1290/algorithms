#include <bits/stdc++.h>

using namespace std;

int getInversionsCount(int arr[], int len);

int split(int arr[], int start, int end);

int merge(int arr[], int start, int mid, int end);

void copyArray(int source[], int destination[], int fromIndex, int upToIndex);

int main() {
    int len;
    cin >> len;
    int arr[len];
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }
    cout << "inversions = " << getInversionsCount(arr, len) << endl;
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
}

int getInversionsCount(int arr[], int len) {
    int temp[len];
    copyArray(arr, temp, 0, len);
    return split(temp, 0, len-1);
}

int split(int arr[], int start, int end) {
    if (end > start) {
        int mid = (start + end)/2;
        int leftInversions = split(arr, start, mid);
        int rightInversions = split(arr, mid+1, end);
        int currentInversions = merge(arr, start, mid, end);
        return leftInversions + rightInversions + currentInversions;
    }
    return 0;
}

int merge(int arr[], int start, int mid, int end) {
    int leftLen = mid - start + 1;
    int rightLen = end - mid;
    int leftSubArr[leftLen + 1];
    int rightSubArr[rightLen + 1];
    leftSubArr[leftLen] = INT32_MAX;
    rightSubArr[rightLen] = INT32_MAX;
    copyArray(arr, leftSubArr, start, mid+1);
    copyArray(arr, rightSubArr, mid+1, end+1);
    int i = 0;
    int j = 0;
    int inversions = 0;
    for (int k = start; k <= end; k++) {
        if (leftSubArr[i] <= rightSubArr[j]) {
            arr[k] = leftSubArr[i++];
        }
        else {
            arr[k] = rightSubArr[j++];
            inversions += (leftLen - i);
        }
    }
    return inversions;
}

void copyArray(int source[], int destination[], int fromIndex, int upToIndex) {
    for (int i = fromIndex; i < upToIndex; i++) {
        destination[i - fromIndex] = source[i];
    }
}