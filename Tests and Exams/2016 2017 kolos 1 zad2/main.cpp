#include <iostream>
#include <algorithm>
using namespace std;
/*
Prosz� zaimplementowa� funkcj�:
int SumBetween(int T[], int from, int to, int n);
Zadaniem tej funkcji jest obliczy� sum� liczb z n elementowej tablicy T, kt�re w posortowanej
tablicy znajdywa�yby si� na pozycjach o indeksach od from do to (w��cznie). Mo�na przyj��, �e
liczby w tablicy T s� parami r�ne (ale nie mo�na przyjmowa� �adnego innego rozk�adu danych).
Zaimplementowana funkcja powinna by� mo�liwie jak najszybsza. Prosz� oszacowa� jej z�o�ono��
czasow� (oraz bardzo kr�tko uzasadni� to oszacowanie).
*/

int partition(int A[], int p,int q)
{
    int x= A[p];
    int i=p;
    int j;
    for(j=p+1; j<q; j++)
    {
        if(A[j]<=x)
        {
            i=i+1;
            swap(A[i],A[j]);
        }

    }
    swap(A[i],A[p]);
    return i;
}
int find_element_sorted_value(int tab[], int p, int q, int k)
{
    if(q == p) return tab[p];
    int pivotIndex = partition(tab, p, q);
    if(pivotIndex == k) return tab[pivotIndex];
    else if(k < pivotIndex) return find_element_sorted_value(tab, 0, pivotIndex,k);
    else return find_element_sorted_value(tab,pivotIndex+1,q,k);
}

void printTable(int tab[], int n){
    for(int i = 0; i < n; i++) {
        cout << tab[i] << " " ;
    }
    cout << endl;
}
int SumBetween(int T[], int from, int to, int n)
{
    int fromValue = find_element_sorted_value(T, 0,n, from);
    int toValue = find_element_sorted_value(T,0, n, to);
    cout << "fromValue " << fromValue << endl;
    cout << "toValue " << toValue << endl;

    int sum = 0;
    for(int i=0; i < n; i++){
        if(T[i] >= fromValue && T[i] <= toValue) sum += T[i];
    }

    return sum;
}
int main() {
    int n = 8;
    int tab[n]={2,3,8,4,5,6,7,1};
    int sum = SumBetween(tab,3,5,n);
    cout << "Sum " << sum << endl;

    return 0;
}
