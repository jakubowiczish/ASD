#include <iostream>
#include <queue>

/// Binary Tree to Doubly Linked List and vice versa

struct Node{
    int val;
    Node *left, *right;
    Node(){};
    Node(int val, Node *left, Node *right){
        this -> val = val;
        this -> left = left;
        this -> right = right;
    }
};

Node *binaryTree2DoublyLinkedList_UTIL(Node *root);
Node *binaryTree2DoublyLinkedList(Node *root);
Node *doublyLinkedList2BinaryTree_UTIL(Node *&root, int leftV, int rightV);
Node *doublyLinkedList2BinaryTree(Node *root);
int sizeOfList(Node *root);
void printList(Node *node);
void inorderPrint(Node *root);
Node *insertToBinaryTree(Node *root, Node *node);
void insertToBinaryTree(Node *tmp, int value);
Node *newNode(int value);
void print2D_UTIL(Node *root, int space);
void print2D(Node *root);

int main() {
    Node *first = new Node{0, nullptr, nullptr};

    for(int i = 0; i < 10; i++)
        insertToBinaryTree(first,i);
    std::cout << "Inorder Binary Tree: " << std::endl;
    inorderPrint(first);
    std::cout << std::endl;

    std::cout << "Printing Tree 2D: " << std::endl;
    print2D(first);
    std::cout << std::endl;

    std::cout << "Binary Tree as Doubly Linked List: " << std::endl;
    Node *firstDLL = binaryTree2DoublyLinkedList(first);
    printList(firstDLL);
    std::cout << std::endl;


    std::cout << "Doubly Linked List again: " << std::endl;
    firstDLL = doublyLinkedList2BinaryTree(firstDLL);
    inorderPrint(firstDLL);
    return 0;
}

Node *binaryTree2DoublyLinkedList_UTIL(Node *root)
{
    if(!root) return nullptr;
    if(root -> left != nullptr){
        Node *left = binaryTree2DoublyLinkedList_UTIL(root -> left);
        while(left -> right != nullptr)
            left = left -> right;
        left -> right = root;
        root -> left = left;
    }

    if(root -> right != nullptr){
        Node *right = binaryTree2DoublyLinkedList_UTIL(root -> right);
        while(right -> left != nullptr)
            right = right -> left;
        right -> left = root;
        root -> right = right;
    }
    return root;
}

Node *binaryTree2DoublyLinkedList(Node *root)
{
    if(!root) return nullptr;

    root = binaryTree2DoublyLinkedList_UTIL(root);
    while(root -> left != nullptr)
        root = root -> left;

    return root;
}

Node *doublyLinkedList2BinaryTree_UTIL(Node *&root, int leftV, int rightV)
{
    if(leftV <= rightV){
        int medium = (leftV + rightV) / 2;
        Node *left = doublyLinkedList2BinaryTree_UTIL(root,leftV,medium-1);
        root -> left = left;
        Node *tmp = root;
        root = root -> right;
        tmp -> right = doublyLinkedList2BinaryTree_UTIL(root,medium+1,rightV);
        return tmp;
    }
    return nullptr;
}

Node *doublyLinkedList2BinaryTree(Node *root)
{
    int counter = sizeOfList(root);
    return doublyLinkedList2BinaryTree_UTIL(root,0,counter);
}

int sizeOfList(Node *root)
{
    int counter = 0;
    while(root -> right != nullptr) {
        ++counter;
        root = root -> right;
    }
    return counter;
}

void printList(Node *node)
{
    while(node != nullptr){
        std::cout << node -> val << " ";
        node = node -> right;
    }
}

void inorderPrint(Node *root)
{
    if(root == nullptr) return;
    inorderPrint(root -> left);
    std::cout << root -> val <<" ";
    inorderPrint(root -> right);
}

Node *insertToBinaryTree(Node *root, Node *node)
{
    if(!root) return node;
    if(node -> val < root -> val){
        root -> left = insertToBinaryTree(root -> left,node);
        return root;
    }
    else{
        node -> right = insertToBinaryTree(root -> right,node);
        return root;
    }
}

void insertToBinaryTree(Node *tmp, int value)
{
    std::queue<Node *> q;
    q.push(tmp);
    while(!q.empty()){
        Node *it = q.front();
        q.pop();

        if(!it -> left){
            it -> left = newNode(value);
            break;
        }
        else
            q.push(it -> left);

        if(!it -> right){
            it -> right = newNode(value);
            break;
        }
        else
            q.push(it -> right);
    }
}

Node *newNode(int value)
{
    Node *node = new Node;
    node -> val = value;
    node -> left = node -> right = nullptr;
    return (node);
}

void print2D_UTIL(Node *root, int space)
{
    const int CONST = 10;
    if(root == nullptr) return;
    space += CONST;

    print2D_UTIL(root -> right,space);
    std::cout << std::endl;
    for(int i = CONST; i < space; i++)
        std::cout << " ";
    std::cout << root -> val << std::endl;

    print2D_UTIL(root -> left,space);
}

void print2D(Node *root)
{
    print2D_UTIL(root,0);
}