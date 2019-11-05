#include <iostream>
#include <vector>
#include "bst.h"

using namespace std;

int main(){
    BinarySearchTree bst = BinarySearchTree();
    for (int i=0; i<10; i++){
        int elem;
        cin >> elem;
        //cout <<"max "<<bst.getMax() <<" and  min "<<bst.getMin()<<endl;
        bst.insert(elem);
        bst.display();
        cout << "kth max min" << endl;
        int min, max;
        cin >> max >> min;
        cout << " min " << bst.getMin(min) <<" max " <<bst.getMax(max);
    }
}
