#include <iostream>
#include <ctime>
#include <cstdlib>

/// Merge two SkipLists

const int INF = INT16_MAX;
const int MAX_LEVEL = 4;

struct SLnode {
    int val;
    int level;
    SLnode **next;
};

struct SkipList{
    SLnode *first;
    SLnode *last;
};

void initializeSkipList(SkipList &list);
inline double myRand();
inline int getHeight();
void insertToSkipList(SkipList list, int value);
SkipList mergeTwoSkipLists(SkipList A, SkipList B);
void printSkipList(SkipList list);

int main() {

    srand((unsigned)time(nullptr));
    SkipList first, second;
    first = second = {nullptr, nullptr};
    ///initialization
    initializeSkipList(first); initializeSkipList(second);

    for(int i = 0; i < 10; i++)
        insertToSkipList(first,i);

    for(int i = 5; i < 15; i++)
        insertToSkipList(second,i);

    std::cout << "First SkipList: " << std::endl;
    printSkipList(first);
    std::cout << "Second SkipList: " << std::endl;
    printSkipList(second);

    SkipList finalSkipList = mergeTwoSkipLists(first,second);
    std::cout << "Final SkipList: " << std::endl;
    printSkipList(finalSkipList);
    getchar();
    return 0;
}

void initializeSkipList(SkipList &list)
{
    SLnode *tmp = new SLnode;
    tmp -> val = -INF;
    tmp -> level = MAX_LEVEL;
    tmp -> next = new SLnode*[MAX_LEVEL];

    SLnode *temp = new SLnode;
    temp -> val = INF;
    temp -> level = MAX_LEVEL;
    temp -> next = nullptr;

    for(int i = MAX_LEVEL - 1; i >= 0; i--){
        tmp -> next[i] = temp;
    }

    list.first = tmp;
    list.last = temp;
}

/// some helping functions
/// myRand() returns real number in the range of [0,1]
inline double myRand()
{
    return (double)(double)rand() / (double) RAND_MAX;
}

inline int getHeight()
{
    double lim = 1/2;
    int height = 1;
    while(height < MAX_LEVEL and myRand() < lim)
        height++;
    return height;
}

void insertToSkipList(SkipList list, int value)
{
    SLnode *it = list.first;
    int height = getHeight();
    SLnode *newNode = new SLnode;
    newNode -> val = value;
    newNode -> next = new SLnode*[height];
    newNode -> level = height;

    for(int i = MAX_LEVEL - 1; i >= 0; i--){
        while(it -> next[i] -> val < value)
            it = it -> next[i];
        if(i < height){
            newNode -> next[i] = it -> next[i];
            it -> next[i] = newNode;
        }
    }
}

SkipList mergeTwoSkipLists(SkipList A, SkipList B)
{
    SkipList Final = {nullptr, nullptr};
    initializeSkipList(Final);

    SLnode *a = A.first;
    SLnode *b = B.first;
    SLnode *f = Final.first;
    SLnode **arr = new SLnode*[MAX_LEVEL];

    for(int i = 0; i < MAX_LEVEL; i++)
        arr[i] = f;

    for(int i = MAX_LEVEL - 1; i >= 0; i--){
        while(a -> next[i] -> val != INF or b -> next[i] -> val != INF){
            SLnode *it;
            if(a -> next[i] -> val < b -> next[i] -> val){
                it = a -> next[i];
                a -> next[i] = a -> next[i] -> next[i];
            }else{
                it = b -> next[i];
                b -> next[i] = b -> next[i] -> next[i];
            }

            it -> next[i] = arr[i] -> next[i];
            arr[i] -> next[i] = it;
            arr[i] = it;
        }
    }
    delete[] arr;

    return Final;
}

void printSkipList(SkipList list)
{
    SLnode *it = list.first;
    while(it -> next[0] -> val != INF){
        std::cout << it -> next[0] -> val << " ";
        it = it -> next[0];
    }
    std::cout << std::endl;
}