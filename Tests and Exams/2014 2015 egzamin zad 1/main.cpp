#include <iostream>
using namespace std;
/*
Prosze zaimplementowac funkcje scalajaca 2 posortowane listy(obie bez wartownika).
*/
struct Node{
    int val;
    Node *next;
};

void print_list(Node *first);
Node *merge_sorted_lists(Node *first1, Node *first2);
Node *addValue(Node *first, int value);
Node *deleteValue(Node *first, int value);
Node *create_node(int value);

int main()
{
    Node *first = create_node(1);
    for(int i=2; i < 50; i++){
        addValue(first,i);
    }
    print_list(first);
    Node *first2 = create_node(34);
    for(int i=35; i < 60; i++){
        addValue(first2,i);
    }
    print_list(first2);
    Node *first3 = merge_sorted_lists(first,first2);
    print_list(first3);
    return 0;
}

Node *merge_sorted_lists(Node *first1, Node *first2)
{
    if(first1 == nullptr) return first2;
    if(first2 == nullptr) return first1;

    Node *ret = new Node;
    ret -> next = nullptr;
    Node *ptr = ret;
    while(first1 != nullptr && first2 != nullptr){
        if(first1 -> val < first2 -> val){
            ptr -> next = first1;
            first1 = first1 -> next;
        }
        else{
            ptr -> next = first2;
            first2 = first2 -> next;
        }
        ptr = ptr -> next;
        ptr -> next = nullptr;
    }
    if(first1)
        ptr -> next = first1;
    if(first2)
        ptr -> next = first2;

    ptr = ret -> next;
    delete ret;
    return ptr;
}

Node *addValue(Node *first, int value)
{
    Node *wsk;
    if(first == nullptr){
        first = wsk = new Node;
    }
    else{
        wsk = first;
        while(wsk -> next != nullptr){
            wsk = wsk -> next;
        }
        wsk -> next = new Node;
        wsk = wsk -> next;
    }
    wsk -> val = value;
    wsk -> next = nullptr;
    return first;
}

Node *deleteValue(Node *first, int value)
{
    Node *wsk, *wsk2;
    if(first == nullptr){
        return first;
    }
    wsk = first;
    if(first -> val == value){
        first = first -> next;
        delete wsk;
    }
    else{
        while((wsk -> next != nullptr) and (wsk -> next -> val != value)){
            wsk = wsk -> next;
        }
        if(wsk -> next != nullptr){
            wsk2 = wsk -> next;
            wsk -> next = wsk2 -> next;
            delete wsk2;
        }
    }
    return first;
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
