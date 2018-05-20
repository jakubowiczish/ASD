#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void CountingSort_v2(int A[], int N);
int find_maximum_element(int tab[], int N);
void printTable(int tab[], int N);
void setTable(int tab[], int N);

int main()
{
    int N = 10;
    int tab[N];
    setTable(tab,N);
    printTable(tab,N);
    CountingSort_v2(tab,N);
    printTable(tab,N);
    return 0;
}

void CountingSort_v2(int A[], int N)
{
    int *B = new int[N];
    int k = find_maximum_element(A,N) + 1;
    int *C = new int[k];

    for(int i = 0; i < k; i++)
        C[i] = 0;

    for(int i = 0; i < N; i++)
        C[A[i]]++;

    for(int i = 1; i < k; i++)
        C[i] = C[i]+C[i-1];

    for(int i = N-1; i>=0; i--)
        B[--C[A[i]]] = A[i];

    for(int i=0; i<N; i++)
        A[i] = B[i];

    delete [] B;
    delete [] C;
}

int find_maximum_element(int tab[], int N)
{
    int max = tab[0];
    for(int i = 1; i < N; i++)
        if(tab[i] > max)
            max = tab[i];
    return max;
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
