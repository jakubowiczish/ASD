#include <iostream>
using namespace std;

struct Node{
    int val;
    Node *next;
};

const int N = 20;

void addNode(Node* list, int value);
Node *create_node(int value);
void print_list(Node *first);

void SelectionSortList(Node *&first);

int main()
{
    Node *first = new Node;
    first -> next = nullptr;
    first -> val = 0;

    for(int i=N; i >= 0; i--){
        addNode(first,i);
    }
    print_list(first);
    SelectionSortList(first);
    print_list(first);
    delete first;
    return 0;
}

void SelectionSortList(Node *&first)
{
   Node *h = first;
    Node *i, *j;
    for(i = h; i != nullptr and i -> next != nullptr; i = i -> next){
        Node *min = i;
        for(j = i-> next; j != nullptr; j = j -> next){
            if(j -> val < min -> val)
                min = j;
        }
        if(min != i){
            int tmp;
            tmp = min -> val;
            min -> val = i -> val;
            i -> val = tmp;
        }
    }
    first = h;
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
