#include <iostream>
#include <queue>

struct Graph{
    int **E;
    bool *visited;
    int size;
    Graph(){};
    Graph(int **E, bool *visited, int size){
        this -> E = E;
        this -> visited = visited;
        this -> size = size;
    }
};

void printMatrix(Graph *G);
Graph *initializeDirectedGraph();
Graph *initializeUndirectedGraph();
void BFSmatrix(Graph *G, int s);

void DFSmatrix_UTIL(Graph *G, int s);
void DFSmatrix(Graph *G, int s);
void deleteGraph(Graph *G);

int main() {

    Graph *G = initializeUndirectedGraph();
    printMatrix(G);
    std::cout << "Give me the starting vertex for BFS: " << std::endl;
    int vertex;
    std::cin >> vertex;
    //DFSmatrix(G,vertex);
    BFSmatrix(G,vertex);
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

    deleteGraph(G);
    return 0;
}

Graph *initializeDirectedGraph()
{
    int vertices, edges;
    std::cout <<  "Give me the number of vertices and edges in your graph: " << std::endl;
    std::cin >> vertices >> edges;
    int **A = new int*[vertices];
    bool *B = new bool[vertices];

    for(int i = 0; i < vertices; i++)
        A[i] = new int[vertices];

    for(int i = 0; i < vertices; i++){
        B[i] = false;
        for(int j = 0; j < vertices; j++)
            A[i][j] = 0;
    }
    std::cout << "Give me starting and ending vertex for every edge: " << std::endl;
    int v1, v2;
    for(int i = 0; i < edges; i++) {
        std::cin >> v1 >> v2;
        A[v1][v2] = 1;
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
    int **A = new int*[vertices];
    bool *B = new bool[vertices];

    for(int i = 0; i < vertices; i++)
        A[i] = new int[vertices];

    for(int i = 0; i < vertices; i++){
        B[i] = false;
        for(int j = 0; j < vertices; j++)
            A[i][j] = 0;
    }
    std::cout << "Give me starting and ending vertex for every edge: " << std::endl;
    int v1, v2;
    for(int i = 0; i < edges; i++) {
        std::cin >> v1 >> v2;
        A[v1][v2] = A[v2][v1] = 1;
    }

    Graph *F = new Graph;
    F -> E = A;
    F -> visited = B;
    F -> size = vertices;

    return F;
}

void BFSmatrix(Graph *G, int s)
{
    int *distance = new int[G -> size];
    int *predecessor = new int[G -> size];

    for(int i = 0; i < G -> size; i++){
        G -> visited[i] = false;
        distance[i] = INT32_MAX;
        predecessor[i] = -1;
    }
    std::queue<int> q;
    q.push(s);
    G -> visited[s] = true;
    distance[s] = 0;
    predecessor[s] = -1;

    int current;
    std::cout << "BFS from starting point at " << s << std::endl;
    while(!q.empty()){
        current = q.front();
        q.pop();
        std::cout << current << " ";

        for(int v = 0; v < G -> size; v++){
            if(G -> E[current][v] == 1 and !(G -> visited[v])){
                G -> visited[v] = true;
                distance[v] = distance[current] + 1;
                predecessor[v] = current;
                q.push(v);
            }
        }
    }

    std::cout << std::endl;
    for(int i = 0; i < G -> size; i++)
        std::cout << "index: " << i << ", distance: " << distance[i] << ", predecessor: " << predecessor[i] << std::endl;
}

void DFSmatrix_UTIL(Graph *G, int s)
{
    G -> visited[s] = true;
    std::cout << s << " ";
    for(int i = 0; i < G -> size; i++)
        if(G -> E[s][i] == 1 and !(G -> visited[i]))
            DFSmatrix_UTIL(G,i);
}

void DFSmatrix(Graph *G, int s)
{
    std::cout << "DFS from starting point at: " << s << std::endl;
    DFSmatrix_UTIL(G,s);
}


void printMatrix(Graph *G)
{
    std::cout << "Adjacency matrix: " << std::endl;
    for(int i = 0; i < G -> size; i++) {
        for (int j = 0; j < G->size; j++)
            std::cout << G -> E[i][j] << " ";
        std::cout << std::endl;
    }

}

void deleteGraph(Graph *G)
{
    for(int i = 0; i < G -> size; i++)
        delete G -> E[i];
    delete G -> E;
    delete G -> visited;
}
