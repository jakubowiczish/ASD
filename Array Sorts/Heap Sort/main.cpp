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

void printTable(int tab[], int N);
void setTable(int tab[], int N);

int main()
{
    int N = 10;
    int tab[N];
    setTable(tab,N);
    printTable(tab,N);
    HeapSort(tab,N);
    printTable(tab,N);

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

void printTable(int tab[], int N)
{
    for(int i=0; i < N; i++){
        cout << tab[i] <<" ";
    }
    cout << endl;
}

void setTable(int tab[], int N)
{
    srand(time( NULL ));
    for (int i=0; i < N; i++){
        tab[i] = rand()% 50 + 1;
    }
}
