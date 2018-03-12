#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
int partition(int tab[], int N, int l, int r);
void QuickSort(int tab[], int N, int l, int r);
void QuickSortIterative(int tab[], int N, int l, int r);
void printTable(int tab[], int N);
void setTable(int tab[], int N);

int main()
{
    int N = 10;
    int tab[N];
    setTable(tab,N);
    printTable(tab,N);
    QuickSort(tab,N,0,N-1);
    printTable(tab,N);

    return 0;
}

int partition(int tab[], int N, int l, int r)
{
    int x = tab[r];
    int i; int j = l;
    for(i=l; i < r; i++){
        if(tab[i] <= x){
            swap(tab[i],tab[j]);
            j++;
        }
    }
    swap(tab[j],tab[r]);
    return j;
}

void QuickSort(int tab[], int N, int l, int r)
{
    if(l < r){
        int x = partition(tab,N,l,r);
        QuickSort(tab,N,l,x-1);
        QuickSort(tab,N,x+1,r);
    }
}

void QuickSortIterative(int tab[], int N, int l, int r)
{
    int stack[r-l+1];
    int top = -1;
    stack[++top] = l;
    stack[++top] = r;

    /// Keep popping from stack while is not empty
    while(top >= 0){
        r = stack[top--];
        l = stack[top--];
        int p = partition(tab,N,l,r);

        /// If there are elements on left side of pivot,
        /// then push left side to stack
        if(p-1 > l){
            stack[++top] = l;
            stack[++top] = p-1;
        }
        /// If there are elements on right side of pivot,
        /// then push right side to stack
        if(p+1 < r){
            stack[++top] = p+1;
            stack[++top] = r;
        }
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
