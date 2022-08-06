//Using adjacency list
//Doesn't work on graph with negative cycle
//Doesn't work on undirected graph with negative weight edges
#include <iostream>
#include <vector> 

using namespace std;

struct Edge
{
    int src;
    int dest;
    int weight;
};

class Graph
{
private:
    int V;
    vector<Edge> *adj;
public:
    Graph(int V);
    void addEdgeD(int src, int dest, int wt);
    void printGraph();
    void bellmanford(int src);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new vector<Edge>[V];
}

void Graph::addEdgeD(int v, int u, int wt)
{
    Edge e;
    e.src = v;
    e.dest = u;
    e.weight = wt;
    adj[v].push_back(e);
}

void Graph::printGraph()
{
    for (int i = 0; i < V; i++)
    {
        cout << "Vertex " << i << " is adjacent to:" << endl;
        for (auto j = adj[i].begin(); j != adj[i].end(); j++)
        {
            cout << "\tVertex " << j->dest << " with weight = " << j->weight << endl;
        }
    }
}

//O(EV)
void Graph::bellmanford(int src)
{
    //Array SP[V] to store the shortest dist from src to vertex v
    int SP[V] = {0};
    for (int i = 0; i < V; i++)
    {
        if (i != src)
        {
            SP[i] = INT_MAX;
        }
    }

    //Vector edges to store all vector to be considered
    vector<Edge> edges;
    for (int i = 0; i < V; i++)
    {
        for (auto j = adj[i].begin(); j != adj[i].end(); j++)
        {
            edges.push_back(*j);
        }
    }

    for (int i = 0; i < V; i++)
    {
        for (auto j = edges.begin(); j != edges.end(); j++)
        {
            if (SP[j->dest] > SP[j->src] + j->weight)
            {
                SP[j->dest] = SP[j->src] + j->weight;
            }
        }
    }

    cout << "Shotest Path from vertex " << src << " to:\n";
    for (int i = 0; i < V; i++)
    {
        cout << "\tVertex " << i << " = " <<  SP[i] << endl;
    }
    
}

int main()
{
    int V = 7;
    Graph g(V);
    g.addEdgeD(0,1,6);
    g.addEdgeD(0,2,5);
    g.addEdgeD(0,3,5);
    g.addEdgeD(1,4,-1);
    g.addEdgeD(2,1,-2);
    g.addEdgeD(2,4,1);
    g.addEdgeD(3,2,-2);
    g.addEdgeD(3,5,-1);
    g.addEdgeD(4,6,3);
    g.addEdgeD(5,6,3);
    //g.printGraph();
    g.bellmanford(0);
    return 0;
}