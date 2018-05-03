#include <iostream>
#include <queue>
/// Prosze zaimplementowa algorytm, ktory majac na wejciu dwa drzewa BST
/// (przechowujce liczby typu int; prosz zadeklarowa odpowiednie struktury danych) zwraca nowe
/// drzewo BST, zawierajce wycznie te liczby, ktre wystpuj w obu drzewach. Algorytm powinien
/// by jak najszybszy i wykorzystywa jak najmniej pamici. Jaka jest zoono zaproponowanego
/// algorytmu? Co mona powiedzie o zrwnowaeniu drzew tworzonych przez zaproponowany algorytm?


struct BSTnode{
    BSTnode *left, *right, *parent;
    int val;
};

BSTnode *foundInBoth(BSTnode *firstTree, BSTnode *secondTree);
bool find(BSTnode *root, int value);
BSTnode *makeNode(int val);
void inorderPrint(BSTnode *root);
void addNode(BSTnode* &root, int value);
void free_BST(BSTnode* root);
BSTnode *min(BSTnode *root);
BSTnode *max(BSTnode *root);
BSTnode *succ(BSTnode *node);
BSTnode *prev(BSTnode *node);
BSTnode *search(BSTnode* root, int val);

int main() {
    BSTnode *first = nullptr;
    BSTnode *second = nullptr;

    for(int i = 0; i < 10; i++)
        addNode(first,i);

    std::cout << "First Tree: " << std::endl;
    inorderPrint(first);

    for(int i = 2; i < 15; i++)
        addNode(second,i);
    std::cout << "Second Tree: " << std::endl;
    inorderPrint(second);

    BSTnode *final = foundInBoth(first,second);
    std::cout << "Final Tree: " << std::endl;
    inorderPrint(final);
    return 0;
}

BSTnode *foundInBoth(BSTnode *firstTree, BSTnode *secondTree)
{
    std::queue< BSTnode * > Q;
    if(firstTree != nullptr)
        Q.push(firstTree);
    else return nullptr;

    BSTnode *finalTree = nullptr;

    while(!Q.empty()){
        BSTnode *it = Q.front();
        Q.pop();
        if(it -> left != nullptr)
            Q.push(it -> left);
        if(it -> right != nullptr)
            Q.push(it -> right);

        if(find(secondTree,it -> val)){
            ///std::cout << it -> val << std::endl;
            addNode(finalTree,it -> val);
        }
        else delete it;
    }
    return finalTree;
}

bool find(BSTnode *root, int value)
{
    BSTnode *p = root;
    while(p != nullptr){
        if(p -> val == value)
            return true;
        else if(p -> val > value)
            p = p -> left;
        else
            p = p -> right;
    }
    return false;
}
BSTnode *makeNode(int val)
{
    BSTnode *newNode = new BSTnode;
    newNode -> val = val;
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


void free_BST(BSTnode* root)
{
    if(root == nullptr){
        return;
    }
    if(root->left != nullptr){
        free_BST(root->left);
    }
    if(root->right != nullptr){
        free_BST(root->right);
    }
    delete root;
    return;
}

BSTnode *min(BSTnode *root)
{
    while(root -> left != nullptr)
        root = root -> left;
    return root;
}

BSTnode *max(BSTnode *root)
{
    while(root -> right != nullptr)
        root = root -> right;
    return root;
}

BSTnode *succ(BSTnode *node)
{
    if(node->right != nullptr)
        return min(node->right);

    else{
        BSTnode* tmp = node -> parent;
        while(tmp != nullptr && tmp -> left != node){
            node = tmp;
            tmp = tmp -> parent;
        }
        return tmp;
    }
}

BSTnode *prev(BSTnode *node)
{
    if(node -> left != nullptr)
        return max(node -> left);
    else{
        BSTnode *tmp = node -> parent;
        while(tmp != nullptr && tmp -> right != node){
            node = tmp;
            tmp = tmp -> parent;
        }
        return tmp;
    }
}
BSTnode *search(BSTnode* root, int val)
{
    // Base Cases: root is null or key is present at root
    if(root == nullptr || root->val == val){
        return root;
    }
    // Key is greater than root's key
    if(root->val < val){
        return search(root -> right, val);
    }
    // Key is smaller than root's key
    return search(root -> left, val);
}