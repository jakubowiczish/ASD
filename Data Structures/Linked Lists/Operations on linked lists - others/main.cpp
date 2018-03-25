#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Node{
    int val;
    Node *next;
};
void reverseList(Node *&first);
void reverseList_v2(Node *&first);
Node *reverseList_v3(Node *first);
void deleteFromBeginning(Node *&first);
void deleteFromEnd(Node *&first);
void DeleteDuplicates(Node *first);
void DeleteDuplicates_v2(Node *first);
Node *create_node(int value);
Node* generateList(int N);
void print_list(Node *first);
int getSizeOfList(Node *first);
Node *MergeThreeLists(Node *list1, Node *list2, Node *list3);
void SplitList_v1(Node *list, Node *&list1, Node *&list2);
Node *SplitList_v2(Node *list);
Node *MergeLists_v1(Node *first1, Node *first2);
Node *MergeLists_v2(Node *list1, Node *list2);
Node *MergeLists_v3(Node *&list1, Node *&list2);
void MergeSortList(Node *&list);
Node *MergeSortList2(Node *list1);
void addNodeBeginning(Node *&list, int value);
Node *AddListToList_v1(Node *list1, Node *list2);
void add_at_beginning_v1(Node *&first, Node *new_node);

int main()
{
    Node *first = generateList(15);
    print_list(first);
    reverseList(first);
    print_list(first);
    cout << getSizeOfList(first) << endl;
    return 0;
}

void addNodeBeginning(Node *&list, int value)
{
    Node *newNode = new Node;
    newNode->val = value;
    newNode->next = list;
    list = newNode;
}

Node *AddListToList_v1(Node *list1, Node *list2)
{
    while(list2 != nullptr){
        list1 -> next = list2;
        list2 = list2 -> next;
        list1 = list1 -> next;
    }
    return list1;
}

void reverseList(Node *&first)
{
    Node *p = nullptr;
    Node *tmp = nullptr;
    if(first != nullptr){
        tmp = first;
        while(tmp -> next != nullptr){
            p = tmp -> next;
            tmp -> next = p -> next;
            p -> next = first;
            first = p;
        }
    }
}

void reverseList_v2(Node *&first)
{
    if(first == nullptr) return;
    Node *current = nullptr;
    Node *tmp = first;
    while(tmp -> next != nullptr){
        current = tmp -> next;
        tmp -> next = current -> next;
        current -> next = first;
        first = current;
    }
}

