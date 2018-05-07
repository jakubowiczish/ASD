#include <iostream>
#include <queue>
#include <vector>

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

bool isLeaf(Node *node);
void inorderPrint(Node *root);
Node *newNode(int value);
void insertToBinaryTree(Node *tmp, int value);
void printRootToLeafPaths_UTIL(Node *node, std::vector<int> &path);
void printRootToLeafPaths(Node *node);
void print2D_UTIL(Node *root, int space);
void print2D(Node *root);
void freeBinaryTree(Node* root);

int main() {
    int SIZE = 15;
    Node *tree = new Node{1, nullptr, nullptr};

    for(int i = 0; i < SIZE; i++)
        insertToBinaryTree(tree,i);
    std::cout << "Inorder Print: " << std::endl;
    inorderPrint(tree);
    std::cout << std::endl;
    std::cout << "Printing 2D: " << std::endl;
    print2D(tree);
    std::cout << "All root to leaf paths: " << std::endl;
    printRootToLeafPaths(tree);
    freeBinaryTree(tree);
    return 0;
}

bool isLeaf(Node *node)
{
    return (node -> left == nullptr and node -> right == nullptr);
}

void freeBinaryTree(Node* root)
{
    if(root == nullptr){
        return;
    }
    if(root->left != nullptr){
        freeBinaryTree(root->left);
    }
    if(root->right != nullptr){
        freeBinaryTree(root->right);
    }
    delete root;
    return;
}

void inorderPrint(Node *root)
{
    if(root == nullptr) return;
    inorderPrint(root -> left);
    std::cout << root -> val <<" ";
    inorderPrint(root -> right);
}

Node *newNode(int value)
{
    Node *tmp = new Node;
    tmp -> val = value;
    tmp -> left = tmp -> right = nullptr;
    return tmp;
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

void printRootToLeafPaths_UTIL(Node *node, std::vector<int> &path)
{
    if(node == nullptr) return;
    path.push_back(node -> val);

    if(isLeaf(node)){
        for(int data: path)
            std::cout << data << " ";
        std::cout << std::endl;
    }

    printRootToLeafPaths_UTIL(node -> left, path);
    printRootToLeafPaths_UTIL(node -> right,path);
    path.pop_back();
}

void printRootToLeafPaths(Node *node)
{
    std::vector<int> path;
    printRootToLeafPaths_UTIL(node,path);
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