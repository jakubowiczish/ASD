 #include <iostream>
#include <ctime>
#include <cstdlib>
/*
1. Implementacja kolejko priorytetowej na drzewie trinarnym
2. wyrazenie arytmetyczne sk³ada siê: ze zmiennych a,b,c,...
operatorów +,-,*,/,^ oraz nawiasów (). Proszê zaimplementowaæ
funkcjê sprawdzajaca poprawnoœæ wyrazenie.
3. Jak zaimplementowaæ kolejkê na dwóch stosach?
4. Proszê zaimplementowaæ algorytm “przesuwajacy” zadana n-elementowa
tablice A o k pozycji.
(Przesuniêcie tablicy oznacza, ¿e element, który by³ pierwotnie na
pozycji i, powinien siê znalezc na pozycji
n + k (modulo n). Algorytm powinien dzialaæ w miejscu.
 */
using namespace std;

const int MAX=20;

struct stos {
    int t[MAX];
    int size;
};

int parent(int index);
int leftChild(int index);
int middleChild(int index);
int rightChild(int index);
void heapify(int arr[], int index);
void buildHeap(int arr[], int n);
int heapsort(int arr[], int n);

int ExtractMax(int tab[]);
void Insert(int tab[], int N, int key);
void printPriorityQueue(int tab[]);

bool isExpressionValid(string expression);
char operators[5]={'+','-','*','/','^'};

void moveElements_helping(int tab[], int N, int k,int index);
void moveElements_actual(int tab[], int N, int k);
int count_next(int i, int N, int k);
void set_table(int tab[], int N);
void print_table(int tab[], int N);

void init(stos &st);
void push(stos &st, int el);
int pop(stos &st);
bool empty(stos &st);
int put(stos &s1, int value);
int get(stos &s1, stos &s2);

///***********************************MAIN*********************************///
int main()
{
    cout << "TASK NUMBER 1: " << endl << endl;
    ///*********************ZADANIE 1*******************************///
    srand(time(NULL));
	//EXAMPLE USAGE OF ALGORITHM
	int n = 5;
	int arr[n];
	arr[0] = 0; //in this place, a size of elements will be stored

	for(int i = 0; i < n-1; i++){
		int prority = rand();
		cout << "Inserting prority: " << prority << endl;
		Insert(arr,n,prority);
		printPriorityQueue(arr);
	}
	for(int i = 0; i < n-1; i++){
		int extracted = ExtractMax(arr);
		cout << "Extracting: " << extracted << endl;
		printPriorityQueue(arr);
	}

	cout << "TASK NUMBER 2: " << endl << endl;
    ///********************** ZADANIE 2 ****************************///
    string expression;
    cout << "Enter the expression: " << endl;
    getline(cin,expression);
    if(isExpressionValid(expression))
        cout << "The expression is valid" << endl;
    else
        cout << "The expression is faulty!" << endl;

    cout << "TASK NUMBER 3: " << endl << endl;
    ///******************** ZADANIE 3 **********************///
    stos s1;
    stos s2;

    init(s1);
    init(s2);

    put(s1,3);
    put(s1,8);
    put(s1,2);
    put(s1,4);

    cout << get(s1,s2) << endl;
    cout << get(s1,s2) << endl;
    cout << get(s1,s2) << endl;
    cout << get(s1,s2) << endl;

    cout << endl << endl;

    cout << "TASK NUMBER 4: " << endl << endl;
    ///************************ZADANIE 4******************************///

    int N = 20;
    int tab[N];
    set_table(tab,N);
    print_table(tab,N);
    int k;
    cout << "How many to the right? " << endl;
    cin >> k;
    moveElements_actual(tab,N,k);
    print_table(tab,N);
    return 0;
}

///***********************************************************************************************///

int ExtractMax(int tab[])
{
    if(tab[0] == 0)
        exit(1);
    int result = tab[1];
    tab[1] = tab[tab[0]];
    tab[tab[0]] = 0;
    tab[0]--;
    heapify(tab,1);
    return result;
}

void Insert(int tab[], int N, int key)
{
    if(tab[0] == N-1)
        exit(1); /// queue is full
    tab[++tab[0]] = key;
    int i = tab[0];

    while(i > 1 and tab[i] > tab[parent(i)]){
        swap(tab[i],tab[parent(i)]);
        i = parent(i);
    }
}

