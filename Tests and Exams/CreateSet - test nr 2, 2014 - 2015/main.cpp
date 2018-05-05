#include <iostream>
/*
 *  Pewna firma przechowuje dużo liczb pierwszych w postaci binarnej jako stringi ”10101...”.
    Zaimplementuj strukturę danych Set do przechowywania tych danych. Napisz funkcje:
    Set createSet( string A[], int n ), która tworzy Set z n-elementowej tablicy stringów
    oraz bool contains( Set a, string s ), która sprawdza czy dana liczba jest w Secie.
    Oszacuj złożoność czasową i pamięciową powyższych funkcji.
 */
struct Set{
    int val;
    bool contains;
    Set *left, *right;
};

void inorderPrint(Set *root);
Set *createSet(std::string A[], int n);
bool contains(Set *p, std::string s);

int main() {
    std::string keys[] = {"10","10111","10101","0","1000","11111"};
    std::string toCheck[] = {"0","1111","11111"};

    Set *root = createSet(keys,6);
    inorderPrint(root);
    std::cout << std::endl;
    for(int i = 0; i < 3; i++){
        if(contains(root,toCheck[i]))
            std::cout << "YES" << std::endl;
        else
            std::cout << "NO" << std::endl;
    }

    return 0;
}

void inorderPrint(Set *root)
{
    if(root == nullptr) return;
    inorderPrint(root -> left);
    std::cout << root -> val << ' ';
    inorderPrint(root -> right);
}

Set *createSet(std::string A[], int n)
{
    Set *newSet = new Set;
    newSet -> val = -1;
    newSet -> right = newSet -> left = nullptr;
    Set *tmp = newSet;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < A[i].length(); j++){
            if(A[i][j] == '1'){

                if(tmp -> right == nullptr){
                    Set *temp = new Set;
                    temp -> val = 1;
                    temp -> left = temp -> right = nullptr;
                    if(A[i].length() - 1 == j) temp -> contains = true;
                    else temp -> contains = false;
                    tmp -> right = temp;
                    tmp = temp;
                }
                else{
                    if(A[i].length() - 1 == j) tmp -> contains = true;
                    tmp = tmp -> right;
                }
            }
            else{

                if(tmp -> left == nullptr){
                    Set *temp = new Set;
                    temp -> val = 0;
                    temp -> left = temp -> right = nullptr;
                    if(A[i].length() - 1 == j) temp -> contains = true;
                    else temp -> contains = false;
                    tmp -> left = temp;
                    tmp = temp;
                }
                else{
                    if(A[i].length() - 1 == j) tmp -> contains = true;
                    tmp = tmp -> left;
                }
            }
        }
        tmp = newSet;
    }
    return newSet;
}

bool contains(Set *p, std::string s)
{
    int last = s.length() - 1;
    for(int i = 0; i < s.length() - 1; i++){
        if(s[i] =='1'){
            if(p -> right != nullptr) p = p -> right;
            else return false;
        }
        else{
            if(p -> left != nullptr) p = p -> left;
            else return false;
        }
    }
    if(s[last] == '1'){
        if(p -> right == nullptr) return false;
        else
        if(p -> right -> contains != true) return false;
    }
    else{
        if(p -> left == nullptr) return false;
        else
        if(p -> left -> contains != true) return false;
    }
    return true;
}
