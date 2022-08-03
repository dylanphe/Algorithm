/*
-Min Heap: Minimum as root.
-Max Heap: Maximum as root.
-For i > 1,
    For even i, its parent is (i/2 - 1)
    For odd i, its parent is (i/2)
    Its children are (2*i + 1) and (2*i - 1)

-Insertion 
    Loop method:
        1. Insert at n-1
        2. Iteratively compare with parents and swap to create heap using while loop. (Bottom up fashion)

-Deletion
    Recursion method:
        1. Swap root and the last element.
        2. Delete the last element after swapping.
        3. Using iterative loop, recursively heapify starting from the last parent. (Top-down fashion)

-Sort
    1. Insert all element into heap.
    2. Delete all element one by one from heap.    
*/

#include <iostream>
#include <vector>

using namespace std;

void swap(int &x, int &y)
{
    int temp = x;
    x =y;
    y = temp;
}

void minInsertion (int key, vector<int> &heap)
{
    heap.push_back(key);
    int n = heap.size() - 1; 
    while (n >= 1)
    {
        if (n%2 == 0)
        {
            if (heap[n] < heap[(n/2) - 1])
            {
                swap(heap[n], heap[(n/2) - 1]);
            }
            n = (n/2) - 1;
        }
        else
        {
            if (heap[n] < heap[n/2])
            {
                swap(heap[n], heap[n/2]);
            }
            n = n/2;
        }
    }
}

void maxInsertion (int key, vector<int> &heap)
{
    heap.push_back(key);
    int n = heap.size() - 1; 
    while (n >= 1)
    {
        if (n%2 == 0)
        {
            if (heap[n] > heap[(n/2) - 1])
            {
                swap(heap[n], heap[(n/2) - 1]);
            }
            n = (n/2) - 1;
        }
        else
        {
            if (heap[n] > heap[n/2])
            {
                swap(heap[n], heap[n/2]);
            }
            n = n/2;
        }
    }
}

void maxHeapify (vector <int> &heap, int i)
{
    int n = heap.size();
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && heap[left] > heap[largest])
    {
        largest = left;
    }
    
    if (right < n && heap[right] > heap[largest])
    {
        largest = right;
    }
    
    if (largest != i)
    {
        swap(heap[i], heap[largest]);
        maxHeapify(heap, largest);
    }
}

void minHeapify (vector <int> &heap, int i)
{
    int n = heap.size();
    
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && heap[left] < heap[smallest])
    {
        smallest = left;
    }
    
    if (right < n && heap[right] < heap[smallest])
    {
        smallest = right;
    }
    
    if (smallest != i)
    {
        swap(heap[i], heap[smallest]);
        minHeapify(heap, smallest);
    }
}

int maxDeletion (vector<int> &heap)
{
    int n = heap.size();
    int i = 0;
    
    //swap the first and last element, then delete the last element out of the heap
    swap(heap[i], heap[n-1]);
    int temp = heap[n-1];
    heap.pop_back();
    for (int i = (n/2) - 1; i >= 0; i--)
    {
        maxHeapify(heap, i);
    }
    return temp;
}

int minDeletion (vector<int> &heap)
{
    int n = heap.size(); 
    int i = 0;
    
    swap(heap[i], heap[n-1]);
    int temp = heap[n-1];
    heap.pop_back();
    for (int i = (n/2) - 1; i >= 0; i--)
    {
        minHeapify(heap, i);
    }
    return temp;
}

void maxheapSort (int arr[], vector<int> heap, int size) {
    
    for (int i = 0; i < size; i++)
    {
        maxInsertion(arr[i], heap);
    }
    for (int i = size-1; i >= 0; i--)
    {
        int temp = maxDeletion(heap);
        arr[i] = temp;
    }
    
}

void minheapSort (int arr[], vector<int> heap, int size) {
    
    for (int i = 0; i < size; i++)
    {
        minInsertion(arr[i], heap);
    }
    for (int i = size-1; i >= 0; i--)
    {
        int temp = minDeletion(heap);
        arr[i] = temp;
    }
    
}

int main() 
{
    //int list[5] =  {10, 20, 15, 30, 40};
    //int list[4] =  {30, 20, 15, 10};
    int list[7] = {10, 20, 15, 50, 40, 25, 18};
    int n = sizeof(list)/sizeof(list[0]);
    vector<int> heap;
    vector<int> badHeap(list, list+n);
    
    maxheapSort(list, heap, n);
        
    cout << "After HeapSort: " ;
    //Print List  
    for (int i = 0; i < n; i++)
        cout << list[i] << " ";
        
    return 0;
}