void printPriorityQueue(int tab[])
{
    cout << "Priority Queue: " << endl;
    for(int i = 1; i <= tab[0]; i++){
        cout << tab[i] <<" ";
    }
    cout << endl;
}

int parent(int index)
{
    if(index%3 == 2) return index/3 + 1;
    if(index%3 == 0) return index/3;
    if(index%3 == 1) return index/3;
}
int leftChild(int index)
{
    return index*3-1;
}
int middleChild(int index)
{
    return index*3;
}
int rightChild(int index)
{
    return index*3+1;
}
void heapify(int arr[], int index)
{
    int size = arr[0];
    int largest = index;
    int left = leftChild(index);
    int middle = middleChild(index);
    int right = rightChild(index);
    if(left <= size && arr[left] > arr[largest]) largest=left;
    if(middle <= size && arr[middle] > arr[largest]) largest=middle;
    if(right <= size && arr[right] > arr[largest]) largest=right;
    if(largest != index){
        std::swap(arr[largest], arr[index]);
        heapify(arr,largest);
    }
}
void buildHeap(int arr[], int n)
{
    arr[0]=n-1;
    for(int i = (n-1)/3; i>=1; i--){
        heapify(arr,i);
    }
}
int heapsort(int arr[], int n)
{
    buildHeap(arr, n);
    for(int i = n-1; i>1; i--){
        std::swap(arr[1], arr[i]);
        arr[0]--;
        heapify(arr,1);
    }
}

void init(stos &st)
{
    st.size=0;
}
void push(stos &st, int el)
{
    st.t[st.size++]=el;
} // brak kontroli
int pop(stos &st)
{
    return st.t[--st.size];
} // brak kontroli
bool empty(stos &st)
{
    return (st.size==0);
}
int put(stos &s1, int value)
{
    push(s1,value);
}
int get(stos &s1, stos &s2)
{
    while(s1.size > 1){
        int value = pop(s1);
        push(s2, value);
    }
    int tmp = pop(s1);
    while(s2.size > 0){
        int value = pop(s2);
        push(s1, value);
    }
    return tmp;
}

bool isExpressionValid(string expression)
{
    int bracketsCounter = 0;
    int charactersCounter=0;
    int operatorsCounter=0;
    bool lastOperator=false;
    bool lastCharacter=false;
    for(int i = 0; i < expression.size(); i++){
        if(expression[i]=='('){
            lastOperator=false;
            lastCharacter=false;
            bracketsCounter++;
        }
        if(expression[i]==')'){
            bracketsCounter--;
            lastOperator=false;
            lastCharacter=false;
            if(lastOperator) return false;
            if(bracketsCounter < 0) return false;
        }
        if((expression[i]>='A' && expression[i] <= 'Z') || (expression[i]>='a' && expression[i] <= 'z')){
            if(!lastCharacter){
                charactersCounter++;
                lastCharacter=true;
                lastOperator=false;
            }
        }
        for(int j = 0; j < 5; j++){
            if(expression[i]==operators[j]){
                operatorsCounter++;
                if(lastOperator){
                    return false;
                }
                lastCharacter=false;
                lastOperator=true;
            }
        }
    }
    cout << "Liczba operatorow: " << operatorsCounter << endl;
    cout << "Liczba zmiennych: " << charactersCounter << endl;
    if(bracketsCounter!=0) return false;
    if(lastOperator) return false;
    return true;
}

void moveElements_helping(int tab[], int N, int k,int index)
{
    int start = index;
    int current = tab[index];
    int next = count_next(index,N,k);
    while(next != start){
        swap(current,tab[next]);
        index = next;
        next = count_next(index,N,k);
    }
    swap(current,tab[next]);
}

void moveElements_actual(int tab[], int N, int k)
{
    int it = (N%k == 0) ? k : 1;
    for(int i = 0; i < it; i++)
        moveElements_helping(tab,N,k,i);
}

int count_next(int i, int N, int k)
{
    return (i+k)%N;
}
void set_table(int tab[], int N)
{
    for(int i = 0; i < N; ++i) {
        tab[i] = i+2;
    }
}

void print_table(int tab[], int N)
{
    for(int i =0 ; i < N; ++i) {
        cout << tab[i] << " ";
    }
    cout << endl;
}

