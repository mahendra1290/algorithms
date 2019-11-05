#include "bst.h"

void printInRangeFromBst(BinarySearchTree bst, int lower, int upper);

int main(){
    BinarySearchTree bst;
    for (int i = 0; i < 20; i++){
        bst.insert(val);
    }
    while (1){
        int lower, upper;
        cin >> lower >> upper;
        printInRangeFromBst(bst, lower, upper);
    }
    return 0;
}

void printInRangeFromBst(BinarySearchTree bst, int lower, int upper){
    vector <int> vect;
    bst.copyToVector(bst.root, vect);
    for (int i = 0; i < vect.size(); i++){
        int elem = vect[i];
        if (elem > lower && elem < upper){
            cout <<elem << " ";
        }
    }
    cout << endl;
}