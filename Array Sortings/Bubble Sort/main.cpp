#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
void BubbleSort(int tab[], int N);
void printTable(int tab[], int N);
void setTable(int tab[], int N);

int main()
{
    int N = 10;
    int tab[N];
    setTable(tab,N);
    printTable(tab,N);
    BubbleSort(tab,N);
    printTable(tab,N);

    return 0;
}

void BubbleSort(int tab[], int N)
{
    bool stop;
    for (int i=0; i < N; i++){
        stop = false;
        for (int j=0; j < N-1; j++){
            if (tab[j] > tab[j+1]){
                swap(tab[j],tab[j+1]);
                stop = true;
            }
        }
        if(!stop) break;
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
