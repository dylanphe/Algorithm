    for (auto i = adj[v].begin(); i != adj[v].end(); i++)
            {
                if (!visited[i->dest])
                {
                    heapinsert(minHeap, *i);
                }
            }
            cout << v << " ";