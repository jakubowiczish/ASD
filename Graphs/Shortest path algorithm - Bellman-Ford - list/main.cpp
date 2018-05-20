#include <iostream>

struct Edge{
    int src, dest, weight; /// src and dest vertices, weight of the edge
};

struct Graph{
    int V, E; /// V = number of vertices in graph, E = number of edges
    Edge **edges;
};

void BellmanFord(Graph *G, int src);
void printArray(int *distances, int n);
Graph *initializeUndirectedGraph();
void printList(Graph *G);

int main() {
    Graph *G = initializeUndirectedGraph();
    std::cout << "Give me source vertex for BellmanFord algorithm: " << std::endl;
    int src;
    std::cin >> src;
    BellmanFord(G,src);
    printList(G);
    return 0;
}

void BellmanFord(Graph *G, int src)
{
    int distances[G -> V];
    for(int i = 0; i < G -> V; i++){
        distances[i] = INT32_MAX;
    }
    distances[src] = 0;

    for(int i = 0; i <= G -> V - 1; i++){
        for(int j = 0; j < G -> E; j++){
            int u = G -> edges[j] -> src;
            int v = G -> edges[j] -> dest;
            int weight = G -> edges[j] -> weight;
            if(distances[u] != INT32_MAX and distances[u] + weight < distances[v])
                distances[v] = distances[u] + weight;
        }
    }

    for(int i = 0; i < G -> E; i++){
        int u = G -> edges[i] -> src;
        int v = G -> edges[i] -> dest;
        int weight = G -> edges[i] -> weight;
        if(distances[u] != INT32_MAX and distances[u] + weight < distances[v])
            std::cout << "Graph contains negative weight cycle" << std::endl;
    }
    printArray(distances,G -> V);
    return;
}

void printArray(int *distances, int n)
{
    std::cout << "Vertex and its distance from source: " << std::endl;
    for(int i = 0; i < n; i++){
        std::cout << "Vertex: " << i << ", distance: " << distances[i] << std::endl;
    }
}
Graph *initializeUndirectedGraph()
{
    int vertices, edges;
    std::cout <<  "Give me the number of vertices and edges in your graph: " << std::endl;
    std::cin >> vertices >> edges;
    Graph *G = new Graph;
    G -> V = vertices;
    G -> E = edges;
    G -> edges = new Edge*[edges];

    std::cout << "Give me starting and ending vertex for every edge, as well as its weight: " << std::endl;
    int v1, v2, weight;
    for(int i = 0; i < edges; i++){
        std::cin >> v1 >> v2 >> weight;
        Edge *edge = new Edge;
        edge -> src = v1;
        edge -> dest = v2;
        edge -> weight = weight;
        G -> edges[i] = edge;
    }
    return G;
}

void printList(Graph *G)
{
    std::cout << "List of weighted edges and their vertices " << std::endl;
    for(int i = 0; i < G -> E; i++){
        std::cout << "Edge and its src and dest vertices: " << std::endl;
        std::cout << "Edge: " << i <<", weight: " << G -> edges[i] -> weight << ", src vertex: " << G -> edges[i] -> src << ", dest vertex: " << G -> edges[i] -> dest << std::endl;
    }
}