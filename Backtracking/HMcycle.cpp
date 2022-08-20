#include <iostream>
#include <vector>

using namespace std;

class Graph
{
private:
    int V;
    vector <int> *adj;
    int *hmcycle; 
public: 
    Graph(int n);
    void addEdgeU(int u, int v);
    void printGraph();
    void printResult();
    void halmitoniancycle(int k, int src);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new vector <int> [V];
    hmcycle = new int[V+1];
    for (int i = 0; i < V+1; i++)
    {
        hmcycle[i] = 0;
    }
}

void Graph::addEdgeU(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void Graph::printGraph()
{
    for (int i = 0; i < V; i++)
    {
        cout << "Vertex " << i << " is adjacent to:\n";
        for (auto j : adj[i])
        {
            cout << "\tVertex " << j << endl; 
        }
    }
}

void Graph::printResult()
{
    for (int i = 0; i < V+1; i++)
    {
        if (i < V)
        {
            cout << hmcycle[i] << " -> ";;
        }
        else
        {
            cout << hmcycle[i];
        }
    }
    cout << endl;
}

//O(EV^V) or O(V!)
void Graph::halmitoniancycle(int k, int src)
{

    if (k >= V)
    {
        printResult();
        return;
    }


    for (auto j : adj[src])
    {
        //Check for duplicate
        bool dup = false;
        for (int i = 0; i <= k-1; i++)
        {
            if (k > 0)
            {
                if (j == hmcycle[i])
                {
                    dup = true;
                }
            }
        }

        //Checking if the last node has an edge back to src
        bool tosrc = false;
        if (k == (V-1))
        {
            if (j == 0)
            {
                tosrc = true;
            }
        }

        if (k < (V-1))
        {
            if (!dup)
            {
                hmcycle[k+1] = j;
                halmitoniancycle(k+1, j);
            }
        }
        else 
        {
            if (tosrc)
            {
                hmcycle[k+1] = j;
                halmitoniancycle(k+1, j);
            }
        }
    }
    return;
}

int main()
{
    /*int V = 6;
    Graph g(V);
    g.addEdgeU(0,1);
    g.addEdgeU(0,2);
    g.addEdgeU(0,5);
    g.addEdgeU(1,2);
    g.addEdgeU(1,4);
    g.addEdgeU(1,5);
    g.addEdgeU(2,3);
    g.addEdgeU(3,4);
    g.addEdgeU(4,5);*/
    int V = 4;
    Graph g(V);
    g.addEdgeU(0,1);
    g.addEdgeU(1,2);
    g.addEdgeU(2,3);
    g.addEdgeU(3,0);
    //g.printGraph();
    g.halmitoniancycle(0, 0);
    return 0;
}