Node *reverseList_v3(Node *first)
{
    if(first == nullptr)
        return nullptr;
    Node *new_list = first;
    Node *tmp;
    first = first -> next;
    new_list -> next = nullptr;
    while(first != nullptr){
        tmp = first;
        first = first -> next;
        add_at_beginning_v1(new_list,tmp);
    }
    return new_list;
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

int getSizeOfList(Node *first)
{
    int counter = 0;
    while(first != nullptr){
        counter++;
        first = first -> next;
    }
    return counter;
}

void DeleteDuplicates(Node *first)
{
    Node *it;
    Node *tmp;
    Node *head = first;
    while(head != nullptr){
        it = head;
        while(it -> next != nullptr){
            if(it -> next -> val == head -> val){
                tmp = it -> next;
                it -> next = tmp -> next;
                delete tmp;
            }
            else
                it = it -> next;
        }
        head = head -> next;
    }
}

void DeleteDuplicates_v2(Node *first)
{
    for(Node *p = first; p -> next != nullptr; p = p -> next){
        for(Node *q = p; q -> next != nullptr; ){
            if(p -> val == q -> next -> val){
                Node *tmp = q -> next;
                q -> next = tmp -> next;
                delete tmp;
            }
            else
                q = q -> next;
        }
    }
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

Node *create_node(int value)
{
    Node *new_node = new Node;
    new_node->val = value;
    new_node->next = nullptr;
    return new_node;
}

void deleteFromBeginning(Node *&first)
{
    if(first == nullptr)
        return;
    Node *tmp = first;
    first = first -> next;
    delete tmp;
}

void deleteFromEnd(Node *&first)
{
    Node *tmp = first;
    if(tmp != nullptr){
        if(tmp -> next != nullptr){
            while(tmp -> next -> next != nullptr)
                tmp = tmp -> next;

            delete tmp -> next;
            tmp -> next = nullptr;
        }
        else{
            delete tmp;
            first = nullptr;
        }
    }
}

Node *MergeThreeLists(Node *list1, Node *list2, Node *list3)
{
    Node *guardian = new Node;
    guardian -> next = nullptr;
    Node *current = guardian;
    current = AddListToList_v1(current,list1);
    current = AddListToList_v1(current,list2);
    current = AddListToList_v1(current,list3);

    return guardian -> next;
}

void SplitList_v1(Node *list, Node *&list1, Node *&list2)
{
    Node *tmp1 = list;
    Node *tmp2 = list;

    while(tmp1)
    {
        tmp1 = tmp1->next;
        if(tmp1)
        {
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
    }
    list2 = tmp2;

    list1 = list;
    while(list->next != list2) list = list->next;
    list->next = nullptr;
}

// another splitting function

Node *SplitList_v2(Node *list)
{
    Node *slow = list;
    Node *fast = list;
    while(fast -> next != nullptr and fast -> next -> next != nullptr){
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    Node *secondList = slow -> next;
    slow -> next = nullptr;
    return secondList;
}

void SplitList_v3(Node *list, Node *&list1, Node *&list2)
{
    Node *slow = list;
    Node *fast = list;
    while(fast -> next != nullptr and fast -> next -> next != nullptr){
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    list1 = slow -> next;
    slow -> next = nullptr;
    list2 = list;
}

Node *MergeLists_v1(Node *first1, Node *first2)
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

// another merging function

Node *MergeLists_v2(Node *list1, Node *list2)
{
    Node *first = new Node;
    Node *current = first;
    while(list1 != nullptr or list2 != nullptr){
        if(list1 != nullptr and list2 == nullptr){
            current -> next = list1;
            current = current -> next;
            list1 = list1 -> next;
        }
        else if(list1 == nullptr and list2 != nullptr){
            current -> next = list2;
            current = current -> next;
            list2 = list2 -> next;
        }
        else{
            if(list1 -> val < list2 -> val){
                current -> next = list1;
                current = current -> next;
                list1 = list1 -> next;
            }
            else{
                current -> next = list2;
                current = current -> next;
                list2 = list2 -> next;
            }
        }
    }
    return first -> next;
}

Node *MergeLists_v3(Node *&list1, Node *&list2)
{
    Node *result = nullptr;
    if(list1 == nullptr)
        return list2;
    else if(list2 == nullptr)
        return list1;

    if(list1 -> val < list2 -> val){
        result = list1;
        result -> next = MergeLists_v3(list1 -> next,list2);
    }
    else{
        result = list2;
        result -> next = MergeLists_v3(list1,list2 -> next);
    }
    return result;
}

Node *MergeLists_v4(Node *list1, Node *list2)
{
    Node *first = new Node;
    Node *current = first;
    while(list1 != nullptr or list2 != nullptr){
        if(list1 != nullptr and list2 == nullptr){
            current -> next = list1;
            return first -> next;
        }
        else if(list1 == nullptr and list2 != nullptr){
            current -> next = list2;
            return first -> next;
        }
        else{
            if(list1 -> val < list2 -> val){
                current -> next = list1;
                current = current -> next;
                list1 = list1 -> next;
            }
            else{
                current -> next = list2;
                current = current -> next;
                list2 = list2 -> next;
            }
        }
    }
    return first -> next;
}

void MergeSortList(Node *&list)
{
    if(list == nullptr or list->next == nullptr) return;
    Node *list1, *list2;
    SplitList_v3(list, list1, list2);
    MergeSortList(list1);
    MergeSortList(list2);
    list = MergeLists_v4(list1, list2);
}

Node *MergeSortList2(Node *list1)
{
    if(list1 == nullptr and list1 -> next == nullptr){
        Node *list2 = SplitList_v2(list1);
        Node *sortedList1 = MergeSortList2(list1);
        Node *sortedList2 = MergeSortList2(list2);
        return MergeLists_v2(sortedList1, sortedList2);
    }
    return list1;
}
