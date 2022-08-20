#include <iostream>
#include <vector>
#include <queue>
#include <stack> 
using namespace std;

struct Edge
{
    int dest;
};

class Graph
{
private:
    int V;
    vector<Edge> *adj;
public:
    Graph(int V);
    void addEdgeU(int src, int dest);
    //void addEdgeD(int src, int dest);
    void bfs(int src);
    void dfs(int src);
    void printGraph();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new vector<Edge>[V];
}

void Graph::addEdgeU(int v, int w)
{
    Edge e1;
    e1.dest = v;
    Edge e2;
    e2.dest = w;
    adj[v].push_back(e2);
    adj[w].push_back(e1);
}

void Graph::printGraph()
{
    for (int i=0; i < V; i++)
    {
        cout << "Vertex " << i << " is adjacent to:\n";
        for (auto j = adj[i].begin(); j != adj[i].end(); j++)
        {
            cout << "\tVertex " << j->dest << endl;
        }
    }
}

void Graph::bfs(int src)
{
    bool visited[V] = {0};
    queue<int> q;
    q.push(src);
    visited[src] = true;
    cout << "BFS = ";
    while (!q.empty())
    {
        int v = q.front();
        cout << v << " ";
        for (auto i = adj[v].begin(); i != adj[v].end(); i++)
        {
            if (!visited[i->dest])
            {
                q.push(i->dest);
                visited[i->dest] = true;
            }
        }
        q.pop();
    }
    cout << endl;
}

void Graph::dfs(int src)
{
    bool visited[V] = {0};
    stack<int> s;
    s.push(src);
    visited[src] = true;
    cout << "DFS = ";
    while (!s.empty())
    {
        int v = s.top();
        s.pop();
        cout << v << " ";
        for (auto i = adj[v].begin(); i != adj[v].end(); i++)
        {
            if (!visited[i->dest])
            {
                s.push(i->dest);
                visited[i->dest] = true;
            }
        }
    }
}

int main()
{
    int V = 10;
    Graph g(V);
    g.addEdgeU(0,1);
    g.addEdgeU(0,3);
    g.addEdgeU(1,3);
    g.addEdgeU(1,4);
    g.addEdgeU(1,6);
    g.addEdgeU(1,7);
    g.addEdgeU(2,3);
    g.addEdgeU(2,8);
    g.addEdgeU(2,9);
    g.addEdgeU(4,5);
    g.addEdgeU(4,6);
    g.addEdgeU(4,7);
    g.addEdgeU(6,7);
    g.printGraph();
    g.bfs(0);
    g.dfs(0);
    return 0;
}