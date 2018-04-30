#include <iostream>

/// Prosze zaimplementowac funkcje int countInterval(BST *T, int a, int b)
/// ktora oblicza ile liczb z danego przedzialu domknietego znajduje sie w drzewie T

struct BSTnode{
    BSTnode *left, *right, *parent;
    int val;
};

void addNode(BSTnode* &root, int value);
void countIntervalRecursive(BSTnode *root, int a, int b, int &sum);
int countInterval(BSTnode *root, int a, int b);
void inorderPrint(BSTnode *root);

int main() {
    BSTnode *root = nullptr;
    for(int i = 0; i < 30; i++)
        addNode(root,i);

    int a,b;
    inorderPrint(root);
    std::cout << "Insert a" << std::endl;
    std::cin >> a;
    std::cout << "Insert b" << std::endl;
    std::cin >> b;
    std::cout << "Amount of numbers between " << a << " and " << b << " is: ";
    std::cout << countInterval(root,28,31) << std::endl;
    return 0;
}

void countIntervalRecursive(BSTnode *root, int a, int b, int &sum)
{
    if(root != nullptr){
        countIntervalRecursive(root -> left,a,b,sum);
        if(a <= root -> val and root -> val <= b)
            sum++;
        if(root -> val > b) return;
        countIntervalRecursive(root -> right,a,b,sum);
    }
}

int countInterval(BSTnode *root, int a, int b)
{
    int sum = 0;
    countIntervalRecursive(root,a,b,sum);
    return sum;
}

void inorderPrint(BSTnode *root)
{
    if(root != nullptr){
        inorderPrint(root -> left);
        std::cout << root ->val << std::endl;
        inorderPrint(root -> right);
    }
}

void addNode(BSTnode* &root, int value)
{
    BSTnode* tmp = new BSTnode;
    tmp->val=value;
    tmp->left = nullptr;
    tmp->right = nullptr;
    tmp->parent = nullptr;

    // If root is empty?
    if(root == nullptr){
        root = tmp;
        return;
    }

    BSTnode* tmpRoot = root;
    BSTnode* prevRoot = nullptr;

    // Find the father of a new node
    while(tmpRoot != nullptr){
        if(tmpRoot -> val < tmp -> val){
            prevRoot = tmpRoot;
            tmpRoot = tmpRoot -> right;
        }
        else{
            prevRoot = tmpRoot;
            tmpRoot = tmpRoot -> left;
        }
    }

    // Insert the new node
    if(prevRoot->val < value)
        prevRoot -> right = tmp;
    else{
        prevRoot -> left = tmp;
    }
    tmp -> parent = prevRoot;
}
