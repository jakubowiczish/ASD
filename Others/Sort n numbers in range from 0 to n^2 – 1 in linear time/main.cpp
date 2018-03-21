#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;


void countSort(int arr[], int N, int exp);
void specialSort(int arr[], int N);
void setTable(int tab[], int N);
void printTable(int tab[], int N);

int main()
{
    int N = 20;
    int arr[N];
    setTable(arr,N);
    printTable(arr,N);
    specialSort(arr,N);
    printTable(arr,N);
    return 0;
}

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
