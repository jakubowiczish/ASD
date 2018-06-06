#include <iostream>
#include <stack>

struct Vertex{
    int val;
    Vertex *next;
    Vertex(){};
    Vertex(int val, Vertex *next){
        this -> val = val;
        this -> next = next;
    }
};

struct Graph{
    Vertex **E;
    bool *visited;
    int size;
    Graph(){};
    Graph(Vertex **E, bool *visited, int size){
        this -> E = E;
        this -> visited = visited;
        this -> size = size;
    }
};

void DFSlistVisit(Graph *G, int v, std::stack<int> &stack);
void DFSlistPrint(Graph *G, int v);
void transposeList(Graph *G);
void findSCC(Graph *G, int v);

void topologicalSort_UTIL(Graph *G, int v, std::stack<int> &stack);
void topologicalSort(Graph *G);

Graph *initializeDirectedGraph();
void printList(Graph *G);
void deleteGraph(Graph *G);

int main() {
    Graph *G = initializeDirectedGraph();
    /*
        a)
        6 6

        0 1
        0 3
        1 2
        2 5
        3 4
        4 5

        b)
        15 18

        0 1
        0 2
        1 3
        2 3
        2 11
        3 4
        4 5
        4 7
        5 6
        6 7
        7 8
        8 9
        8 10
        9 10
        11 12
        11 13
        14 12
        14 13
     */

    printList(G);
    findSCC(G,0);
    deleteGraph(G);
    return 0;
}

/************************************************************************************************************/

void DFSlistVisit(Graph *G, int v, std::stack<int> &stack)
{
    for(Vertex *tmp = G -> E[v]; tmp; tmp = tmp -> next)
        if(!G -> visited[tmp -> val])
            DFSlistVisit(G,tmp -> val,stack);
    G -> visited[v] = true;
    stack.push(v);
}

void DFSlistPrint(Graph *G, int v)
{
    for(Vertex *tmp = G -> E[v]; tmp; tmp = tmp -> next)
        if(!G -> visited[tmp -> val])
            DFSlistPrint(G,tmp -> val);
    G -> visited[v] = true;
    std::cout << v << " ";
}

void transposeList(Graph *G)
{
    Graph *F = new Graph;
    Vertex **A = new Vertex*[G -> size];
    bool *B = new bool[G -> size];
    for(int i = 0; i < G -> size; i++) {
        A[i] = nullptr;
        B[i] = false;
    }

    for(int i = 0; i < G -> size; i++){
        for(Vertex *tmp = G -> E[i]; tmp; tmp = tmp -> next){
            Vertex *v = new Vertex;
            v -> val = tmp -> val;
            v -> next = A[tmp -> val];
            A[tmp -> val] = v;
        }
    }

    F -> E = A;
    F -> visited = B;
    F -> size = G -> size;

    G = F;
}

/// function that finds and prints Strongly Connected Components
void findSCC(Graph *G, int v)
{
    std::stack<int> stack;
    for(int i = 0; i < G -> size; i++)
        G -> visited[i] = false;

    for(int i = 0; i < G -> size; i++)
        if(!G -> visited[i])
            DFSlistVisit(G,i,stack);

    transposeList(G);

    for(int i = 0; i < G -> size; i++)
        G -> visited[i] = false;

    std::cout << "Strongly Connected Components in given graph: " << std::endl;
    int tmp;
    while(!stack.empty()){
        tmp = stack.top();
        stack.pop();
        if(!G -> visited[tmp]){
            DFSlistPrint(G,tmp);
            std::cout << std::endl;
        }
    }
}

/************************************************************************************************************/

void topologicalSort_UTIL(Graph *G, int v, std::stack<int> &stack)
{
    G -> visited[v] = true;
    for(Vertex *tmp = G -> E[v]; tmp; tmp = tmp -> next)
        if(!G -> visited[tmp -> val])
            topologicalSort_UTIL(G,tmp -> val,stack);
    stack.push(v);
}

void topologicalSort(Graph *G)
{
    std::stack<int> stack;
    for(int i = 0; i < G -> size; i++)
        G -> visited[i] = false;
    for(int i = 0; i < G -> size; i++)
        if(!G -> visited[i])
            topologicalSort_UTIL(G,i,stack);

    std::cout << "Topological sort of given graph: " << std::endl;
    while(!stack.empty()){
        std::cout << stack.top() << " ";
        stack.pop();
    }
    std::cout << std::endl;
}

/************************************************************************************************************/

Graph *initializeDirectedGraph()
{
    int vertices, edges;
    std::cout <<  "Give me the number of vertices and edges in your graph: " << std::endl;
    std::cin >> vertices >> edges;
    Vertex **A = new Vertex *[vertices];
    bool *B = new bool[vertices];

    for(int i = 0; i < vertices; i++) {
        A[i] = nullptr;
        B[i] = false;
    }

    std::cout << "Give me starting and ending vertex for every edge: " << std::endl;
    int v1, v2;
    for(int i = 0; i < edges; i++) {
        std::cin >> v1 >> v2;
        Vertex *vertex = new Vertex;
        vertex -> val = v2;
        vertex -> next = A[v1];
        A[v1] = vertex;
    }

    Graph *F = new Graph;
    F -> E = A;
    F -> visited = B;
    F -> size = vertices;

    return F;
}

void printList(Graph *G)
{
    std::cout << "Adjacency list: " << std::endl;
    Vertex *tmp;
    for(int i = 0; i < G -> size; i++){
        tmp = G -> E[i];
        std::cout << i <<": ";

        while(tmp){
            std::cout << tmp -> val << " ";
            tmp = tmp -> next;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void deleteGraph(Graph *G)
{
    for(int i = 0; i < G -> size; i++){
        Vertex *ptr = G -> E[i];
        while(ptr){
            Vertex *tmp = ptr;
            ptr = ptr -> next;
            delete tmp;
        }
    }
    delete G -> E;
    delete G -> visited;
}