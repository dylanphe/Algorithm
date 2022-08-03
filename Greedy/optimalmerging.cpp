#include <iostream>

using namespace std;

struct List {
    string name;
    int size;
};

void merge(List arr[], int head, int mid, int tail)
{
    int leftSize = mid - head + 1;
    int rightSize = tail - mid;

    List leftArr[leftSize];
    List rightArr[rightSize];

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
        if (leftArr[a].size <= rightArr[b].size)
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

void mergeSort(List arr[], int head, int tail)
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
void optMerge(List arr[], int n)
{
    int cost = 0;
    int total = 0;
    
    //O(nlogn)
    mergeSort(arr, 0, n-1);
    
    // Order of merging
    cout << "First, merge list " << arr[0].name << " and " << arr[1].name << endl;;  
    cost += (arr[0].size + arr[1].size);
    total = cost;

    //O(n)
    for (int i = 2; i < n; i ++)
    {
        cout << "Then merge that list with " << arr[i].name << endl;
        cost += arr[i].size;
        total += cost;
    }
    
    cout << "\nTotal cost of merging is " << total;
}

int main(){
    int n = 0;
    cout << "How many lists do you want to merge? ";
    cin >> n;
    List lists[n]; 
    cout << "\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Enter the name for list " << i+1 << ": ";
        cin >> lists[i].name;
        cout << "Enter the size for list " << i+1 << ": ";
        cin >> lists[i].size;
        cout << endl;
    }


    cout << "\n";

    /*for (int i = 0; i < n; i++)
    {
        cout << lists[i].name << " ";
        cout << lists[i].size << endl;
    }*/

    optMerge(lists, n);
    
    return 0;
}