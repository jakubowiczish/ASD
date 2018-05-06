#include <iostream>
#include <iomanip>
/*
 * Drzewo BST jest opisane przez strukturę
 * struct BST{
 *      BST *left, *right;
 *      int value;
 * };
 *
 * Proszę zaimplementować funkcję double average(BST *T), która oblicza
 * średnią wartość elementów w drzewie T;
 */
struct BSTnode{
    int val;
    BSTnode *right;
    BSTnode *left;
    BSTnode *parent;
};

void addToBST(BSTnode *&root, int value);
void freeBST(BSTnode* root);
void inorderPrint(BSTnode *root);
int sumWholeBST(BSTnode *T);
int amountOfNodesInBST(BSTnode *T);
double average(BSTnode *T);
double average_v2_UTIL(BSTnode *T, double &sum, double &amount);
double average_v2(BSTnode *T);

int main() {
    int AMOUNT = 10;
    BSTnode *mine = nullptr;
    for(int i = 0; i < AMOUNT; i++){
        addToBST(mine,i);
    }
    inorderPrint(mine);
    std::cout << "Average value of node in BST: " << std::endl;
    std::cout << average(mine) << std::endl;
    std::cout << average_v2(mine) << std::endl;
    return 0;
}


void addToBST(BSTnode *&root, int value)
{
    BSTnode *tmp = new BSTnode;
    tmp -> val = value;
    tmp -> left = tmp -> right = tmp -> parent = nullptr;

    if(root == nullptr){
        root = tmp;
        return;
    }

    BSTnode *tmpRoot = root;
    BSTnode *prevRoot = nullptr;

    while(tmpRoot != nullptr){
        if(tmpRoot -> val < tmp -> val){
            prevRoot = tmpRoot;
            tmpRoot = tmpRoot -> right;
        }else{
            prevRoot = tmpRoot;
            tmpRoot = tmpRoot -> left;
        }
    }
    /// inserting
    if(prevRoot -> val < value)
        prevRoot -> right = tmp;
    else
        prevRoot -> left = tmp;

    tmp -> parent = prevRoot;
}

void freeBST(BSTnode* root)
{
    if(root == nullptr){
        return;
    }
    if(root->left != nullptr){
        freeBST(root->left);
    }
    if(root->right != nullptr){
        freeBST(root->right);
    }
    delete root;
    return;
}

void inorderPrint(BSTnode *root)
{
    if(root == nullptr) return;
    inorderPrint(root -> left);
    std::cout << root -> val << ' ';
    inorderPrint(root -> right);
}

int sumWholeBST(BSTnode *T)
{
    if(T == nullptr) return 0;
    if(T -> left == nullptr and T -> right == nullptr)
        return T -> val;
    else
        return T -> val + sumWholeBST(T -> left) + sumWholeBST(T -> right);
}

int amountOfNodesInBST(BSTnode *T)
{
    if(T == nullptr) return 0;
    if(T -> left == nullptr and T -> right == nullptr)
        return 1;
    else
        return 1 + amountOfNodesInBST(T -> left) + amountOfNodesInBST(T -> right);
}

double average(BSTnode *T)
{
    double sumOfAllNodes = sumWholeBST(T);
    double amountOfAllNodes = amountOfNodesInBST(T);
    return (sumOfAllNodes / amountOfAllNodes);
}

double average_v2_UTIL(BSTnode *T, double &sum, double &amount)
{
    if(T == nullptr) return 0;
    average_v2_UTIL(T -> left,sum,amount);
    average_v2_UTIL(T -> right,sum,amount);
    if(T != nullptr){
        sum += T -> val;
        ++amount;
    }

    if(T -> parent == nullptr) return (sum / amount);
}

double average_v2(BSTnode *T)
{
    double sum = 0;
    double amount = 0;
    return average_v2_UTIL(T,sum,amount);
}