#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <random>
using namespace std;

void BubbleSort(int tab[], int N);
void InsertionSort(int tab[], int N);
void SelectionSort(int tab[], int N);

int partition(int tab[], int N, int l, int r);
void QuickSort(int tab[], int N, int l, int r);
void QuickSortIterative(int tab[], int N, int l, int r);

void merge_tab_v3(int tab[], int N,int left, int mid, int right);
void MergeSort(int tab[], int N, int l, int r);

int LeftChild(int i);
int RightChild(int i);
int Parent(int i);
void heapify(int tab[], int index);
void BuildHeap(int tab[], int N);
int HeapSort(int tab[], int N);

void countSort(int arr[], int N, int exp);
void radix_sort(int arr[], int N);
void counting_sort(int A[],int N, int k);

void printTable(int tab[], int N);
void setTable(int tab[], int N);

int main() {
    int N = 10000;
    int tab[N];
    setTable(tab,N);
    //printTable(tab,N);

    int helpingTab[N];

    for(int i = 0; i < N; i++){
        helpingTab[i] = tab[i];
    }

    /// QUICKSORT
    for(int i = 0; i < N; i++){
        tab[i] = helpingTab[i];
    }
    auto start = std::chrono::system_clock::now();
    QuickSort(tab,N,0,N-1);
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "QuickSort: " << elapsed_seconds.count() << "s\n";

    /// SELECTION SORT
    for(int i = 0; i < N; i++){
        tab[i] = helpingTab[i];
    }
    auto start2 = std::chrono::system_clock::now();
    SelectionSort(tab,N);
    auto end2 = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds2 = end2-start2;
    std::cout << "SelectionSort " << elapsed_seconds2.count() << "s\n";

    /// BUBBLE SORT
    for(int i = 0; i < N; i++){
        tab[i] = helpingTab[i];
    }
    auto start3 = std::chrono::system_clock::now();
    BubbleSort(tab,N);
    auto end3 = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds3 = end3-start3;
    std::cout << "BubbleSort " << elapsed_seconds3.count() << "s\n";

    ///MERGE SORT
    for(int i = 0; i < N; i++){
        tab[i] = helpingTab[i];
    }

    auto start4 = std::chrono::system_clock::now();
    MergeSort(tab,N,0,N-1);
    auto end4 = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds4 = end4-start4;
    std::cout << "MergeSort " << elapsed_seconds4.count() << "s\n";


    /// INSERTION SORT
    for(int i = 0; i < N; i++){
        tab[i] = helpingTab[i];
    }
    auto start5 = std::chrono::system_clock::now();
    InsertionSort(tab,N);
    auto end5 = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds5 = end5-start5;
    std::cout << "InsertionSort " << elapsed_seconds5.count() << "s\n";

    /// HEAPSORT
    for(int i = 0; i < N; i++){
        tab[i] = helpingTab[i];
    }
    auto start6 = std::chrono::system_clock::now();
    HeapSort(tab,N);
    auto end6 = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds6 = end6-start6;
    std::cout << "HeapSort " << elapsed_seconds6.count() << "s\n";

    /// QUICKSORT ITERATIVE
    for(int i = 0; i < N; i++){
        tab[i] = helpingTab[i];
    }
    auto start7 = std::chrono::system_clock::now();
    QuickSortIterative(tab,N,0,N-1);
    auto end7 = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds7 = end7-start7;
    std::cout << "QuickSortIterative " << elapsed_seconds7.count() << "s\n";

    /// RADIX SORT
    for(int i = 0; i < N; i++){
        tab[i] = helpingTab[i];
    }
    auto start8 = std::chrono::system_clock::now();
    radix_sort(tab,N);
    auto end8 = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds8 = end8-start8;
    std::cout << "RadixSort " << elapsed_seconds8.count() << "s\n";

    /// COUNTING SORT
    for(int i = 0; i < N; i++){
        tab[i] = helpingTab[i];
    }
    auto start9 = std::chrono::system_clock::now();
    counting_sort(tab,N,100000001);
    auto end9 = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds9 = end9-start9;
    std::cout << "CountingSort " << elapsed_seconds9.count() << "s\n";


    return 0;
}
/// END OF MAIN


/***************QUICK SORT*********************/

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

/******************BUBBLE SORT*************************/

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

/****************INSERTION SORT****************************/

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

/*************SELECTION SORT*******************************/

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

/****************MERGE SORT*****************************/

void merge_tab_v3(int tab[], int N,int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for(int i=0; i < n1; i++)
        L[i] = tab[left + i];
    for(int i=0; i < n2; i++)
        R[i] = tab[mid + 1 + i];
    int i = 0;
    int j = 0;
    int k = left;
    while(i < n1 and j < n2)
    {
        if(L[i] < R[j])
            tab[k] = L[i++];
        else
            tab[k] = R[j++];
        k++;
    }
    while(i < n1)
        tab[k++] = L[i++];
    while(j < n2)
        tab[k++] = R[j++];
}

void MergeSort(int tab[], int N, int l, int r)
{
    if(l < r){
        int middle = (l+r)/2;
        MergeSort(tab,N,l,middle);
        MergeSort(tab,N,middle+1,r);
        merge_tab_v3(tab,N,l,middle,r);
    }
}

/*************************HEAP SORT********************************/

int LeftChild(int i)
{
    return i*2;
}
int RightChild(int i)
{
    return i*2 + 1;
}
int Parent(int i)
{
    return i/2;
}

void heapify(int tab[], int index)
{
    int size = tab[0];
    int largest = index;
    int left = LeftChild(index);
    int right = RightChild(index);

    if(left <= size and tab[left] > tab[largest])
        largest = left;
    if(right <= size and tab[right] > tab[largest])
        largest = right;

    if(largest != index){
        swap(tab[largest],tab[index]);
        heapify(tab,largest);
    }
}

void BuildHeap(int tab[], int N)
{
    tab[0] = N-1;
    for(int i = (N-1)/2; i >= 1; i--)
        heapify(tab,i);
}

int HeapSort(int tab[], int N)
{
    BuildHeap(tab,N);
    for(int i = N-1; i>1; i--){
        swap(tab[1],tab[i]);
        tab[0]--;
        heapify(tab,1);
    }
}

/// COUNTING AND RADIX SORT

void countSort(int arr[], int N, int exp)
{
    int *output=new int[N];
    int i, count[10] = {0};
    for (i = 0; i < N; i++)
        count[ (arr[i]/exp)%10 ]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = N - 1; i >= 0; i--)
    {
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }

    for (i = 0; i < N; i++)
        arr[i] = output[i];

    delete [] output;
}

void radix_sort(int arr[], int N)
{
    int m = 100000000;

    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(arr, N, exp);
}
void counting_sort(int A[],int N, int k)
{
    int *B=new int[N];
    int *C=new int[k];

    for(int i=0; i<k; i++) C[i]=0;
    for(int i=0;i<N;i++) C[A[i]]++;
    for(int i=1; i<k; i++) C[i]=C[i]+C[i-1];
    for(int i=N-1; i>=0; i--) {
        B[--C[A[i]]]=A[i];
    }
    for(int i=0; i<N; i++) A[i]=B[i];
    delete [] B;
    delete [] C;
}
/// POZOSTALE FUNKCJE
void printTable(int tab[], int N)
{
    for(int i=0; i < N; i++){
        cout << tab[i] <<" ";
    }
    cout << endl;
}

void setTable(int tab[], int N)
{
    //srand(time( NULL ));
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0,100000000);

    for (int i=0; i < N; i++){
        tab[i] = dis(gen);
    }
}
