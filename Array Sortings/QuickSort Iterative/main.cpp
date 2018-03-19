#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int MAX = 20;

struct stos{
    int t[MAX + 1];
    int size;
};

void init(stos &st) {st.size = 0;}
void push(stos &st, int el){st.t[st.size++] = el;}
int pop(stos &st) {return st.t[--st.size];}
bool empty(stos &st) {return st.size == 0;}

int partition(int arr[], int l, int r);
void QuickSortIterative(int arr[], int l, int r);
void printTable(int tab[], int N);
void setTable(int tab[], int N);

int main()
{
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
