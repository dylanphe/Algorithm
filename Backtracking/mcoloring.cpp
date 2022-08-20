#include <iostream>
#include <vector>

using namespace std; 

class Graph
{
private:
    int V;
    vector <int> *adj;
    int *result;

public:
    Graph(int V);
    void addEdgeU(int u, int v);
    void printGraph();
    bool mcoloring(int m, string colors[], int k);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new vector <int> [V];
    result = new int[V];
    for (int i = 0; i < V; i++)
    {
        result[i] = -1;
    }
}

void Graph::addEdgeU(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void Graph::printGraph()
{
    for (auto i = 0; i < V; i++)
    {
        cout << "Vertex " << i << " is adjacent to: \n";
        for (auto j = adj[i].begin(); j != adj[i].end(); j++)
        {
            cout << "\tVertex " << *j << endl;
        }
    }
}

//O(Em^V)
bool Graph::mcoloring(int m, string colors[], int k)
{
    bool solved = false;
    if (k >= V)
    {
        solved = true;
        for (int i = 0; i < V; i++)
        {
            cout << colors[result[i]] << " ";
        }
        cout << endl;
        return solved;
    }
    for (int i = 0; i < m; i++)
    {
        bool match = false;
        //Checking for a possible different color from its adjacent to color the vertex
        for (auto j = adj[k].begin(); j != adj[k].end(); j++)
        {
            if (i == result[*j])
            {
                match = true;
            }
        }

        if (!match)
        {
            result[k] = i;
            if (mcoloring(m, colors, k+1))
            {
                solved = true;
            }
            result[k] = -1;
        }
    } 
    return solved;  
}

int main()
{
    /*int V = 5;
    int m = 3;
    string colors[m] = {"R", "G", "B"};
    Graph g(V);
    g.addEdgeU(0,1);
    g.addEdgeU(0,4);
    g.addEdgeU(1,2);
    g.addEdgeU(1,4);
    g.addEdgeU(2,3);
    g.addEdgeU(2,4);
    g.addEdgeU(3,4);*/

    int V = 4;
    int m = 2;
    string colors[m] = {"R", "G"};
    Graph g(V);
    g.addEdgeU(0,1);
    g.addEdgeU(1,2);
    g.addEdgeU(2,3);
    g.addEdgeU(3,0);
    //g.printGraph();
    if (!g.mcoloring(m, colors, 0))
    {
        cout << "No Solution!" << endl;
    }
    return 0;
}