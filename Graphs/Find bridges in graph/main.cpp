#include <iostream>

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

int min(int a, int b);

Graph *initializeUndirectedGraph();
void printList(Graph *G);
void deleteGraph(Graph *G);

void findBridges_UTIL(Graph *G, int u, int *disc, int *low, int *parent, int &time);
void findBridges(Graph *G);


int main() {
    Graph *G = initializeUndirectedGraph();
    /*
    Test number 1:
    6 7

     0 1
     0 2
     1 2
     1 3
     3 4
     3 5
     4 5
     */

    /*
     Test number 2:
     13 14

     0 1
     0 9
     1 2
     1 3
     3 4
     3 5
     3 9
     5 6
     6 7
     7 8
     8 6
     9 10
     10 11
     11 12
     */


    printList(G);
    findBridges(G);
    deleteGraph(G);
    return 0;
}

void findBridges_UTIL(Graph *G, int u, int *disc, int *low, int *parent, int &time)
{
    G -> visited[u] = true;
    disc[u] = low[u] = ++time;
    for(Vertex *tmp = G -> E[u]; tmp; tmp = tmp -> next){
        int current = tmp -> val;
        if(!G -> visited[current]){
            parent[current] = u;
            findBridges_UTIL(G,current,disc,low,parent,time);

            low[u] = min(low[u], low[current]);

            if(low[current] > disc[u])
                std::cout << "Bridge: " << u << " " << current << std::endl;
        }
        else if(current != parent[u])
            low[u] = min(low[u], disc[current]);
    }
}

void findBridges(Graph *G)
{
    int time = 0;
    G -> visited = new bool[G -> size];
    int *disc = new int[G -> size];
    int *low = new int[G -> size];
    int *parent = new int[G -> size];

    for(int i = 0; i < G -> size; i++){
        parent[i] = -1;
        disc[i] = 0;
        low[i] = 0;
        G -> visited[i] = false;
    }

    for(int i = 0; i < G -> size; i++)
        if(!G -> visited[i])
            findBridges_UTIL(G,i,disc,low,parent,time);
}

int min(int a, int b)
{
    if(a > b) return b;
    return a;
}

Graph *initializeUndirectedGraph()
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

        Vertex *vertex_1 = new Vertex;
        vertex_1 -> val = v2;
        vertex_1 -> next = A[v1];
        A[v1] = vertex_1;

        Vertex *vertex_2 = new Vertex;
        vertex_2 -> val = v1;
        vertex_2 -> next = A[v2];
        A[v2] = vertex_2;
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