#include <iostream>

using namespace std;

void merge(int arr[], int first, int mid, int last)
{
    //Fill up left and right subarrays with elements to sort and merge
    int leftSize = mid - first + 1;
    int rightSize = last - mid;
    int leftArr[leftSize];
    int rightArr[rightSize];
    for (int i = 0; i < leftSize; i++)
    {
        leftArr[i] = arr[first + i];
    }
    for (int i = 0; i < rightSize; i++)
    {
        rightArr[i] = arr[mid + 1 + i];
    }

    //Sort and Merge the element.
    int a = 0, b = 0, c = first;
    while ( a < leftSize && b < rightSize)
    {
        if (leftArr[a] <= rightArr[b])
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

    //Copy remaining elements
    while(a < leftSize)
    {
        arr[c] = leftArr[a];
        a++;
        c++;
    }
    while(b < rightSize)
    {
        arr[c] = rightArr[b];
        b++;
        c++;
    }

}

void mergeSort (int arr[], int const first, int const last)
{
    // if problem is large.
    if (first < last) 
    {
        int mid = (first + last)/2;
        //divide left subarray
        mergeSort(arr, first, mid);
        //divide right subarray
        mergeSort(arr, mid+1, last);
        //merge them back
        merge(arr, first, mid, last);
    }
}

int main()
{
    int List[11] = {2, 5, 10, 34, 60, 30, 42, 59, 4, 20, 50};
    int n = sizeof(List)/sizeof(List[0]);
    cout << "List (Before): ";
    for (int i = 0; i < n; i++)
    {
        cout << List[i] << " ";
    }
    cout << endl;
    mergeSort(List, 0, n-1);
    cout << "List (After): ";
    for (int i = 0; i < n; i++)
    {
        cout << List[i] << " ";
    }

    return 0;
}