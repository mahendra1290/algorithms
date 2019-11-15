#include <bits/stdc++.h>

using namespace std;

void radixSort(int *arr, int len, int digits);

void countingSort(int arr[], int len, int digit);

int getNthDigit(int number, int d);

int main() {
    int len;
    cin >> len;
    int arr[len];
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }
    radixSort(arr, len, 3);
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
}

void radixSort(int *arr, int len, int digits) {
    for (int i = 1; i <= digits; i++) {
        countingSort(arr, len, i);
    }
}

void countingSort(int arr[], int len, int digit) {
    int hash[10];
    memset(hash, 0, sizeof(int)*(10));
    struct Number{
        int num;
        int digit;
    };
    Number numberArr[len];
    for (int i = 0; i < len; i++) {
        numberArr[i].num = arr[i];
        numberArr[i].digit = getNthDigit(arr[i], digit);
    }
    for (int i = 0; i < len; i++) {
        hash[numberArr[i].digit] += 1;
    }
    for (int i = 1; i < 10; i++) {
        hash[i] += hash[i - 1];
    }
    for (int i = len - 1; i >= 0; i--) {
        arr[hash[numberArr[i].digit] - 1] = numberArr[i].num;
        hash[numberArr[i].digit] -= 1;
    }
}

int getNthDigit(int number, int d) {
    int ten = pow(10, d);
    return (number % ten) / (ten / 10);
}