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

//O(V^2)
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
    
    //cost to store the min cost from v to sink
    //path to store the shortest path take from any vertex w to sink
    //shortestPath to store the shortest path taken in each stage
    int cost[V], path[V], shortestPath[stage]; 
    //Last node has no path. therefore its cost is also 0
    cost[V-1] = 0;
    path[V-2] = INT_MAX;
    //shortestPath in stage 1 is the src vertex and in stage n is the sink vertex
    shortestPath[0] = 0;
    shortestPath[stage-1] = V-1;
    //Update cost and path
    for (int i = V - 2; i >= 0; i--)
    {
        int min = INT_MAX;
        for (int j = i + 1; j < V; j++)
        {
            if (w[i][j] != 0 && w[i][j] + cost[j] < min)
            {
                //suboptimal formula
                min = w[i][j] + cost[j];
                path[i] = j;
            }
        }
        cost[i] = min;
    }

    for(int i = 1; i < stage-1; i++)
    {
        shortestPath[i] = path[shortestPath[i-1]];
    }

    cout << "Shortest Path = ";
    for (int i = 0; i < stage; i++)
    {
        cout << shortestPath[i] << " ";
    }
    
    cout << "\nMinimum Cost = " << cost[0];

    

    /*cout << "\n";

    for (int i = 0; i < V; i++)
    {
        cout << path[i] << " ";
    }

    for (int i = 0; i < V; i++)
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