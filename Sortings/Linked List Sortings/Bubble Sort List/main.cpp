#include <iostream>
using namespace std;

struct Node{
    int val;
    Node *next;
};

const int N = 20;

void BubbleSort(Node *first);
void swap(Node *a, Node *b);

void addNode(Node* list, int value);
Node *create_node(int value);
void print_list(Node *first);

int main()
{
    Node *first = new Node;
    first -> next = nullptr;
    first -> val = 0;

    for(int i=N; i >= 0; i--){
        addNode(first,i);
    }
    print_list(first);
    BubbleSort(first);
    print_list(first);
    delete first;
    return 0;
}

void BubbleSort(Node *first)
{
    Node *ptr = first;
    Node *lptr = nullptr;

    if(ptr == nullptr)
        return;

    int swapped;

    do{
        swapped = 0;
        ptr = first;
        while(ptr -> next != lptr)
        {
            if(ptr -> val > ptr -> next -> val){
                swap(ptr, ptr -> next);
                swapped = 1;
            }
            ptr = ptr -> next;
        }
        lptr = ptr;
    }while(swapped);
}

void swap(Node *a, Node *b)
{
    int temp = a -> val;
    a -> val = b -> val;
    b -> val = temp;
}

void addNode(Node* list, int value)
{
    while(list!=nullptr){
        if(list->next == nullptr){
            Node* newNode = new Node;
            newNode->val = value;
            newNode->next = nullptr;
            list->next = newNode;
            return;
        }
        list = list->next;
    }
}

Node *create_node(int value)
{
    Node *new_node = new Node;
    new_node->val = value;
    new_node->next = nullptr;
    return new_node;
}

void print_list(Node *first)
{
    while(first != nullptr) {
        cout << first->val << " ";
        first = first->next;
    }
    cout << endl;
}
