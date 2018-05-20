#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Node{
    int val;
    Node *next;
};

void print_list(Node *first);
void addNodeBeginning_v2(Node *&first, int value);
Node* generateList(int N);

Node *partition(Node *head, Node *end, Node *&newHead, Node *&newEnd);
Node *quickSortRecur(Node *head, Node *end);
void QuickSortList(Node *&first);
Node *getTail(Node *first);

int main()
{
    Node *first = generateList(30);
    print_list(first);
    QuickSortList(first);
    print_list(first);
    return 0;
}

Node *partition(Node *head, Node *end, Node *&newHead, Node *&newEnd)
{
    Node *pivot = end;
    Node *prev = nullptr;
    Node *current = head;
    Node *tail = pivot;

    while(current != pivot){
        if(current -> val < pivot -> val){
            if(newHead == nullptr)
                newHead = current;
            prev = current;
            current = current -> next;
        }
        else{
            if(prev != nullptr)
                prev -> next = current -> next;
            Node *tmp = current -> next;
            current -> next = nullptr;
            tail -> next = current;
            tail = current;
            current = tmp;
        }
    }
    if(newHead == nullptr)
        newHead = pivot;
    newEnd = tail;
    return pivot;
}

Node *quickSortRecur(Node *head, Node *end)
{
    if(!head or head == end)
        return head;
    Node *newHead = nullptr, *newEnd = nullptr;
    Node *pivot = partition(head,end,newHead,newEnd);
    if(newHead != pivot){
        Node *tmp = newHead;
        while(tmp -> next != pivot)
            tmp = tmp -> next;
        tmp -> next = nullptr;
        newHead = quickSortRecur(newHead,tmp);
        tmp = getTail(newHead);
        tmp -> next = pivot;
    }
    pivot -> next = quickSortRecur(pivot -> next, newEnd);
    return newHead;
}

void QuickSortList(Node *&first)
{
    first = quickSortRecur(first,getTail(first));
    return;
}

Node *getTail(Node *first)
{
    while(first != nullptr and first -> next != nullptr){
        first = first -> next;
    }
    return first;
}

void addNodeBeginning_v2(Node *&first, int value)
{
    Node *new_node = new Node;
    new_node -> val = value;
    new_node -> next = first;
    first = new_node;
}

Node* generateList(int N)
{
    srand(time(NULL));
    Node *first = new Node;
    first -> next = nullptr;
    first -> val = rand()%100 + 1;
    for(int i = 0; i < N; i++){
        addNodeBeginning_v2(first,rand()%100 + 1);
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
