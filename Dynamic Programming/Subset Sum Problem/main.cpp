#include <iostream>

bool isSubsetSumRecursive(int array[], int n, int sum);
bool isSubsetSumDynamic(int array[], int n, int sum);

int main() {
    int SIZE = 8;
    int array[] = {1, 5, 8, 9, 11, 13, 18, 26};
    int sum = 28;
    if(isSubsetSumRecursive(array, SIZE, sum))
        std::cout << "(REC) There is a subset in a given array with given sum: " << sum << std::endl;
    if(isSubsetSumDynamic(array, SIZE, sum))
        std::cout << "(DYN) There is a subset in a given array with given sum: " << sum << std::endl;
    else
        std::cout << "There is no subset with given sum" << std::endl;
    return 0;
}

// returns true if there is a subset of array that is equal to sum
bool isSubsetSumRecursive(int array[], int n, int sum){
    if(n == 0 and sum != 0) return false;
    if(sum == 0) return true;

    if(array[n-1] > sum)
        isSubsetSumRecursive(array, n-1, sum);
    return isSubsetSumRecursive(array, n-1, sum) || isSubsetSumRecursive(array, n-1, sum - array[n-1]);
}

bool isSubsetSumDynamic(int array[], int n, int sum){
    bool subSet[n+1][sum+1];

    for(int i = 0; i <= n; i++)
        subSet[i][0] = true;
    for(int i = 0; i <= sum; i++)
        subSet[0][i] = false;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= sum; j++){
            if(j < array[i-1])
                subSet[i][j] = subSet[i-1][j];
            if(j >= array[i-1])
                subSet[i][j] = subSet[i-1][j] || subSet[i-1][j-array[i-1]];
        }
    }
    return subSet[n][sum];
}
