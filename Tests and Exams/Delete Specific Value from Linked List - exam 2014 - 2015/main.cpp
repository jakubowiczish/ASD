#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

/// funkcja usuwajaca z listy elementy o wartosci x

struct Node{
    int val;
    Node *next;
};

Node* generateList(int N);
void print_list(Node *first);
void deleteSpecificValue(Node *first, int x);
void addNodeBeginning(Node *&list, int value);

int main()
{
    Node *first = new Node;
    first -> next = nullptr;
    for(int i = 0; i < 20; i++){
        addNodeBeginning(first,i);
    }
    print_list(first);
    deleteSpecificValue(first,18);
    deleteSpecificValue(first,3);
    print_list(first);
    return 0;
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

void addNodeBeginning(Node *&list, int value)
{
    Node *newNode = new Node;
    newNode->val = value;
    newNode->next = list;
    list = newNode;
}

void print_list(Node *first)
{
    while(first != nullptr) {
        cout << first->val << " ";
        first = first->next;
    }
    cout << endl;
}

void deleteSpecificValue(Node *first, int x)
{
    if(first -> val == x){
        Node *p = first;
        if(p != nullptr){
            first = p -> next;
            delete p;
        }
    }
    else{
        Node *p = first;
        while(p -> next -> val != x)
            p = p -> next;
        Node *tmp = p -> next;
        p -> next = tmp -> next;
        delete tmp;
    }
}

