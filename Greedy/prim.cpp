#include <iostream>
#include <vector>
using namespace std;


//Using minheap and adjacency list

struct Edge{
    int dest;
    int weight;
};

void swap (int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

void heapInsert(vector<int> &heap, int node, int key[])
{
    heap.push_back(node);
    int n = heap.size() - 1;
    while (n >= 1)
    {
        if (n%2 == 0)
        {
            if (key[n] < key[(n/2)-1])
            {
                swap(heap[n], heap[n/2-1]);
            }
            n = n/2-1;
        }
        else 
        {
            if (key[n] < key[n/2])
            {
                swap(heap[n], heap[n/2]);
            }
            n=n/2;
        }
        
    }
}

void heapify(vector<int>  &heap, int key[], int i)
{
    int n = heap.size();
    for (int i = (n/2) - 1; i >= 0; i--)
    {
        int smallest = i;
        int left = 2*i + 1;
        int right = 2*i + 2;

        if (left < n && key[heap[left]] < key[heap[smallest]])
        {
            smallest = left;
        }
        
        if (right < n && key[heap[right]] < key[heap[smallest]])
        {
            smallest = right;
        }

        if (smallest != i)
        {
            swap(heap[smallest], heap[i]);
            heapify(heap, key, smallest);
        }
    }

}

int heapDelete(vector<int> &heap, int key[])
{
    int n = heap.size() - 1;
    int i = 0;
    int temp = heap[i];
    swap(heap[i], heap[n]);
    heap.pop_back();
    return temp;
}

bool notIn (vector<int> MST, int key)
{
    for (auto i = MST.begin(); i != MST.end(); i++)
    {
        if (key == *i)
        {
            return false;
        }
    }
    return true;
}

void PrimMST(vector <Edge> G[], int V)
{
    int cost = 0;
    vector<int> MST;
    int key[V];
    key[0] = 0;

    //O(V)
    for (int i = 1; i < V; i++)
    {
        key[i] = INT_MAX;
    }

    //O(VlogV)
    vector<int> minHeap;
    for (int i = 0; i < V; i++)
    {
        heapInsert(minHeap, i, key);
    }

    //O((V*E)+V) = O(V^2)? why not O(ElogV)?
    while(!minHeap.empty())
    {
        //O(1) Extract the top node from minHeap
        int node = heapDelete(minHeap, key);
        int n = minHeap.size();
        MST.push_back(node);
        cost += key[node];
        
        //Updating Key Values O(E+V)
        for (auto i = G[node].begin(); i != G[node].end(); i++)
        {
            if (notIn(MST,i->dest))
            {
                key[i->dest] = i->weight;
            }
        }

        //O(logn) Heapify minHeap after update key values
        for (int i = n/2 - 1; i >= 0; i--)
        {
            heapify(minHeap, key, i);
        }

    }

    //Print result
    for (auto j = MST.begin(); j != MST.end(); j++)
    {
            cout << *j << " ";
    }

    if (cost > 0) 
    {
        cout << "\nMinimum Cost = " << cost;
    }
    else 
    {
        cout << "\nMinimum Cost = Error (Disconnected Graph)";
    }

}

void printGraph(vector <Edge> G[], int V)
{
    for (int i = 0; i < V; i++)
    {
        cout << "Vertex " << i << " make an edge with \n";
        for (auto j = G[i].begin(); j != G[i].end(); j++)
        {
            cout << "\tVertex " << j->dest << " with edge weight =" << j->weight << "\n";
        }
        cout << "\n";
    }
}

void addedge(vector<Edge> G[], int v, int w, int wt)
{
    G[v].push_back({w, wt});
    G[w].push_back({v, wt});
}

int main(){
    int V = 7;
    vector<Edge> G[V];
    addedge(G, 0, 5, 10);
    addedge(G, 0, 1, 28);
    addedge(G, 1, 2, 16);
    addedge(G, 1, 6, 14);
    addedge(G, 3, 2, 12);
    addedge(G, 4, 3, 22);
    addedge(G, 5, 4, 25);
    addedge(G, 6, 4, 24);
    addedge(G, 6, 3, 18);

    /*addedge(G, 0, 5, 10);
    addedge(G, 0, 1, 28);
    addedge(G, 1, 6, 14);
    addedge(G, 3, 2, 12);
    addedge(G, 4, 3, 22);
    addedge(G, 5, 6, 25);
    addedge(G, 2, 4, 18);*/

    printGraph(G, V);
    PrimMST(G, V);
    return 0;
}