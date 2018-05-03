#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
/// based on https://github.com/kaszperro
/*
Zadanie 1. Dana jest struktura opisujaca liste jednokierunkowa przechowujaca liczby typu double:
struct Node { Node* next; double value; };
Prosze zaimlementowac funkcje Node* sortList( Node* L ), która sortuje liste wejsciowa w kolejnosci
nierosnacej i zwraca wskaznik na element, który po posortowaniu zostal glowa tej listy (wejsciowa lista nie
ma wartownika). Funkcja powinna byc mozliwie jak najszybsza (wiadomo, ze liczby w wejsciowej liscie
zostaly wygenerowane zgodnie z rozkladem jednostajnym na przedziale (0,4)).
*/
struct Node{
    double val;
    Node *next;
    Node(){
    }
    Node(double val, Node* next){
        this->val = val;
        this->next = next;
    }
};

void print_list(Node *first);
void addToSortedList(Node *&first, Node *new_node);
int b_num(double val, double min, double width);
Node *bucketSortList(Node *list);
double rand_num(double min, double max);
Node * create_random_list(int n, double min, double max);

int main()
{
    Node *first = create_random_list(10, 0, 4);
    print_list(first);
    cout << endl << endl;
    first = bucketSortList(first);
    print_list(first);
    return 0;
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

int b_num(double val, double min, double width)
{
    return (val - min)/width;
}

Node *bucketSortList(Node *list)
{
    int m = 100; ///number of buckets
    double max = 4;
    double min = 0;
    double width = (max - min)/m;
    Node **buckets = new Node*[m];
    for(int i = 0; i < m; i++) buckets[i] = nullptr;

    while(list){
        int i = b_num(list -> val, min, width);
        Node *tmp = list -> next;
        addToSortedList(buckets[i],list);
        list = tmp;
    }
    Node *ptr = nullptr;
    for(int i = m-1; i >= 0; i--){ /// starting from last buckets - those with highest values
        if(buckets[i] == nullptr) continue;
        if(ptr == nullptr)
            list = buckets[i];
        else
            ptr -> next = buckets[i];
        ptr = buckets[i];
        while(ptr -> next)
            ptr = ptr -> next;
    }

    delete [] buckets;
    return list;
}

double rand_num(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

Node * create_random_list(int n, double min, double max)
{
    srand((unsigned)time(NULL));
    Node *bg = new Node(rand_num(min,max),nullptr);
    Node *pt = bg;
    for(int i = 1; i < n; ++i) {
        Node *my = new Node(rand_num(min,max),nullptr);
        pt->next = my;
        pt = pt->next;
    }
    return bg;
}

void print_list(Node *first)
{
    while(first != nullptr) {
        cout << first->val << " ";
        first = first->next;
    }
    cout << endl;
}
