#include <iostream>

// Uncomment line with "#define DEBUG" if you want to see your hashtable.
// But rememeber to send only solutions with debug turned off!
// #define DEBUG 1

using namespace std;

enum states {
    EMPTY = 0,
    OCCUPIED = 1,
    STH_WAS_HERE = 2
};

struct Slot
{
    string name;
    string phone;
    states state;
};

uint32_t hashfunc(string txt) {

    uint32_t limit = (txt.length()/4);
    uint32_t x = 0;

    for(int i = 0; i < limit; i++){
        uint32_t tmp = 0;
        for(int j = 0; j < 4; j++){
            tmp += txt[j+i*4];
            tmp <<= 8; /// przesuniecie bitowe o 8
        }
        x ^= tmp;
        if(i == limit - 1){
            int k = i*4;
            tmp = 0;
            while(k < txt.length()){
                tmp += txt[k];
                k++;
                tmp <<= 8;
            }
            x ^= tmp;
        }
    }
    return x;
}

void add_to_hashtable(Slot** hashtable, int n, string name, string phone) {
    uint32_t hash = hashfunc(name) % n;

    uint32_t tmp = hash;
    while(hashtable[hash] -> state == OCCUPIED){
        hash++;
        if(hash == n) hash = 0;
        if(hash == tmp) return;
    }
    hashtable[hash]->state = OCCUPIED;
    hashtable[hash]->name = name;
    hashtable[hash]->phone = phone;
}

string get_number(Slot** hashtable, int n, string name) {
    if (n == 0) return "";
    uint32_t hash = hashfunc(name) % n;
    int i = 0;
    uint32_t tmp = hash;

    while(hashtable[hash] -> name != name){
        hash++;
        if(hash == n) hash = 0;
        if(hash == tmp) return "";/// empty string
        if(hashtable[hash] -> state == EMPTY) return "";
    }

    return hashtable[hash]->phone;
}

void remove_from_hashtable(Slot** hashtable, int n, string name) {
    uint32_t hash = hashfunc(name) % n;
    uint32_t tmp = hash;

    while(hashtable[hash] -> name != name){
        hash++;
        if(hash > n) hash = 0;
        if(hash == tmp) return;
        if(hashtable[hash] -> state == EMPTY) return;
    }
    hashtable[hash] -> name = "";
    hashtable[hash] -> phone = "";
    hashtable[hash]->state = STH_WAS_HERE;
}


void free_memory(Slot** hashtable, int n) {
    for (int i = 0; i < n; i++) {
        delete(hashtable[i]);
    }
    delete[](hashtable);
}

void debug_print_hashtable(Slot** hashtable, int n) {
    #ifdef DEBUG
        for (int i = 0; i < n; i++) {
            cout << i << ": [" << hashtable[i]->state << "] " <<  hashtable[i]->name << endl;
        }
        cout << endl;
    #endif
}

int main() {
    ios::sync_with_stdio(false);
    int Z;
    cin >> Z;

    while (Z--) {
        int n, d, k;
        char op;
        string tmp_name, tmp_phone;

        cin >> n;
        cin >> k;

        int size = n*5;

        Slot** hashtable = new Slot*[size]();

        for (int i = 0; i < size; i++) {
            hashtable[i] = new Slot();
            hashtable[i]->state = EMPTY;
        }

        for (int i = 0; i < k; i++) {
            cin >> op;
            switch(op) {
                case 'a':
                    cin >> tmp_name;
                    cin >> tmp_phone;
                    add_to_hashtable(hashtable, size, tmp_name, tmp_phone);
                    break;
                case 'r':
                    cin >> tmp_name;
                    remove_from_hashtable(hashtable, size, tmp_name);
                    break;
                case 'g':
                    cin >> tmp_name;
                    cout << get_number(hashtable, size, tmp_name) << endl;
                    break;
            }
            debug_print_hashtable(hashtable, size);
        }

        free_memory(hashtable, size);

    }

}
