//Find shortest path for all pairs of vertices
//Doesn't work on graph with negative cycle
//Doesn't work on Undirected graph with negative weights
#include <iostream>
#include <vector>

using namespace std;

class Graph
{

private:
    int V;
    int **w;

public:
    Graph(int n);
    void addEdgeD(int src, int dest, int wt);
    void printResult();
    void floydwarshall();
};

Graph::Graph(int V)
{
    this->V = V;
    w = new int *[V];
    for (int i = 0; i < V; i++)
    {
        w[i] = new int[V];
        for (int j = 0; j < V; j++)
        {
            if ( j == i)
            {
                w[i][j] = 0;
            }
            else
            {
                w[i][j] = INT_MAX;
            }
        }
    }
}

void Graph::addEdgeD(int v, int u, int wt)
{
    w[v][u] = wt;
}

void Graph::printResult()
{
    for (int i = 0; i < V; i++)
    {
        cout << "Shortest Distance from vertex " << i << " to:" << endl;
        for (int j = 0; j < V; j++)
        {
            cout << "\tVextex " << j << " = " << w[i][j] << endl;
        }
        cout << endl;
    }
}

//O(n^3)
void Graph::floydwarshall()
{
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (w[i][k] != INT_MAX && w[k][j] != INT_MAX && w[i][k] + w[k][j] < w[i][j])
                {
                    w[i][j] = w[i][k] + w[k][j];
                }
            }
        }

    }
}

int main()
{
    int V = 4;
    Graph g(V);
    g.addEdgeD(0,3,7);
    g.addEdgeD(0,1,3);
    g.addEdgeD(1,0,8);
    g.addEdgeD(1,2,2);
    g.addEdgeD(2,0,5);
    g.addEdgeD(2,3,1);
    g.addEdgeD(3,0,2);
    g.floydwarshall();
    g.printResult();
    return 0;
}