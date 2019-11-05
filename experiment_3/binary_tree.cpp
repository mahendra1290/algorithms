#include <iostream>

using namespace std;

struct node {
    int data;
    node *left;
    node *right;
};

node *createNode(int key);

class BinarySearchTree {
    private:
        node *root;
        void inOrderTraversal(node *root);
    public:
        BinarySearchTree();
        void insert(int val);
        void inOrderTraversal();


};

BinarySearchTree::BinarySearchTree() {
    root = NULL;
}

void BinarySearchTree::insert(int val) {
    if (root == NULL) {
        root = createNode(val);
    }
    else {
        node *temp = root;
        while (temp != NULL) {
            if (val < temp->data && temp->left == NULL) {
                temp->left = createNode(val);
                    break;
                }
                else {
                    temp = temp->left;
                }
            }
            else {
                if (temp->right == NULL) {
                    temp->right = createNode(val);
                    break;
                }
                else {
                    temp = temp->right;
                }
            }
        }
    }
}

void BinarySearchTree::inOrderTraversal(node *root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        cout << root->data << " ";
        inOrderTraversal(root->right);
    }
}

void BinarySearchTree::inOrderTraversal() {
    inOrderTraversal(root);
    cout << endl;
}

//create and return a binary node
node *createNode(int key) {
    node *newNode = new node;
    newNode->data = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int main() {
    BinarySearchTree bst;
    for (int i = 0; i < 10; i++) {
        int val;
        cin >> val;
        bst.insert(val);
    }
    bst.inOrderTraversal();
    bst.inOrderTraversal()
    return 0;
}