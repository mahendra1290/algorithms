#include <iostream>

using namespace std;

void countingSort(int arr[], int len);

int getMax(int arr[], int len);

int main() {
    int arr[10] = {9, 5, 6 , 5 , 2 , 2 , 7 , 3 , 4 , 5};
    countingSort(arr, 10);
    for (int i=0; i<10; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}

int getMax(int arr[], int len) {
    int max = -1;
    for (int i = 0; i < len; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void countingSort(int arr[], int len) {
    int max = getMax(arr, len);
    int countArray[max+1];
    for (int i = 0; i <= max; i++) {
        countArray[i] = 0;
    }
    for (int i = 0; i < len; i++) {
        countArray[arr[i]]++;
    }
    int helper[max+1];
    for (int i = 0; i <= max; i++) {
        helper[i] = 0;
    }
    helper[0] = countArray[0];
    for (int i = 1; i <= max; i++) {
        helper[i] = countArray[i] + helper[i-1];
    }
    int sortedArray[len];
    for (int i = len-1; i >=0; i--) {
        sortedArray[helper[arr[i]] - 1] = arr[i];
        helper[arr[i]]--;
    }
    for (int i = 0; i < len; i++) {
        arr[i] = sortedArray[i];
    }
}