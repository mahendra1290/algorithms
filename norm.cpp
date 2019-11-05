#include <iostream>

using namespace std;

int main() {
    int test;
    int p;
    int prices[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 };
    cin >> test;
    while (test--) {
        cin >> p;
        int numberOfMenus = 0;
        for (int i = 11; i >= 0; i--) {
            int count = p/prices[i];
            numberOfMenus += count;
            p -= (count * prices[i]);
        }
        cout << numberOfMenus << endl;
    }
    return 0;
}