#include <iostream>

/*
 *
struct field {
    int value;
    int long j;
    int short j;

Z każdego pola można skakać tylko o ilość pól zapisaną w long j lub short j. Napisać program
który zwróci maksymalną wartość jaką możemy osiągnąć poprzez przejście z pola 0 do n-1.
Można założyć, że z każdego pola da się dojść do pola n-1.
 */

struct field {
    int value;
    int long_j;  /// long jump
    int short_j; /// short jump
};

int max(int a, int b);
int findPath_UTIL(field Field[],int values[], int left, int right);
int findPath(field Field[], int N);

int main() {
     /// Można założyć że z każdego pola da się dojść do pola n-1, zatem:
    const int SIZE = 10;
    field Field[SIZE];
    /// initialization
    for(int i = 0; i < 7; i++){
        Field[i].value = i;
        Field[i].short_j = 2;
        Field[i].long_j = 3;
    }
    for(int i = 7; i < SIZE; i++)
        Field[i].value = Field[i].short_j = Field[i].long_j = 1;
    Field[5].value = 10;

    /*

     value      short_j     long_j
     0          2           3
     1          2           3
     2          2           3
     3          2           3
     4          2           3
     10         2           3
     6          2           3
     1          1           1
     1          1           1
     1          1           1

     maxPath:
     0 -> 3 -> 10 -> 1 -> 1 -> 1 -> 1 = 16
     */
    std::cout << findPath(Field,SIZE);

    return 0;
}

int max(int a, int b)
{
    if(a > b) return a;
    return b;
}

int findPath_UTIL(field Field[],int values[], int left, int right)
{
    if(values[left] > -1) return values[left];
    if(left == right){
        values[left] = Field[left].value;
        return values[left];
    }
    int maximumValue = max(findPath_UTIL(Field,values,left + Field[left].short_j,right),findPath_UTIL(Field,values,left + Field[left].long_j, right)) + Field[left].value;
    values[left] = maximumValue;
    return maximumValue;
}

int findPath(field Field[], int N)
{
    int values[N];
    for(int i = 0; i < N; i++) values[i] = -1;
    return findPath_UTIL(Field,values,0,N-1);
}