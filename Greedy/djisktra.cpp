//Pro: work on both Directed and Undirected Graph
//Con: doesn't work on graph with negative weight
#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
    int dest;
    int weight;
};

void swap(int x, int y)
{
    int temp = x;
    x = y;
    y = temp;
}

void heapinsert(vector<Edge> &heap, Edge e)
{
    heap.push_back(e);
    int n = heap.size() - 1;
    while (n >= 1)
    {
        if (n%2 == 0)
        {
            if (heap[n/2 -1].weight > heap[n].weight)
            {   
                swap(heap[n], heap[n/2-1]);
            }
            n = n/2 -1;
        }
        else if (n%2 != 0)
        {
            if (heap[n/2].weight > heap[n].weight)
            {   
                swap(heap[n], heap[n/2]);
            }
            n = n/2;
        }
    }
}

void heapify(vector<Edge> &heap, int i)
{
    int n = heap.size() -1;
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left <= n && heap[left].weight < heap[smallest].weight)
    {
        smallest = left;
    }
    
    if (right <= n && heap[right].weight < heap[smallest].weight)
    {
        smallest = right;
    }
    
    if (smallest != i)
    {
        swap(heap[i], heap[smallest]);
        heapify(heap, smallest);
    }
}

int heapextract(vector<Edge> &heap)
{
    int n = heap.size() - 1;
    int temp = heap[0].dest;
    swap(heap[0], heap[n]);
    heap.pop_back();
    for (int i = n/2 - 1; i >= 0; i--)
    {
        heapify(heap, i);
    }
    return temp;
}

/*void heapdelete(vector<Edge> &heap)
{
    int n = heap.size() - 1;
    if (n==0)
    {
       ;
    }
    else 
    {
        swap(heap[0], heap[n]);
        heap.pop_back();
        for (int i = n/2 - 1; i >= 0; i--)
        {
            heapify(heap, i);
        }
    }
}*/

class Graph 
{
private:
    int V;
    vector <Edge> *adj;

public:
    Graph(int V);
    void addEdgeU(int src, int dest, int weight);
    void addEdgeD(int src, int dest, int weight);
    void print();
    void relaxation();
    void djisktra(int src);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new vector<Edge>[V];
}

void Graph::addEdgeD(int v, int w, int wt)
{
    Edge e1;
    e1.dest = w;
    e1.weight = wt;
    adj[v].push_back(e1);

}

void Graph::addEdgeU(int v, int w, int wt)
{
    Edge e1;
    e1.dest = w;
    e1.weight = wt;
    Edge e2;
    e2.dest = v;
    e2.weight = wt;
    adj[v].push_back(e1);
    adj[w].push_back(e2);

}

void Graph::print()
{
    for (auto i = 0; i < V; i++)
    {
        cout << "Vertex " <<  i  <<  " is adjacent to:\n";
        for (auto j = adj[i].begin(); j != adj[i].end(); j++)
        {
            cout << "\tVertex " << j->dest << " with weight = " << j->weight << endl;
        }
    }
}


//O(ElogV)
void Graph::djisktra(int src)
{
    //initialize cost[] and visited for relaxation
    int dist[V] = {0};
    bool visited[V];
    //O(V)
    for (int i = 0; i < V; i++)
    {
        if (i != src)
        {
            dist[i] = INT_MAX;
            visited[i] = false;
        }
        else 
        {
            visited[i] = true;
        }
    }
    
    //O(ElogV)
    vector<Edge> minHeap;
    for (auto i = adj[src].begin(); i != adj[src].end(); i++)
    {
        heapinsert(minHeap, *i);
        dist[i->dest] = i->weight;
    }

    //O(ElogV)
    while (!minHeap.empty())
    {
        int v = heapextract(minHeap);
        if (!visited[v])
        {
            visited[v] = true;
            if (!adj[v].empty())
            {
                for (auto i = adj[v].begin(); i != adj[v].end(); i++)
                {
                    if (!visited[i->dest])
                    {
                        heapinsert(minHeap, *i);
                        //Relaxation
                        if (dist[v] + i->weight < dist[i->dest])
                        {
                            dist[i->dest] = dist[v] + i->weight;
                        }
                    }
                }
            }
        }
        //cout << endl;
        //cout << v << " ";
    }
    //Print Result 
    cout << "Shortest distance from vertex " << src << " to:" << endl; 
    for (int i = 1; i < V; i++)
    {
        cout << "\tvertex " << i << " = " << dist[i] << endl;

    }


}

int main()
{
    int V = 6;
    Graph g(V);
    g.addEdgeD(0,1,2);
    g.addEdgeD(0,2,4);
    g.addEdgeD(1,2,1);
    g.addEdgeD(1,3,7);
    g.addEdgeD(2,4,3);
    g.addEdgeD(3,5,1);
    g.addEdgeD(4,3,2);
    g.addEdgeD(4,5,5);

    /*g.addEdgeU(0,1,4);
    g.addEdgeU(0,7,8);
    g.addEdgeU(1,7,11);
    g.addEdgeU(1,2,8);
    g.addEdgeU(2,3,7);
    g.addEdgeU(2,5,4);
    g.addEdgeU(2,8,2);
    g.addEdgeU(3,4,9);
    g.addEdgeU(3,5,14);
    g.addEdgeU(4,5,10);
    g.addEdgeU(5,6,2);
    g.addEdgeU(6,7,1);
    g.addEdgeU(6,8,6);
    g.addEdgeU(7,8,7);*/
    //g.print();
    g.djisktra(0);
    return 0;
}