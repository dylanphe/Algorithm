#include <iostream>
#include <algorithm>

using namespace std;

struct Job 
{
    int num;
    double profit;
    int deadline;

    //Default constructor
    Job()
    {
        num = 0;
        profit = 0;
        deadline = 0;
    }

    Job(int i, double p, int dl)
    {
        num = i;
        profit = p;
        deadline = dl;
    }
};

void merge(Job arr[], int head, int mid, int tail)
{
    int leftSize = mid - head + 1;
    int rightSize = tail - mid;
    Job leftArr[leftSize];
    Job rightArr[rightSize];

    for (int i = 0; i < leftSize; i++)
    {
        leftArr[i] = arr[head + i];
    }

    for (int i = 0; i < rightSize; i++)
    {
        rightArr[i] = arr[mid + 1+ i];
    }

    int a = 0, b = 0, c = head;
    while (a < leftSize && b < rightSize )
    {
        if (leftArr[a].profit >= rightArr[b].profit)
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

void mergeSort(Job arr[], int head, int tail)
{
    if (head < tail)
    {
        int mid = (head + tail)/2;
        mergeSort(arr, head, mid);
        mergeSort(arr, mid + 1, tail);
        merge(arr, head, mid, tail);
    }
}

//Time complexity: O(n^2)
double jobSeq (Job arr[], int n)
{
    double maxprofit = 0;

    Job sortedJobs[n];
    for (int i = 0; i < n; i++)
    {
        sortedJobs[i] = arr[i];
    }

    //Figuring out the number of slots for the sequence of jobs
    int m = 0;
    for (int i = 0; i < n; i++)
    {
        m = max(m, arr[i].deadline);     
    }

    //Initialize all slots as free
    //0 means slot is free
    //1 means slot is taken
    int slot[m] = {0};

    //Sort the given jobs in a decreasing order of profit
    mergeSort(sortedJobs, 0, n-1);
    
    //For each job in the sorted order, find the slot for them.
    for (int i = 0; i < n; i++)
    {
        for (int j = m; j > 0 ; j--)
        {
            //Slot chosen should be the first free largest spot avaliable that is before or equal to the job deadline
            if (j <= sortedJobs[i].deadline && slot[j-1] == 0)
            {
                slot[j-1] = sortedJobs[i].num;
                maxprofit += sortedJobs[i].profit;
                break;
            }
        }
    }

    for (int i = 0; i < m; i++)
    {
        cout << slot[i] << " ";
    }
    return maxprofit;

}

int main()
{
    int n = 5;
    Job jobs[n] = { {1, 15, 2},
                    {2, 10, 1},
                    {3, 20, 2},
                    {4, 1, 3},
                    {5, 5, 3}   };
    double result = jobSeq(jobs, n);
    cout << endl << "Max Profit = " << result;
    return 0;
}