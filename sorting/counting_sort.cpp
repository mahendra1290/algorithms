#include <bits/stdc++.h>

using namespace std;

void countingSort(int arr[], int len, int range);

int main() {
    int len;
    cin >> len;
    int arr[len];
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }
    countingSort(arr, len, 10);
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
}

void countingSort(int arr[], int len, int range) {
    int hash[range + 1];
    memset(hash, 0, sizeof(int)*(range+1));
    for (int i = 0; i < len; i++) {
        hash[arr[i]] += 1;
    }
    int k = 0;
    int bArr[len];
    for (int i = 1; i <= range; i++) {
        hash[i] = hash[i] + hash[i - 1];
    }
    for (int i = len - 1; i >= 0; i--) {
        bArr[hash[arr[i]] - 1] = arr[i];
        hash[arr[i]] -= 1;
    }
    for (int i = 0; i < len; i++) {
        arr[i] = bArr[i];
    }

}