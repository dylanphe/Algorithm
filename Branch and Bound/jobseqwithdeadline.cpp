// Solving job seq with deadline using FIFO Branch and Bound
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct Jobs {
    int j;
    int profit;
    int deadline;
    int time;

    Jobs() {
        j = 0;
        profit = 0;
        deadline = 0;
        time = 0;
    }

    Jobs(int i, int p, int dl, int t) {
        this->j = i;
        this->profit = p;
        this->deadline = dl;
        this->time = t;
    }
};

struct Node {
    int i;
    int c = 0;
    int u = INT_MAX;
    bool *path;

    Node(int n)
    {
        path = new bool[n];
        for (int i = 0; i < n; i++)
        {
            path[i] = false;
        }
    }
};

class Solution {
private: 
    int total = 0;
    int ind = 0;
    int ubound = INT_MAX;
    queue<Node> q;

    vector <int> result;
    int maxprof = 0;
public:
    bool isValid(int n, Node child, Jobs J[])
    {
        bool valid = true;
        int maxtime = 1;
        int time = 0;
        for (int i = 0; i < n; i++)
        {
            if (child.path[i] == true)
            {
                maxtime = max(maxtime, J[i].deadline);
                time += J[i].time;
                if (time > maxtime)
                {
                    valid = false;
                }
            }
        }
        return valid;
    }

    void maxprofitUtil(int n, Node node, Jobs J[])
    {
        if (node.c <= ubound)
        {
            for (int j = node.i + 1; j < n; j++)
            {
                Node child(n);
                //Set the new node path to be the same as its parent
                for (int k = 0; k < n; k++)
                {
                    child.path[k] = node.path[k];
                }
                child.path[j] = true;
                child.i = j;

                if (isValid(n, child, J))
                {
                    //Calculate cost
                    for (int i = 0; i < j; i++)
                    {
                        if (child.path[i] == false)
                        {
                            child.c += J[i].profit;
                        }
                    }
                    //Calculate upper
                    child.u = total;
                    for (int i = 0; i < n; i++)
                    {
                        if (child.path[i] == true)
                        {
                            child.u -= J[i].profit;
                        }
                    }
                    // Update ubound
                    if (child.u < ubound)
                    {
                        ubound = child.u;
                        result.clear();
                        for (int i = 0; i < n; i++)
                        {
                            if (child.path[i] == true)
                            {
                                result.push_back(i);
                            }
                        }
                    }
                    //cout << child.u << " ";
                    
                    // Add any child node that has its cost < ubound into the queue 
                    if (child.c <= ubound)
                    {
                        q.push(child);
                    }
                }
            }
        }
    }

    void maxprofit(int n, Jobs J[])
    {
        for (int i = 0; i < n; i++)
        {
            total += J[i].profit;
        }
        //First Level in SST
        while (ind < n)
        {   
            Node node(n);
            node.path[ind] = true;
            //Caluclate cost
            for (int i = 0; i < ind; i++)
            {
                node.c += J[i].profit;
            }
            node.i = ind;
            //Calculate upper
            node.u = total - J[ind].profit;
            //Update ubound to min of ubound or upper 
            if (node.u < ubound)
                    {
                        ubound = node.u;
                        result.clear();
                        for (int i = 0; i < n; i++)
                        {
                            if (node.path[i] == true)
                            {
                                result.push_back(i);
                            }
                        }
                    }
            //Add the feasible node to the queue
            if (node.c <= ubound)
            {
                q.push(node);
            }
            ind++;
        }
        
        while (!q.empty())
        {
            maxprofitUtil(n, q.front(), J);
            q.pop();
        }
        
        //Print the result
        cout << "Jobs: ";
        for (auto i = result.begin(); i != result.end(); i++)
        {
            cout << J[*i].j << " ";
            maxprof += J[*i].profit;
        }
        cout << "\nMax Profit = " << maxprof;
    }
};

int main() {
    int n = 5;
    Jobs j1(1, 15, 2, 1);
    Jobs j2(2, 10, 1, 1);
    Jobs j3(3, 20, 2, 1);
    Jobs j4(4, 1, 3, 1);
    Jobs j5(5, 5, 3, 1);
    Jobs J[n] = {j1, j2, j3, j4, j5};
    /*int n = 4;
    Jobs j1(1, 5, 1, 1);
    Jobs j2(2, 10, 3, 2);
    Jobs j3(3, 6, 2, 1);
    Jobs j4(4, 3, 1, 1);
    Jobs J[n] = {j1, j2, j3, j4};*/
    Solution s;
    s.maxprofit(n, J);
    return 0;
}