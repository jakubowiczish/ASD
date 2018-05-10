#include <iostream>
#include <queue>
/*
 *  Proszę zaimplementować algorytm, który mając na wejściu dwa drzewa BST
    (przechowujące liczby typu int; proszę zadeklarować odpowiednie struktury danych) zwraca nowe
    drzewo BST zawierające wyłącznie te liczby, które występują w dokładnie jednym z drzew (ale nie w
    obu). Algorytm powinien być jak najszybszy i wykorzystywać jak najmniej pamięci. Jaka jest złożoność
    czasowa zaproponowanego algorytmu? Co można powiedzieć o zrównoważeniu drzew tworzonych
    przez zaproponowany algorytm?
 */
struct BSTnode{
    BSTnode *left, *right, *parent;
    int val;
};

BSTnode *foundOnlyInOne(BSTnode *first, BSTnode *second);
bool find(BSTnode *root, int value);
void inorderPrint(BSTnode *root);
void addNode(BSTnode* &root, int value);
void freeBST(BSTnode* root);

int main() {
    BSTnode *first = nullptr;
    BSTnode *second = nullptr;

    for(int i = 0; i < 20; i++)
        addNode(first,i);

    std::cout << "First Tree: " << std::endl;
    inorderPrint(first);

    for(int i = 5; i < 25; i++)
        addNode(second,i);

    std::cout << "Second Tree: " << std::endl;
    inorderPrint(second);

    BSTnode *finalTree = foundOnlyInOne(first,second);
    std::cout << "Final Tree: " << std::endl;
    inorderPrint(finalTree);
    freeBST(first); freeBST(second); freeBST(finalTree);
    return 0;
}

BSTnode *foundOnlyInOne(BSTnode *first, BSTnode *second)
{
    std::queue<BSTnode * > Q;
    if(first != nullptr)
        Q.push(first);
    else return nullptr;

    BSTnode *finalTree = nullptr;
    while(!Q.empty()){
        BSTnode *it = Q.front();
        Q.pop();
        if(it -> left != nullptr)
            Q.push(it -> left);
        if(it -> right != nullptr)
            Q.push(it -> right);

        if(!find(second,it -> val))
            addNode(finalTree,it -> val);
    }

    if(second != nullptr)
        Q.push(second);
    else return nullptr;

    while(!Q.empty()){
        BSTnode *it = Q.front();
        Q.pop();
        if(it -> left != nullptr)
            Q.push(it -> left);
        if(it -> right != nullptr)
            Q.push(it -> right);

        if(!find(first,it -> val))
            addNode(finalTree,it -> val);
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
    tmp->left = tmp->right = tmp->parent = nullptr;

    if(root == nullptr){
        root = tmp;
        return;
    }

    BSTnode* tmpRoot = root;
    BSTnode* prevRoot = nullptr;


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

    if(prevRoot->val < value)
        prevRoot -> right = tmp;
    else{
        prevRoot -> left = tmp;
    }
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
