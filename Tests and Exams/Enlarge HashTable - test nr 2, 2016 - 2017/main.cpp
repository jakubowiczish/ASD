#include <iostream>
/*
 * Dana jest struktura HT, która opisuje tablicę haszującą rozmiaru size, przechowywującą liczby nieujemne:

struct HT {
    int* table;
    int size;
};
Tablica korzysta z funkcji haszującej int hash(int x) i liniowego rozwiązywania konfliktów
(ujemne wartości w tablicy table oznaczają wolne pola).

Doskonałością takiej tablicy nazywamy liczbę elementów x takich,
że pozycja x w tablicy to hash(x) % size (a więc x jest na "swojej" pozycji).

Proszę napisać funkcję void enlarge(HT* ht), która powiększa tablicę dwukrotnie
i wpisuje elementy w takiej kolejności, by doskonałość powstałej tablicy była największa.
Funkcja powinna być możliwie najszybsza.
 */

struct HT{
    int *table;
    int size;
};

void initializeHashTable(HT *ht, int n);
void addToHashTable(HT *ht, int value);
void printHashTable(HT *ht);
void enlarge(HT *ht);
unsigned int hashFunction(unsigned int x, int size);

int main() {
    int SIZE = 7;
    int data[] = {2,1,5,7,8,9,4};
    HT *ht = new HT;
    initializeHashTable(ht,SIZE);

    for(int i = 0; i < 7; i++)
        addToHashTable(ht,data[i]);

    std::cout << "HashTable before enlarging: " << std::endl;
    printHashTable(ht);
    enlarge(ht);
    std::cout << "HashTable after enlarging: " << std::endl;
    printHashTable(ht);

    return 0;
}

void initializeHashTable(HT *ht, int n)
{
    ht -> size = n;
    ht -> table = new int[n];
    for(int i = 0; i < n; i++)
        ht -> table[i] = -1; /// initialize all positions to be empty
    /// instead of creating bool *free in struct HT
}

void addToHashTable(HT *ht, int value)
{
    int hash = hashFunction(value,ht -> size);
    if(ht -> table[hash] == -1){
        ht -> table[hash] = value;
        return;
    }
    if(ht -> table[hash] != -1){
        int start = hash;
        hash++;
        while(hash != start){
            if(ht -> table[hash] == -1){
                ht -> table[hash] = value;
                return;
            }
            hash = (hash + 1) % (ht -> size);
        }
    }
}

void printHashTable(HT *ht)
{
    for(int i = 0; i < ht -> size; i++)
        std::cout << ht -> table[i] << std::endl;
    std::cout << std::endl;
}

void enlarge(HT *ht)
{
    int newSize = 2*(ht -> size); /// hashTable is to be enlarged twice
    int *arr = new int[newSize];
    for(int i = 0; i < newSize; i++)
        arr[i] = -1; /// if -1 - position is empty

    /// finding proper position for some elements

    for(int i = 0; i < ht -> size; i++){
        if(ht -> table[i] == -1) continue; /// empty position in HT being enlarged

        int index = hashFunction(ht -> table[i],newSize);
        if(arr[index] != -1) continue; ///occupied position
        arr[index] = ht -> table[i];
        ht -> table[i] = -1; /// value moved
    }

    /// finding proper position for the rest of elements

    for(int i = 0; i < newSize; i++){
        if(ht -> table[i] == -1) continue; /// empty position in HT being enlarged
        int index = hashFunction(ht -> table[i],newSize);

        while(true){
            if(arr[index] != -1){ /// if there's a place for something to be added
                arr[index] = ht -> table[i];
                ht -> table[i] = -1; /// value moved
                break;
            }
            ///finding nextHash
            index = (index + 1) % newSize;
        }
    }
    ht -> table = arr;
    ht -> size = newSize; /// update hashTable
}

unsigned int hashFunction(unsigned int x, int size) ///supposedly good hashing function for integers
{
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x % size;
}