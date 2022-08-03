#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

void swap (int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

int tailPartition (int arr[], int head, int tail)
{
    int pivot = arr[tail];
    int i = head - 1;
    for (int j = head; j <= tail; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[tail]);
    return (i+1);
}

int headPartition (int arr[], int head, int tail)
{
    int pivot = arr[head];
    int i = head;
    int j = tail;
    while (i < j)
    {
        while ( pivot >= arr[i])
        {
            i++;
        }
        while (pivot < arr[j])
        {
            j--;
        }
        if (i < j)
        {
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[head], arr[j]);
    return j;
}

int midPartition (int arr[], int head, int tail)
{
    int mid = (head + tail)/2;
    int pivot = arr[mid];
    int i = head;
    int j = tail;
    while (i < j)
    {
        while ( pivot > arr[i])
        {
            i++;
        }
        while (pivot < arr[j])
        {
            j--;
        }
        if (i < j)
        {
            swap(arr[i], arr[j]);
        }
    }
    return j;
}

int randPivot(int arr[], int head, int tail)
{
    srand(time(NULL));
    int indexPivot = head + rand() % (tail - head);
    swap(arr[indexPivot], arr[tail]);
    return tailPartition(arr, head, tail);
}


void quickSort(int arr[], int head, int tail)
{
    if (head < tail)
    {
        int j = randPivot(arr, head, tail);
        quickSort(arr, head, j-1);
        quickSort(arr, j+1, tail);
    }
}

int main()
{
    int List[11] = {40, 5, 10, 34, 60, 30, 42, 59, 4, 20, 50};
    //int List[5] = {2,4,5,3,1};
    int n = sizeof(List)/sizeof(List[0]);
    cout << "List (Before): ";
    for (int i = 0; i < n; i++)
    {
        cout << List[i] << " ";
    }
    cout << endl;

    quickSort(List, 0, n-1);

    cout << "List (After): ";
    for (int i = 0; i < n; i++)
    {
        cout << List[i] << " ";
    }

    return 0;
}