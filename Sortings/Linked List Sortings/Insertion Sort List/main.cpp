#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Node{
    int val;
    Node *next;
};

void addToSortedList(Node *&first, Node *new_node);
void InsertionSortList(Node *&first);
void print_list(Node *first);
void addNodeBeginning(Node *&list, int value);
Node* generateList(int N);

int main()
{
    int N = 30;
    Node *first = generateList(N);
    print_list(first);
    InsertionSortList(first);
    print_list(first);
    return 0;
}

void addNodeBeginning(Node *&list, int value)
{
    Node *newNode = new Node;
    newNode->val = value;
    newNode->next = list;
    list = newNode;
}

Node* generateList(int N)
{
    srand(time(NULL));
    Node *first = new Node;
    first -> next = nullptr;
    first -> val = rand()%100 + 1;
    for(int i = 0; i < N; i++){
        addNodeBeginning(first,rand()%100 + 1);
    }
    return first;
}

void print_list(Node *first)
{
    while(first != nullptr) {
        cout << first->val << " ";
        first = first->next;
    }
    cout << endl;
}

void InsertionSortList(Node *&first)
{
    Node *result = nullptr;
    Node *current = first;
    while(current != nullptr){
        Node *tmp = current -> next;
        addToSortedList(result,current);
        current = tmp;
    }
    first = result;
}

void addToSortedList(Node *&first, Node *new_node)
{
    if(first == nullptr or first -> val >= new_node -> val){
        new_node -> next = first;
        first = new_node;
    }
    else{
        Node *current = first;
        while(current -> next != nullptr and current -> next -> val < new_node -> val){
            current = current -> next;
        }
        new_node -> next = current -> next;
        current -> next = new_node;
    }
}
