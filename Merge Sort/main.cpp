#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
void table_merge(int tab[], int N, int l1, int middle, int r2);
void merge_tab(int tab[], int N,int l, int middle, int r);
void merge_tab_v2(int tab[], int N,int l, int middle, int r);
void merge_tab_v3(int tab[], int N,int left, int mid, int right);
void MergeSort(int tab[], int N, int l, int r);
void MergeSort_v2(int tab[], int N, int left, int right);

void printTable(int tab[], int N);
void setTable(int tab[], int N);

int main()
{
    int N = 10;
    int tab[N];
    setTable(tab,N);
    printTable(tab,N);
    MergeSort(tab,N,0,N-1);
    printTable(tab,N);

    return 0;
}

void table_merge(int tab[], int N, int l1, int middle, int r2) /// 1 wersja procedury do scalania
{
    int tmp_tab[N];
    int i = l1, start = l1;

    int r1 = middle;
    int l2 = middle+1;

    while(l1<=r1 and l2<=r2)
        tab[l1] > tab[l2] ? tmp_tab[i++] = tab[l2++] : tmp_tab[i++] = tab[l1++];

    while(l1<=r1)
        tmp_tab[i++] = tab[l1++];
    while(l2<=r2)
        tmp_tab[i++] = tab[l2++];

    for(int j=start; j<=r2; j++) tab[j] = tmp_tab[j];
}

void merge_tab(int tab[], int N,int l, int middle, int r)
{
    int i,j,q;
    int tmp_tab[r-l+1];
    for(i=l; i <= r; i++)
        tmp_tab[i-l] = tab[i];
    i = 0;
    j = middle-l + 1;
    q = l;
    while(i <= middle-l && j <= r-l){
        if(tmp_tab[i] < tmp_tab[j])
            tab[q++] = tmp_tab[i++];
        else
            tab[q++] = tmp_tab[j++];
    }
    while(i <= middle-l)
        tab[q++] = tmp_tab[i++];
}

void merge_tab_v2(int tab[], int N,int l, int middle, int r)
{
    int i,j,q;
    int tmp_tab[N];
    for(i=l; i <= r; i++)
        tmp_tab[i] = tab[i];
    i = l;
    j = middle + 1;
    q = l;
    while(i <= middle && j <= r){
        if(tmp_tab[i] < tmp_tab[j])
            tab[q++] = tmp_tab[i++];
        else
            tab[q++] = tmp_tab[j++];
    }
    while(i <= middle)
        tab[q++] = tmp_tab[i++];
}

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
        merge_tab(tab,N,l,middle,r);
    }
}

void MergeSort_v2(int tab[], int N, int left, int right)
{
    if(left < right){
        int middle = (left + right)/2;
        MergeSort_v2(tab,N,left,middle);
        MergeSort_v2(tab,N,middle + 1,right);
        merge_tab_v3(tab,N,left,middle,right);
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
