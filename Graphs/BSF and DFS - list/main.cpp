#include <iostream>
#include <queue>

/// FUNDAMENTAL INFORMATION
/// IN MY GRAPH FOR EVERY VERTEX ITS VALUE IS EQUAL TO ITS INDEX

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


Graph *initializeUndirectedGraph();
void reinitializeGraph(Graph *G);
void printList(Graph *G);
void BFSlist(Graph *G, int s);

void DFSlist_UTIL(Graph *G, int s);
void DFSlist(Graph *G, int s);

void deleteGraph(Graph *G);

int main() {
    Graph *G = initializeUndirectedGraph();
    std::cout << "Give me the starting vertex for BFS: " << std::endl;
    int vertex;
    std::cin >> vertex;
    /*
     *  my example
        6 6

        0 1
        1 2
        2 3
        3 4
        4 5
        5 0
     */
    BFSlist(G,vertex);
    deleteGraph(G);
    return 0;
}

void BFSlist(Graph *G, int s)
{
    int *distance = new int[G -> size], *predecessor = new int[G -> size];
    for(int i = 0; i < G -> size; i++){
        G -> visited[i] = false;
        distance[i] = INT32_MAX;
        predecessor[i] = -1;
    }
    std::queue<int> q;
    G -> visited[s] = true;
    q.push(s);
    distance[s] = 0;
    predecessor[s] = -1;

    int current;
    std::cout << "BFS list - starting point at: " << s << std::endl;
    while(!q.empty()){
        current = q.front();
        q.pop();
        std::cout << current << " ";
        for(Vertex *tmp = G -> E[current]; tmp; tmp = tmp -> next){
            if(!G -> visited[tmp -> val]){
                G -> visited[tmp -> val] = true;
                distance[tmp -> val] = distance[current] + 1;
                predecessor[tmp -> val] = current;
                q.push(tmp -> val);
            }
        }
    }
    std::cout << std::endl;
    for(int i = 0; i < G -> size; i++)
        std::cout << "Index: " << i << ", distance: " << distance[i] << ", predecessor: " << predecessor[i] << std::endl;
}

void DFSlist(Graph *G, int s)
{
    for(int i = 0; i < G -> size; i++)
        G -> visited[i] = false;
    std::cout << "DFS list - starting point at: " << s << std::endl;
    for(int i = 0; i < G -> size; i++)
        if(!G -> visited[i])
            DFSlist_UTIL(G,i);
    std::cout << std::endl;

}

void DFSlist_UTIL(Graph *G, int s)
{
    G -> visited[s] = true;
    std::cout << s << " ";
    for(Vertex *tmp = G -> E[s]; tmp; tmp = tmp -> next)
        if(!G -> visited[tmp -> val])
            DFSlist_UTIL(G,tmp -> val);
}

void reinitializeGraph(Graph *G)
{
    bool *B = new bool[G -> size];
    for(int i = 0; i < G -> size; i++){
        B[i] = false;
    }
    G -> visited = B;
}

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