#include <bits/stdc++.h>

using namespace std;

vector<int> getMaximumSubArray(int *arr, int len);

int main() {
    int len = 0;
    cin >> len;
    int arr[len];
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }
    getMaximumSubArray(arr, len);
    return 0;
}

vector<int> getMaximumSubArray(int *arr, int len) {
    int maxEndingHere = 0;
    int maxSoFar = 0;
    int positiveMax = 0;
    int start = 0;
    int last = 0;
    for (int i = 0; i < len; i++) {
        maxEndingHere += arr[i];
        if (maxEndingHere < 0) {
            maxEndingHere = 0;
            start = i + 1;
        }
        else if (maxEndingHere > maxSoFar) {
            maxSoFar = maxEndingHere;
            last = i;
        }
    }
    vector<int> ans;
    return ans;
}