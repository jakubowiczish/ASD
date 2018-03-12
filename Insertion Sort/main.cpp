#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
void InsertionSort(int tab[], int N);
void printTable(int tab[], int N);
void setTable(int tab[], int N);

int main()
{
    int N = 10;
    int tab[N];
    setTable(tab,N);
    printTable(tab,N);
    InsertionSort(tab,N);
    printTable(tab,N);

    return 0;
}

void InsertionSort(int tab[], int N)
{
    for(int i=1; i < N; i++){
        int value = tab[i];
        int j = i-1;
        while(j >= 0 && tab[j] > value){
            tab[j+1] = tab[j];
            j--;
        }
        tab[j+1] = value;
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
