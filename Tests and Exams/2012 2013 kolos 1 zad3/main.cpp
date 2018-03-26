#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
/*
Proszê napisaæ funkcjê bool possible( char* u, char* v, char* w ), która zwraca prawdê
jeœli z liter s³ów u i v da siê u³o¿yæ s³owo w (nie jest konieczne wykorzystanie wszystkich liter)
oraz fa³sz w przeciwnym wypadku. Mo¿na za³o¿yæ, ¿e w i v sk³adaj¹ siê wy³¹cznie z ma³ych liter
alfabetu ³aciñskiego. Proszê krótko uzasadniæ wybór zaimplementowanego algorytmu.
*/
const int N = 10;
bool possible(char *u, char *v, char *w);

int main()
{
    char u[N];
    char v[N];
    char w[N];
    cout << "Podaj pierwsze slowo: " << endl;
    gets(u);
    cout << "Podaj drugie slowo: " << endl;
    gets(v);
    cout << "Podaj trzecie slowo: " << endl;
    gets(w);
    if(possible(u,v,w))
        cout << "Mozliwe! " << endl;
    else
        cout << "Niemozliwe " << endl;
    return 0;
}

bool possible(char *u, char *v, char *w)
{
    int len;
    int A[26];
    for(int i=0; i < 26; i++)
        A[i] = 0;

    len = strlen(u);
    for(int i=0; i < len; i++)
        A[(int)u[i]-97]++;

    len = strlen(v);
    for(int i=0; i < len; i++)
        A[(int)v[i]-97]++;

    len = strlen(w);
    for(int i=0; i < len; i++)
        A[(int)w[i]-97]--; /// wazne, odejmujemy znaki ktore wystapily w "u" i "v", jesli nie wystapily, ktoras komorka w tablicy bedzie ujemna

    for(int i=0; i < 26; i++)
        if(A[i] < 0)
            return false;
    return true;
}
