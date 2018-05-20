#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int find_maximum_element(int tab[], int N);
void CountSort(int arr[], int N, int exp);
void RadixSort(int arr[], int N);

void printTable(int tab[], int N);
void setTable(int tab[], int N);

int main()
{
    int N = 20;
    int arr[N];
    setTable(arr,N);
    printTable(arr,N);
    RadixSort(arr,N);
    printTable(arr,N);
    return 0;
}

int find_maximum_element(int tab[], int N)
{
    int max = tab[0];
    for(int i = 1; i < N; i++)
        if(tab[i] > max)
            max = tab[i];
    return max;
}

void CountSort(int arr[], int N, int exp)
{
    int output[N];
    int count[N] = {0};
    for(int i = 0; i < N; i++)
        count[ (arr[i]/exp)%10 ]++;
    for(int i = 1; i < N; i++)
        count[i] += count[i-1];
    for(int i = N-1; i >= 0; i--){
        output[ count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }
    for(int i = 0; i < N; i++)
        arr[i] = output[i];
}

void RadixSort(int arr[], int N)
{
    int m = find_maximum_element(arr,N);
    for(int exp = 1; m/exp > 0; exp *= 10)
        CountSort(arr,N,exp);
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
