#include <iostream>
#include <algorithm>

using namespace std;

struct Item
{
    int num;
    int profit;
    int weight;
};

void AONknapsack(Item item[], int n, int cap)
{
    //2D array ks for DP to include or not include the item for max profit
    int ks[n][cap+1];
    //AON table of 0 and 1 to check if the item is included
    int AON[n] = {0};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < cap+1; j++)
        {
            //If weight is 0
            if (j==0)
            {
                ks[i][j] = 0;
            }
            //If the item weight is smaller than the weight considered, we include that if it increases our profit
            else if (item[i].weight <= j)
            {
                if (i == 0)
                {
                    ks[i][j] = item[i].profit;
                }
                else
                {
                    if (ks[i-1][j - item[i].weight] + item[i].profit > ks[i-1][j])
                    {
                        ks[i][j] = ks[i-1][j - item[i].weight] + item[i].profit;
                    }
                    else 
                    {
                        ks[i][j] = ks[i-1][j];
                    }
                }
            }
            //If not, we simply set it to the last value
            else if (item[i].weight > j)
            {
                if (i == 0)
                {
                    ks[i][j] = 0;
                }
                else 
                {
                    ks[i][j] = ks[i-1][j];
                }
            }
        }
    }

    /*for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < cap + 1; j++)
        {
            cout << ks[i][j] << " ";
        }
        cout << endl;
    }*/

    //Fill up AON array for all items 0 = not included, 1 = included
    int i = n-1, j = cap;
    while (i >= 0 && j > 0)
    {
        if (ks[i][j] != ks[i-1][j])
        {
            AON[i] = 1;
            j = j - item[i].weight;
            i--;
        }
        else
        {
            AON[i] = 0;
            i--;
        }
    }

    //Print result
    for (int i = 0; i < n; i++)
    {
        if (AON[i] == 0)
        {
            cout << "Item " << item[i].num << " is not included." << endl;
        }
        else
        {
            cout << "Item " << item[i].num << " is included." << endl;   
        }
    }
}

int main()
{
    int N = 4;
    int cap = 8;
    Item item[N];
    item[0].num = 1;
    item[0].profit = 1;
    item[0].weight = 2;

    item[1].num = 2;
    item[1].profit = 2;
    item[1].weight = 3;

    item[2].num = 3;
    item[2].profit = 5;
    item[2].weight = 4;
    
    item[3].num = 4;
    item[3].profit = 6;
    item[3].weight = 5;
    AONknapsack(item, N, cap);
    return 0;
}