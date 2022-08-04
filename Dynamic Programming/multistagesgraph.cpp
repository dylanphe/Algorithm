#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
    int dest;
    int weight;
};

class multistageGraph 
{
//private:
    int V;
    int stage;
    vector<Edge> *adj;

public:
    //Constructor
    multistageGraph(int V, int stage);
    void addEdge(int src, int dest, int weight);
    void print();
    void MSGshortestpath();
};

multistageGraph::multistageGraph(int n, int stage)
{
    V = n;
    this->stage = stage;
    adj = new vector<Edge>[V];
}

void multistageGraph::addEdge(int v, int w, int wt)
{
    Edge e;
    e.dest = w;
    e.weight = wt;
    adj[v].push_back(e);
}

void multistageGraph::print()
{
    for (int i = 0; i < V-1; i++)
    {
        cout << "Vertex " << i << " make an edge to\n";
        for (auto j = adj[i].begin(); j != adj[i].end(); j++)
        {
            cout << "\tVertex " << j->dest << " with edge weight = " << j->weight << "\n";
        }
    }
}

void multistageGraph::MSGshortestpath()
{
    //Create adjacency matrix for DP 
    int w[V][V]= {0};
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            w[i][j] = 0;
        }
    }
    for (int i = 0; i < V; i++)
    {
        for (auto j = adj[i].begin(); j != adj[i].end(); j++)
        {
            w[i][j->dest] = j->weight;
        }
    }
    
    int cost[V], path[V], shortestPath[stage]; 
    //Last node has no path. therefore its cost is also 0
    cost[V-1] = 0;
    path[V-1] = 0;
    for (int i = V - 2; i >= 0; i--)
    {
        int min = INT_MAX;
    }

    /*for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }*/

}


int main()
{
    int V = 8;
    int stage = 4;
    multistageGraph g(V, stage);
    g.addEdge(0,1,2);
    g.addEdge(0,2,1);
    g.addEdge(0,3,3);
    g.addEdge(1,4,2);
    g.addEdge(1,5,3);
    g.addEdge(2,4,6);
    g.addEdge(2,5,7);
    g.addEdge(3,4,6);
    g.addEdge(3,5,8);
    g.addEdge(3,6,9);
    g.addEdge(4,7,6);
    g.addEdge(5,7,4);
    g.addEdge(6,7,5);
    //g.print();
    g.MSGshortestpath();
    return 0;
}