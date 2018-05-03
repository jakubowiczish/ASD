#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
/// based on git.iiet.pl
/*
 * Dana jest struktura danych opisujaca tablicę haszującą, która przechowuje liczby typu int indeksowane napisami:

struct HT {
    string  *key;   // tablica na klucze danych
    int     *data;  // tablica na dane
    bool    *free;  // pola wolne czy zajete
    int     size;   // rozmiar tablicyu
};
    Tablica wykorzystuje funkcję haszującą int hash(string key, int size), która zwraca pozycję w tablicy,
    na której powinny się znaleźć dane o kluczu key.
    Stosowanie jest liniowe rozwiązywanie kolizji. Niestety możliwe, że tablica zawiera błędne dane.
    Proszę zaimplementować funkcję bool checkHT(HT *ht), która sprawdza czy dla każdego klucza umieszczonego w tablicy faktycznie
    możliwe jest jego odszukanie standardowym algorytmem używanym w tablicach haszujących z liniowym rozwiązywaniem konfliktów.
 */

struct HT {
    std::string *key;   // tablica na klucze danych
    int *data;  // tablica na dane
    bool *free;  // pola wolne czy zajete
    int size;   // rozmiar tablicy
};

void initializeHashTable(HT *ht, int n);
int hashFunction(std::string s, int n);
void addToHashTable(HT *ht, std::string data);
int findData(HT *ht, std::string data);
bool checkHTworse(HT *ht);
bool checkHT(HT *ht);


int main() {
    int SIZE = 14;
    std::string keys[] = {"Jakub Dybczak","Piotr Szczygiel","Mateusz Kubicki","Jacek Kusnierz"};
    HT *ht = new HT;
    std::cout << "Data: " << std::endl;
    initializeHashTable(ht,SIZE);
    for(int i = 0; i < 4; i++){
        addToHashTable(ht,keys[i]);
        std::cout << keys[i] << std::endl;
    }

    if(checkHTworse(ht))
        std::cout << "HashTable is neat and tidy" << std::endl;
    else
        std::cout << "HashTable is faulty" << std::endl;

    if(checkHT(ht))
        std::cout << "HashTable is neat and tidy" << std::endl;
    else
        std::cout << "HashTable is faulty" << std::endl;

    ht -> free[3] = false;
    ht -> key[3] = "Give me some error please";  /// Correct hash for this key is 4 + shift
    std::cout << ht -> key[3] << std::endl;
    if(checkHTworse(ht))
        std::cout << "HashTable is neat and tidy" << std::endl;
    else
        std::cout << "HashTable is faulty" << std::endl;

    if(checkHT(ht))
        std::cout << "HashTable is neat and tidy" << std::endl;
    else
        std::cout << "HashTable is faulty" << std::endl;

    return 0;
}

void initializeHashTable(HT *ht, int n)
{
    ht -> size = n;
    ht -> key = new std::string[n];
    ht -> data = new int[n];
    ht -> free = new bool[n];

    for(int i = 0; i < n; i++)
        ht -> free[i] = true; /// initialize all fields to be true (unoccupied)
}

int hashFunction(std::string s, int n) /// supposedly good hashFunction
{
    int result = 0;
    for(int i = 0; i < s.length(); ++i) {
        result += s[i] * pow(31, i);
    }
    return result % n;
}

void addToHashTable(HT *ht, std::string data)
{
    int hash = hashFunction(data,ht -> size);
    if(ht -> free[hash]){
        ht -> free[hash] = false;
        ht -> key[hash] = data;
        return;
    }
    if(!(ht -> free[hash])){
        int start = hash;
        hash++;
        while(hash != start){
            if(ht -> free){
                ht -> free[hash] = false;
                ht -> key[hash] = data;
                return;
            }
            hash = (hash + 1)%(ht -> size);
        }
    }
}

int findData(HT *ht, std::string data)
{
    int hash = hashFunction(data,ht -> size);
    if(ht -> free[hash]) return -1; /// not found data
    while(!(ht -> free[hash])){
        if(ht -> key[hash] == data)
            return hash;
        else{
            hash++;
            hash = hash % (ht -> size);
        }
    }
    return -1; /// not found in whole hashTable
}

bool checkHTworse(HT *ht)
{
    for(int i = 0; i < ht -> size; i++){
        if(ht -> free[i])
            continue;
        if(i != findData(ht, ht -> key[i]))
            return false;
    }
    return true;
}
bool checkHT(HT *ht) /// returns information about whether it is possible for every key in HashTable to be found
{
    int start = 0; /// start index
    int it = 0; /// iterator through hashTable
    while(it < ht -> size and !(ht -> free[it]))
        it++;

    if(it == ht -> size) return true; /// whole array is occupied

    while(it < ht -> size){
        if(ht -> free[it])
            start = it;
        else{
            int hash = hashFunction(ht -> key[it], ht -> size);
            if(hash <= start or hash > it) return false;
        }
        it++;
    }
    /// case when data is not looped
    if(ht -> free[ht -> size - 1]){
        it = 0;
        while(!(ht -> free[it])){
            if(hashFunction(ht -> key[it], ht -> size) > it)
                return false;
            it++;
        }
    }
    else{
        it = 0;
        while(!(ht -> free[it])){
            int hash = hashFunction(ht -> key[it],ht -> size);
            if(hash > it and hash < start)
                return false;
            it++;
        }
    }
    return true;
}