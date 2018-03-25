#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Node{
    int val;
    Node *next;
};

void add_at_beginning_v1(Node *&first, Node *new_node);
Node *add_at_beginning_v2(Node *first, Node *new_node);
void addToSortedList(Node *&first, Node *new_node);
void addAtSpecificPosition_v1(Node *&first, Node *new_node, int position);
Node *addAtSpecificPosition_v2(Node *first, Node *new_node, int position);
void addNodeBeginning(Node *&list, int value);
void addNodeBeginning_v2(Node *&first, int value);
void addNodeEnd(Node* list, int value);
void add_at_end(Node *&first, Node *new_node);
Node *AddListToList_v1(Node *list1, Node *list2);
Node *AddListToList_v2(Node *list1, Node *list2);
Node *AddListToList_v3(Node *list1, Node *list2);
void AddListToList_v4(Node *list1, Node *list2);

Node *create_node(int value);
Node* generateList(int N);
void print_list(Node *first);

int main()
{
    Node *first = generateList(20);
    print_list(first);
    ///adding
    addNodeBeginning(first,1);
    addNodeBeginning_v2(first,2);
    add_at_beginning_v1(first,create_node(5));
    first = add_at_beginning_v2(first,create_node(6));
    addNodeEnd(first,7);
    add_at_end(first,create_node(9));

    print_list(first);

    Node *first2 = generateList(10);
    print_list(first2);
    Node *first3 = AddListToList_v2(first,first2);
    print_list(first);

    return 0;
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

void add_at_beginning_v1(Node *&first, Node *new_node)
{
    if(first == nullptr) {
        first = new_node;
        return;
    }

    new_node->next = first;
    first = new_node;
}

Node *add_at_beginning_v2(Node *first, Node *new_node)
{
    if(first == nullptr) return new_node;

    new_node->next = first;
    return new_node;
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

void addAtSpecificPosition_v1(Node *&first, Node *new_node, int position)
{
    if(position == 0 or first == nullptr){
        add_at_beginning_v1(first,new_node);
        return;
    }
    Node *tmp = first;
    while(position > 1 and tmp -> next != nullptr){
        position--;
        tmp = tmp -> next;
    }
    new_node -> next = tmp -> next;
    tmp -> next = new_node;
}

Node *addAtSpecificPosition_v2(Node *first, Node *new_node, int position)
{
    if(position == 0 or first == nullptr){
        first = add_at_beginning_v2(first,new_node);
        return first;
    }
    Node *tmp = first;
    while(position > 1 and tmp -> next != nullptr){
        position--;
        tmp = tmp -> next;
    }
    new_node -> next = tmp -> next;
    tmp -> next = new_node;

    return first;
}

void addNodeBeginning(Node *&list, int value)
{
    Node *newNode = new Node;
    newNode->val = value;
    newNode->next = list;
    list = newNode;
}

void addNodeBeginning_v2(Node *&first, int value)
{
    Node *new_node = new Node;
    new_node -> val = value;
    new_node -> next = first;
    first = new_node;
}

void addNodeEnd(Node* list, int value)
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

void add_at_end(Node *&first, Node *new_node)
{
    if(first == nullptr) {
        first = new_node;
        return;
    }

    Node *tmp_node = first;
    while(tmp_node->next != nullptr) tmp_node = tmp_node->next;
    tmp_node->next = new_node;
}
/// list1 - final list
Node *AddListToList_v1(Node *list1, Node *list2)
{
    while(list2 != nullptr){
        list1 -> next = list2;
        list2 = list2 -> next;
        list1 = list1 -> next;
    }
    return list1;
}

/// list1 - final list

Node *AddListToList_v2(Node *list1, Node *list2)
{
    while(list1 -> next != nullptr){
        list1 = list1 -> next;
    }
    list1 -> next = list2;
    return list1;
}

/// returns pointer to a new list
Node *AddListToList_v3(Node *list1, Node *list2)
{
    Node *newList = list1;
    while(list1 -> next != nullptr){
        list1 = list1 -> next;
    }
    list1 -> next = list2;
    return newList;
}
/// list1 - final list
void AddListToList_v4(Node *list1, Node *list2)
{
    while(list1 -> next != nullptr){
        list1 = list1 -> next;
    }
    list1 -> next = list2;
}
