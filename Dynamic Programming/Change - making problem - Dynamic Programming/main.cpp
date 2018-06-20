#include <iostream>

/*  Wydawanie monet
    N[0],…,N[t−1] - dostępne nominały
    S - kwota do wydania
    Obliczyć minimalną liczbę monet do wydania S.
*/
int minimumCoinChange(int N[], int t, int S);

int main() {
    int COINS;
    std::cout << "Tell me how many coins there is in your currency: " << std::endl;
    std::cin >> COINS;

    int N[COINS];
    std::cout << "Give me values of this coins: " << std::endl;
    for(int i = 0; i < COINS; ++i)
        std::cin >> N[i];
    int value;
    std::cout << "Give me value to check: " << std::endl;
    std::cin >> value;

    std::cout << minimumCoinChange(N,COINS,value);
    return 0;
}

int minimumCoinChange(int N[], int t, int S)
{
    int *T = new int[S + 1];
    T[0] = 0; /// for 0 you need 0 coins
    for(int i = 1; i <= S; ++i)
        T[i] = INT32_MAX;
    for(int i = 0; i < t; ++i){
        int nom = N[i];
        for(int j = 0; j <= S - nom; ++j)
            if(T[j] < INT32_MAX)
                if(T[j] + 1 < T[j + nom])
                    T[j + nom] = T[j] + 1;
    }
    return T[S];
}
