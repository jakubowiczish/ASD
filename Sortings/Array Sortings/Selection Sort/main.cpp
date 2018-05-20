#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
void SelectionSort(int tab[], int N);
void printTable(int tab[], int N);
void setTable(int tab[], int N);

int main()
{
    int N = 10;
    int tab[N];
    setTable(tab,N);
    printTable(tab,N);
    SelectionSort(tab,N);
    printTable(tab,N);

    return 0;
}

void SelectionSort(int tab[], int N)
{
    int min_index;
    for(int i=0; i < N; i++){
        min_index = i;
        for(int j=i; j < N; j++){
            if(tab[j] < tab[min_index])
                min_index = j;
        }
        swap(tab[i],tab[min_index]);
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
