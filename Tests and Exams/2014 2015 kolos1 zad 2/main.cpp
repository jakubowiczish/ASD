#include <iostream>
using namespace std;
/*
Dane s¹ nastêpuj¹ce struktury:
struct Node { Node* next; int val; };
struct TwoLists { Node* even; Node* odd; };
Napisaæ funkcjê: TwoLists split(Node* list);
Funkcja rozdziela listê na dwie: jedn¹ zawieraj¹c¹ liczby parzyste i drug¹ zawieraj¹c¹ liczby
nieparzyste. Listy nie zawieraj¹ wartowników
*/
struct Node{
    int val;
    Node *next;
};

struct TwoLists{
    Node *even;
    Node *odd;
};

void print_list(Node *first);
Node *addValue(Node *first, int value);
Node *deleteValue(Node *first, int value);
Node *create_node(int value);
TwoLists splitlist(Node *first);

int main()
{
    Node *first = create_node(1);
    for(int i=2; i < 60; i++){
        first = addValue(first,i);
    }
    print_list(first);
    splitlist(first);
    return 0;
}

TwoLists splitlist(Node *first)
{
    TwoLists S;
    S.even = nullptr;
    S.odd = nullptr;

    while(first != nullptr)
    {
        if((first -> val)%2 == 0)
        {
            Node *tmp = first;
            first = first -> next;
            tmp -> next = S.even;
            S.even = tmp;
        }
        else{
            Node *tmp = first;
            first = first -> next;
            tmp -> next = S.odd;
            S.odd = tmp;
        }
    }
    cout << "ODD: " << endl;
    while(S.odd != nullptr){
        cout << S.odd -> val <<" ";
        S.odd = S.odd -> next;
    }
    cout << endl;
    cout << "EVEN: " << endl;
    while(S.even != nullptr){
        cout << S.even -> val <<" ";
        S.even = S.even -> next;
    }
    cout << endl;
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
