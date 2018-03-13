#include <iostream>
using namespace std;

struct Node{
    int val;
    Node *next;
};

const int N = 20;

void SplitList_v1(Node *list, Node *&list1, Node *&list2);
Node *SplitList_v2(Node *list);
void SplitList_v3(Node *list, Node *&list1, Node *&list2);
Node *MergeLists_v1(Node *first1, Node *first2);
Node *MergeLists_v2(Node *list1, Node *list2);
Node *MergeLists_v3(Node *&list1, Node *&list2);
Node *MergeLists_v4(Node *list1, Node *list2);
int getSizeOfList(Node *first);
void MergeSortList(Node *&list);
Node *MergeSortList2(Node *list1);

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
    MergeSortList(first);
    print_list(first);
    delete first;
    return 0;
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
// another merging function

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
    list = MergeLists_v3(list1, list2);
}

Node *MergeSortList2(Node *list1)
{
    if(list1 != nullptr and list1 -> next != nullptr){
        Node *list2 = SplitList_v2(list1);
        Node *sortedList1 = MergeSortList2(list1);
        Node *sortedList2 = MergeSortList2(list2);
        return MergeLists_v2(sortedList1, sortedList2);
    }
    return list1;
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
