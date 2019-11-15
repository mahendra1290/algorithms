#include <bits/stdc++.h>

using namespace std;

void bucketSort(double arr[], int len);

int main() {
    int len;
    cin >> len;
    double arr[len];
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }
    bucketSort(arr, len);
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
}

void bucketSort(double arr[], int len) {
    vector<double> b[len];
    for (int i = 0; i < len; i++) {
        int index = len * arr[i];
        b[index].push_back(arr[i]);
    }
    for (int i = 0; i < len; i++) {
        sort(b[i].begin(), b[i].end());
    }
    int k = 0;
    for (int i = 0; i < len; i++) {
        for (double d : b[i]) {
            arr[k++] = d;
        }
    }
}