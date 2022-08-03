#include <iostream>

using namespace std;

struct Items {
    int num;
    double profit;
    double weight;
    double ratio;
    double taken;

    //Default constructors
    Items () 
    {
        num = 0;
        profit = 0.0;
        weight = 0.0;
        ratio = 0.0;
        taken = 0.0;
    }

    //Parameterized constructors
    Items (int i, double p, double w)
    {
        num = i;
        profit = p;
        weight = w;
        ratio = p/w;
        taken = 0.0;
    }
};

void merge(Items arr[], int head, int mid, int tail)
{
    int leftSize = mid - head + 1;
    int rightSize = tail - mid;

    Items leftArr[leftSize];
    Items rightArr[rightSize];

    for (int i = 0; i < leftSize; i++)
    {
        leftArr[i] = arr[head + i];
    }
    for (int i = 0; i < rightSize; i++)
    {
        rightArr[i] = arr[mid + 1 + i];
    }

    int a = 0;
    int b = 0;
    int c = head;

    while (a < leftSize && b < rightSize)
    {
        if (leftArr[a].ratio >= rightArr[b].ratio)
        {
            arr[c] = leftArr[a];
            a++;
            c++;
        }
        else
        {
            arr[c] = rightArr[b];
            b++;
            c++;
        }
    }

    while (a < leftSize)
    {
        arr[c] = leftArr[a];
        a++;
        c++;
    }
    while (b < rightSize)
    {
        arr[c] = rightArr[b];
        b++;
        c++;
    }
}

void mergeSort(Items arr[], int head, int tail)
{
    if (head < tail)
    {
        int mid = (head+tail)/2;
        mergeSort(arr, head, mid);
        mergeSort(arr, mid+1, tail);
        merge(arr, head, mid, tail);

    }

}

//O(nlogn)
double fractKnapSack(Items item[], int n, int capacity) 
{
    double maxprofit = 0;
    double currweight = 0;
    Items sortedItems[n];
    for (int i = 0; i < n; i++)
    {
        sortedItems[i] = item[i];
    }

    mergeSort(sortedItems, 0, n-1);

    for (int i = 0; i < n; i++)
    {
        if (currweight == capacity)
        {
            item[sortedItems[i].num - 1].taken = 0;
            return maxprofit;
        }
        else if (currweight + sortedItems[i].weight < capacity)
        {
            currweight += sortedItems[i].weight;
            item[sortedItems[i].num - 1].taken = 1;
            maxprofit += sortedItems[i].profit;
        }
        else 
        {
            double remain = (double)capacity - currweight;
            currweight += remain;
            item[sortedItems[i].num - 1].taken = remain/sortedItems[i].weight ;
            maxprofit += ( item[sortedItems[i].num - 1].taken * sortedItems[i].profit);
        }
    }
    return maxprofit;
}

int main(){
    int n = 7;
    int cap = 15;
    Items obj[n] = {{1, 10, 2}, 
                    {2, 5, 3},
                    {3, 15, 5},
                    {4, 7, 7},
                    {5, 6, 1},
                    {6, 18, 4},
                    {7, 3, 1}};
    double result = fractKnapSack(obj, n, cap);
    cout << "Max profit = " << result << "\n\n";
    for (int i = 0; i < n; i++)
    {
        cout << "For item " << obj[i].num << ", we takes " << obj[i].taken << " of it." << endl; 
    }

    return 0;
}