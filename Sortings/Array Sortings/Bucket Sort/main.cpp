#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void setTable(int tab[], int N);
void printTable(int tab[], int N);
int find_maximum_element(int tab[], int N);
int find_minimum_element(int tab[], int N);
void BucketSort(int arr[], int N);

int main()
{
    int N = 30;
    int arr[N];
    setTable(arr,N);
    printTable(arr,N);
    BucketSort(arr,N);
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

int find_minimum_element(int tab[], int N)
{
    int min = tab[0];
    for(int i = 1; i < N; i++)
        if(tab[i] < min)
            min = tab[i];
    return min;
}
void BucketSort(int arr[], int N)
{
    int MAX = find_maximum_element(arr,N);
    int MIN = find_minimum_element(arr,N);
    int SIZE = MAX - MIN + 1;
    int buckets[SIZE];

    for(int i = MIN; i <= MAX; i++)
        buckets[i-MIN] = 0;
    for(int i = 0; i < N; i++)
        ++buckets[arr[i]-MIN];

    int j = 0;
    for(int i = MIN; i <= MAX; i++)
        while(buckets[i-MIN]--)
            arr[j++] = i;
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
