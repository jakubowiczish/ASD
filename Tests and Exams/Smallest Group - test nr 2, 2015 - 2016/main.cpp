#include <iostream>
/// based on github.com/jakubdybczak
/*
 * W ramach obchodów międzynarodowego święta cyklistów organizatorzy przewidzieli górską wycieczkę rowerową.
 * Będzie się ona odbywać po bardzo wąskiej ścieżce, na której rowery mogą jechać tylko jeden za drugim.
 * W ramach zapewnienia bezpieczeństwa każdy rowerzysta będzie miał numer identyfikacyjny oraz małe urządzenie,
 * przez które będzie mógł przekazać identyfikator rowerzysty przed nim (lub -1 jeśli nie widzi przed sobą nikogo).
 * Należy napisać funkcję, która na wejściu otrzymuje informacje wysłane przez rowerzystów
 * i oblicza rozmiar najmniejszej grupy (organizatorzy obawiają się, że na małe grupy mogłyby napadać dzikie zwierzęta).
 * Dane są następujące struktury danych:

struct Cyclist {
    int id;     // identyfikator rowerzysty
    int n_id;   // identyfikator rowerzysty ktorego widzi
};
Funkcja powinna mieć prototyp int smallestGroup(Cyclist cyclist[], int n), gdzie cyclist to tablica n rowerzystów.

Funkcja powinna być możliwie jak najszybsza. Można założyć,
identyfikatory rowerzystów to liczby z zakresu od 0 do 10^8
(osiem cyft napisanych w rzędach na koszulce rowerzysty) i że pamięć nie jest ograniczona.
Rowerzystów jest jednak dużo mniej niż identyfikatorów (nie bez powodu boją się dzikich zwierząt).
Należy zaimplementować wszystkie porzebne struktury danych.
 */

struct Cyclist {
    int id;     // identyfikator rowerzysty
    int n_id;   // identyfikator rowerzysty ktorego widzi
};

struct CautiousCyclist{
    int id;
    int n_id;
    bool isBehind; /// true if there's someone behind
};

struct HT{
    CautiousCyclist **table;
    int size;
};

unsigned int hashFunction(unsigned int x, int size);
void insertToHashTable(HT *ht, Cyclist cyclist);
int smallestGroup(Cyclist cyclist[], int n);
CautiousCyclist *searchForTheCyclist(HT *ht, int id);

int main() {
    int SIZE = 6;
    Cyclist cyclist[SIZE];
    cyclist[0].id = 0;
    cyclist[0].n_id = 1;
    cyclist[1].id = 1;
    cyclist[1].n_id = 2;
    cyclist[2].id = 2;
    cyclist[2].n_id = 3;
    cyclist[3].id = 3;
    cyclist[3].n_id = -1;
    cyclist[4].id = 6;
    cyclist[4].n_id = -1;
    cyclist[5].id = 5;
    cyclist[5].n_id = 6;
    int result = smallestGroup(cyclist,SIZE);
    std::cout << "Smallest group has " << result << " cyclists" << std::endl;
    return 0;
}

unsigned int hashFunction(unsigned int x, int size) ///supposedly good hashing function for integers
{
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x % size;
}

void insertToHashTable(HT *ht, Cyclist cyclist)
{
    CautiousCyclist* newCyclist = new CautiousCyclist;
    newCyclist -> id = cyclist.id;
    newCyclist -> n_id = cyclist.n_id;
    newCyclist -> isBehind = false;
    int index = hashFunction(cyclist.id,ht -> size);
    while(ht -> table[index] != nullptr)
        index = (index + 1) % (ht -> size);
    ht -> table[index] = newCyclist;
}


int smallestGroup(Cyclist cyclist[], int n)
{
    HT *ht = new HT;
    ht -> table = new CautiousCyclist*[3*n];
    ht -> size = 3*n;

    for(int i = 0; i < ht -> size; i++)
        ht -> table[i] = nullptr;

    for(int i = 0; i < n; i++)
        insertToHashTable(ht,cyclist[i]);

    for(int i = 0; i < n; i++)
        if(cyclist[i].n_id != -1)
            if(searchForTheCyclist(ht,cyclist[i].n_id) -> id != -1)
                searchForTheCyclist(ht,cyclist[i].n_id) -> isBehind = true;

    int finalCounter = INT32_MAX;
    for(int i = 0; i < ht -> size; i++){
        if(ht -> table[i] != nullptr and !ht -> table[i] ->isBehind) { /// there's noone behind
            int counter = 1;
            CautiousCyclist *tmpCyclist = ht->table[i];
            while (tmpCyclist->n_id != -1) {
                tmpCyclist = searchForTheCyclist(ht, tmpCyclist->n_id);
                counter++;
            }
            if(counter < finalCounter)
                finalCounter = counter;
        }
    }
    return finalCounter;
}

CautiousCyclist *searchForTheCyclist(HT *ht, int id)
{
    int index = hashFunction(id,ht -> size);
    while(ht -> table[index] != nullptr){
        if(ht -> table[index] -> id == id)
            return ht -> table[index];
        index = (index + 1) % (ht -> size);
    }
    return nullptr; /// cyclist not found
}


