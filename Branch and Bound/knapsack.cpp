// Solving 0/1knapsack problem using branch and bound

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct Item {
    int num;
    double profit;
    double weight;
    double ratio;
    double negprofit;
    
    Item() {
        num = 0;
        profit = 0;
        weight = 0;
        ratio = 0;
    }

    Item(int i, double p, double wt) {
        num = i;
        profit = p;
        negprofit = (-2 * p) + p;
        weight = wt;
        ratio = p/wt;
    }
};

struct Node {
    int i;
    int c;
    int u;
    double currwt;
    bool *path;

    Node(int n) {
        u = 0;
        c = 0;
        path = new bool[n];
        for (int i = 0; i < n; i++)
        {
            path[i] = true;
        }
    }
};

class Solution {
private:
    double ubound = INT_MAX;
    queue<Node> q;
public:

    void merge(Item items[], int head, int mid, int tail)
    {
        int leftSize = mid - head + 1;
        int rightSize = tail - mid;

        Item leftArr[leftSize];
        Item rightArr[rightSize];

        for (int i = 0; i < leftSize; i++)
        {
            leftArr[i] = items[head + i];
        }
        for (int i = 0; i < rightSize; i++)
        {
            rightArr[i] = items[mid + 1 + i];
        }
        int a = 0;
        int b = 0;
        int c = head;

        while (a < leftSize && b < rightSize)
        {
            if (leftArr[a].ratio > rightArr[b].ratio)
            {
                items[c] = leftArr[a];
                a++;
                c++;
            }
            else
            {
                items[c] = rightArr[b];
                b++;
                c++;
            }
        }

        while (a < leftSize)
        {
            items[c] = leftArr[a];
            a++;
            c++;
        }
        while (b < rightSize)
        {
            items[c] = rightArr[b];
            b++;
            c++;
        }
    }

    void mergeSort(Item items[], int head, int tail)
    {
        if(head < tail)
        {
            int mid = (head+tail)/2;
            mergeSort(items, head, mid);
            mergeSort(items, mid+1, tail);
            merge(items, head, mid, tail);
        }
    }

    void knapsackUtil(int n, double m, Item sortedItems[], Node node)
    {
        if (node.i < n) 
        {
            if (node.u <= ubound)
            {
                if (node.currwt + sortedItems[node.i].weight <= m) 
                {
                    Node child1(n);
                    child1.i = node.i + 1;
                    child1.currwt = node.currwt;
                    for (int i = 0; i < n; i++)
                    {
                        child1.path[i] = node.path[i];
                    }
                    child1.currwt += sortedItems[node.i].weight;
                    child1.c = node.c;
                    child1.u = node.u;
                    //cout << node.c << " ";
                    //cout << node.u << " ";
                    //Update ubound
                    if (child1.u <= ubound) {
                        ubound = child1.u;
                    }
                    //Add to queue
                    if (child1.c <= ubound ) {
                        q.push(child1);
                    }

                    if (child1.u == child1.c && node.i == n-1)
                    {
                        double profit = 0;
                        cout << "Items = ";
                        for (int i = 0; i < n; i++)
                        {
                            if(child1.path[i] == true)
                            {
                                cout << sortedItems[i].num << " ";
                                profit += sortedItems[i].profit;
                            }
                        }
                        cout << "\nProfit = " << profit;
                    }
                }

                Node child2(n);
                for (int i = 0; i < n; i++)
                {
                    child2.path[i] = node.path[i];
                }
                child2.path[node.i] = false;
                
                /*for (int i = 0; i < n; i++)
                {
                    cout << child2.path[i] << " ";
                }*/
                
                child2.i = node.i + 1;
                child2.currwt = node.currwt - sortedItems[node.i].weight;
                 //Find c and u
                double total_weight = 0;
                for (int i = 0; i < n; i++)
                {
                    if (child2.path[i] == true) {
                        if (total_weight + sortedItems[i].weight <= m)
                        {
                            child2.u += sortedItems[i].negprofit;
                            child2.c += sortedItems[i].negprofit;
                            total_weight += sortedItems[i].weight;
                        }
                        else {
                            double remain = m - total_weight;
                            child2.c += (sortedItems[i].negprofit * remain /sortedItems[i].weight);
                            total_weight += remain;
                        }
                    }
                }
                //cout << child2.c << " ";
                //cout << child2.u << " ";

                //Update ubound
                if (child2.u < ubound) 
                {
                    ubound = child2.u;
                }
                //Add to queue
                if (child2.u <= ubound) 
                {
                    q.push(child2);
                }

                if (child2.u == child2.c && node.i == n-1)
                {
                    double profit = 0;
                    cout << "Items to take = ";
                    for (int i = 0; i < n; i++)
                    {
                        if(child2.path[i] == true)
                        {
                            cout << sortedItems[i].num << " ";
                            profit += sortedItems[i].profit;
                        }
                    }
                    cout << "\nMax Profit = " << profit;
                }
            }
        }
        return;
    }

    void knapsack(int n, double m, Item items[]) {
        
        //sortitem in a greedy way by ratio
        Item sortedItems[n];
        for (int i = 0; i < n; i++)
        {
            sortedItems[i] = items[i];
        }
        mergeSort(sortedItems, 0, n-1);
        /*for (int i = 0; i < n; i++)
        {
            cout << sortedItems[i].num << " ";
        }*/

        Node node(n);
        node.i = 0;
        node.currwt = 0;
        
        //Find c and u
        double total_weight = 0;
        for (int i = 0; i < n; i++)
        {
            if (total_weight + sortedItems[i].weight <= m)
            {
                node.u += sortedItems[i].negprofit;
                total_weight += sortedItems[i].weight;
            }
            else {
                node.c = node.u;
                double remain = m - total_weight;
                node.c += (sortedItems[i].negprofit * remain /sortedItems[i].weight);
                total_weight += remain;
            }
        }
        //cout << node.c << " ";
        //cout << node.u << " ";

        //Update ubound
        if (node.u < ubound) {
            ubound = node.u;
        }
        //cout << ubound;

        //Add to queue
        if (node.u <= ubound) {
            q.push(node);
        }

        //While there are still node to process
        while (!q.empty())
        {
            knapsackUtil(n, m, sortedItems, q.front());
            q.pop();
        }
        
    }
};

int main()
{
    int n = 4;
    double m = 15;
    Item i1(1,10,2);
    Item i2(2,10,4);
    Item i4(3,18,9);
    Item i3(4,12,6);
    Item items[n] = {i1, i2, i3, i4};
    Solution s;
    s.knapsack(n, m, items);
}