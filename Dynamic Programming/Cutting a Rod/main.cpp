#include <iostream>

int cuttingARod(int prices[], int n);
int max(int a, int b);

int main() {
    int SIZE = 8;
    int array[] = {2, 5, 10, 11, 12, 30, 32, 40};
    std::cout << cuttingARod(array, SIZE) << std::endl;
    return 0;
}

int max(int a, int b){
    if(a > b) return a;
    return b;
}

int cuttingARod(int prices[], int n){
    if(n <= 0) return 0;
    int maxValue = -1;

    for(int i = 0; i < n; i++)
        maxValue = max(maxValue, prices[i] + cuttingARod(prices, n-i-1));
    return maxValue;
}