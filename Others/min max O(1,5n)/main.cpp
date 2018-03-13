#include <iostream>
/// wyszukiwanie min i max w zlozonosci 3n/2
using namespace std;

void findMinAndMax(int tab[], int n){
    int min = tab[0];
    int max = tab[0];

    for(int i = n%2; i < n; i+=2){
        if(tab[i] > tab[i+1]){
            if(tab[i] > max) max = tab[i];
            if(tab[i+1] < min) min = tab[i+1];
        }
        else {
            if(tab[i+1] > max) max = tab[i+1];
            if(tab[i] < min) min = tab[i];
        }
    }
    cout << "MIN: " << min << endl;
    cout << "MAX: " << max << endl;
}
int main() {
    int tab[] = {9,3,6,2,4,8};
    findMinAndMax(tab,6);
    return 0;
}
