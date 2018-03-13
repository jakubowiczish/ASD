#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int LeftChild(int i);
int RightChild(int i);
int Parent(int i);
void heapify(int tab[], int index);
void BuildHeap(int tab[], int N);
int HeapSort(int tab[], int N);
int ExtractMax(int tab[]);
void Insert(int tab[], int N, int key);
void printPriorityQueue(int tab[]);

int main()
{
    srand(time(NULL));
    int N = 15;
    int tab[N];
    tab[0] = 0; /// Size of array is stored in tab[0]

    for(int i = 0; i < N-1; i++){
        int val = rand() % 20;
        cout << "Inserting: " << val << endl;
        Insert(tab,N,val);
        printPriorityQueue(tab);
    }
    for(int i = 0; i < N-1; i++){
        int extracted = ExtractMax(tab);
        cout << "Extracting: " << extracted << endl;
        printPriorityQueue(tab);
    }
    return 0;
}

int LeftChild(int i)
{
    return i*2;
}
int RightChild(int i)
{
    return i*2 + 1;
}
int Parent(int i)
{
    return i/2;
}

void heapify(int tab[], int index)
{
    int size = tab[0];
    int largest = index;
    int left = LeftChild(index);
    int right = RightChild(index);

    if(left <= size and tab[left] > tab[largest])
        largest = left;
    if(right <= size and tab[right] > tab[largest])
        largest = right;

    if(largest != index){
        swap(tab[largest],tab[index]);
        heapify(tab,largest);
    }
}

void BuildHeap(int tab[], int N)
{
    tab[0] = N-1;
    for(int i = (N-1)/2; i >= 1; i--)
        heapify(tab,i);
}

int HeapSort(int tab[], int N)
{
    BuildHeap(tab,N);
    for(int i = N-1; i>1; i--){
        swap(tab[1],tab[i]);
        tab[0]--;
        heapify(tab,1);
    }
}

int ExtractMax(int tab[])
{
    if(tab[0] == 0)
        exit(1);
    int result = tab[1];
    tab[1] = tab[tab[0]];
    tab[tab[0]] = 0;
    tab[0]--;
    heapify(tab,1);
    return result;
}

void Insert(int tab[], int N, int key)
{
    if(tab[0] == N-1)
        exit(1); /// queue is full
    tab[++tab[0]] = key;
    int i = tab[0];

    while(i > 1 and tab[i] > tab[Parent(i)]){
        swap(tab[i],tab[Parent(i)]);
        i = Parent(i);
    }
}

void printPriorityQueue(int tab[])
{
    cout << "Priority Queue: " << endl;
    for(int i = 1; i <= tab[0]; i++){
        cout << tab[i] <<" ";
    }
    cout << endl;
}
