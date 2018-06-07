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

void DFSlist(Graph *G, int s, int *result, int &counter);
void DFSlist_UTIL(Graph *G, int s, int *result, int &counter);
int *toposort(Graph *G);
int DFScount(Graph *G, int s);
int motherVertices(Graph *G);

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
    std::cout << motherVertices(G) << std::endl;
    deleteGraph(G);
    return 0;
}

/************************************************************************************************************/

void DFSlist(Graph *G, int s, int *result, int &counter)
{
    for(int i = 0; i < G -> size; i++)
        G -> visited[i] = false;
    /// std::cout << "DFS list - starting point at: " << s << std::endl;
    for(int i = 0; i < G -> size; i++)
        if(!G -> visited[i])
            DFSlist_UTIL(G,i,result,counter);
    /// std::cout << std::endl;

}

void DFSlist_UTIL(Graph *G, int s, int *result, int &counter)
{
    G -> visited[s] = true;
    /// std::cout << s << " ";
    for(Vertex *tmp = G -> E[s]; tmp; tmp = tmp -> next)
        if(!G -> visited[tmp -> val])
            DFSlist_UTIL(G,tmp -> val,result,counter);
    result[counter--] = s;

}

int *toposort(Graph *G)
{
    G -> visited[G -> size] = {};
    int *result = new int[G -> size];
    int counter = G -> size - 1;

    for(int i = 0; i < G -> size; i++)
        if(!G -> visited[i])
            DFSlist(G,i,result,counter);
    return result;
}

int DFScount(Graph *G, int s)
{
    G -> visited[s] = true;
    int sum = 1;
    for(int i = 0; i < G -> size; i++){
        for(Vertex *tmp = G -> E[s]; tmp; tmp = tmp -> next)
            if(!G -> visited[tmp -> val])
                sum += DFScount(G,tmp -> val);
    }
    return sum;
}

/// A mother vertex in a graph G is a vertex v such that all other vertices in G can be reached by a path from v.
/// This function finds how many mother vertices graph G contains
int motherVertices(Graph *G)
{
    int *tab = toposort(G);

    for(int i = 0; i < G -> size; i++)
        G -> visited[i] = false;

    std::cout << "The number of mother vertices in graph is: " << std::endl;

    if(DFScount(G,tab[0] == G -> size)){
        for(int i = 0; i < G -> size; i++)
            G -> visited[i] = false;
        return DFScount(G,tab[0]);
    }
    else return 0;

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