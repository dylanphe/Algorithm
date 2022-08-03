#include <iostream>
#include <vector>

using namespace std;

//graph 
struct Edge
{
    int dest;
    int weight;
};

void addEdge(vector<Edge> G[], int v, int u, int wt)
{
    G[v].push_back({u, wt});
    G[u].push_back({v, wt});
}

void printGraph(vector<Edge> G[], int V)
{
    for (int i = 0; i < V; i++)
    {
        cout << "Vertex " << i << " make an edge with\n";
        for (auto j = G[i].begin(); j != G[i].end(); j++)
        {
            cout << "\tVertex " << j->dest << " with edge weight = " << j->weight << "\n";
        }
    }

}

void merge(vector<vector <int>> &list, int head, int mid, int tail)
{
    int leftSize = mid - head + 1;
    int rightSize = tail - mid;
    vector<vector <int>> leftVec;
    vector<vector <int>> rightVec;

    for (int i = 0; i < leftSize; i++)
    {
        leftVec.push_back(list[head + i]);
    }
    for (int i = 0; i < leftSize; i++)
    {
        rightVec.push_back(list[mid + 1 + i]);
    }

    int a=0, b=0, c=head;
    while (a < leftSize && b < rightSize )
    {
        if (leftVec[a][2] <= rightVec[b][2])
        {
            list[c] = leftVec[a];
            a++;
            c++;
        }
        else
        {
            list[c] = rightVec[b];
            b++;
            c++;
        }
    }

    //Copy remaining elements
    while(a < leftSize)
    {
        list[c] = leftVec[a];
        a++;
        c++;
    }
    while(b < rightSize)
    {
        list[c] = rightVec[b];
        b++;
        c++;
    }
}

void mergesort(vector<vector <int>> &list, int head, int tail)
{
    if (head < tail)
    {
        int mid = (head + tail)/2;
        mergesort(list, head, mid);
        mergesort(list, mid+1, tail);
        merge(list, head, mid, tail);
    }
}

//collapsing find
int find (int v, int parent[])
{
    if (parent[v] < 0)
    {
        return v;
    }
    
    return find(parent[v], parent); 

}

//weighted union
void weightedUnion (int v, int w, int parent[])
{
    int s1 = find(v, parent);
    int s2 = find(w, parent);

    if (parent[s1] <= parent[s2])
    {
        parent[s1] += parent[s2];
        parent[s2] = s1;
    }
    else
    {
        parent[s2] += parent[s1];
        parent[s1] = s2;
    }

}

void kruskal(vector<vector <int>> &list, int V)
{
    int cost = 0;
    int parent[V];
    for (int i = 0; i < V; i++)
    {
        parent[i] = -1;
    }

    mergesort(list, 0, list.size()-1);
    
    cout << "MST included the edges below: \n" << endl;
    for (auto i = 0; i < list.size(); i++)
    {
        if (find(list[i][0], parent) != find(list[i][1], parent))
        {
            cout << list[i][0] << " adjacent to ";
            cout << list[i][1] << " of weight = " << list[i][2];
            weightedUnion(list[i][0], list[i][1], parent);
            cost += list[i][2];
            cout << endl;
        }
    }

    cout << "\nTotal minimum cost = " << cost;
    cout << "\n";
    for (int i = 0; i < V; i++)
    {
        cout << parent[i] << " ";
    }
    cout << endl;

}

int main()
{
    int V = 7;
    vector<Edge> G[V];
    addEdge(G, 0, 5, 10);
    addEdge(G, 0, 1, 28);
    addEdge(G, 1, 6, 14);
    addEdge(G, 3, 2, 12);
    addEdge(G, 4, 3, 22);
    addEdge(G, 5, 6, 25);
    addEdge(G, 2, 4, 18);

    //Creating a vector of all edges and its weight
    vector<vector <int>> edgesList;
    for (int i = 0; i < V; i++)
    {
        for (auto j = G[i].begin(); j != G[i].end(); j++)
        {
            if (j->dest > i)
            {
                edgesList.push_back({i, j->dest, j->weight});
            }
        }
    }
    
    kruskal(edgesList, V);
    //printGraph(G, V);
    return 0;
}