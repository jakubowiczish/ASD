#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int MAX = 20;

struct stos{
    int t[MAX + 1];
    int size;
};

void countSort(int arr[], int N, int exp);
void specialSort(int arr[], int N);
void setTable(int tab[], int N);
void printTable(int tab[], int N);

void init(stos &st) {st.size = 0;}
void push(stos &st, int el){st.t[st.size++] = el;}
int pop(stos &st) {return st.t[--st.size];}
bool empty(stos &st) {return st.size == 0;}

int partition(int arr[], int l, int r);
void QuickSortIterative(int arr[], int l, int r);

int main()
{
    /// TASK NR 1
    int N = 20;
    int arr[N];
    cout <<"Task number 1: " << endl << endl;
    setTable(arr,N);
    printTable(arr,N);
    specialSort(arr,N);
    printTable(arr,N);

    cout <<"Task number 2: " << endl << endl;
    int tab[MAX];
    setTable(tab,MAX);
    printTable(tab,MAX);
    QuickSortIterative(tab,0,MAX-1);
    printTable(tab,MAX);
    return 0;
}

int partition(int arr[], int l, int r)
{
    int x = arr[r];
    int i = (l-1);
    for(int j = l; j < r; j++){
        if(arr[j] < x){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[r]);
    return i+1;
}

void QuickSortIterative(int arr[], int l, int r)
{
    stos st;
    init(st);

    push(st,l);
    push(st,r);

    while(st.size > 0){
        r = pop(st);
        l = pop(st);
        int q = partition(arr,l,r);

        if(q-1 > l){
            push(st,l);
            push(st,q-1);
        }
        if(q+1 < r){
            push(st,q+1);
            push(st,r);
        }
    }
}

/// Sort n numbers in range from 0 to n^2 – 1 in linear time
void countSort(int arr[], int N, int exp)
{
    int resultArr[N]; /// array storing result
    int i, countingArr[N];
    for(int i = 0; i < N; i++)
        countingArr[i] = 0;
    for(i = 0; i < N; i++)
        countingArr[ (arr[i]/exp)%N ]++;

    for(i = 1; i < N; i++)
        countingArr[i] += countingArr[i-1];

    for(i = N - 1; i >= 0; i--){
        resultArr[countingArr[ (arr[i]/exp)%N ] -1 ] = arr[i];
        countingArr[ (arr[i]/exp)%N ]--;
    }
    for(i = 0; i < N; i++)
        arr[i] = resultArr[i];
}

void specialSort(int arr[], int N)
{
    countSort(arr,N,1);
    countSort(arr,N,N);
}


void printTable(int tab[], int N)
{
    for(int i=0; i < N; i++){
        cout << tab[i] <<" ";
    }
    cout << endl;
}

void setTable(int tab[], int N) /// range N*N - 1
{
    srand(time( NULL ));
    for (int i=0; i < N; i++){
        tab[i] = rand()%(N*N-1);
    }
}
