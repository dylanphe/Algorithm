#include <iostream>

using namespace std;

int linear_search (int arr[], int size, int key) // O(n)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == key)
        {
            cout << "Found at index ";
            return i;
        }
    }
    cout << key << " is not found." << endl;
    return -1;
}

int main()
{
    int List[10] = {2, 5, 10, 34, 60, 30, 42, 59, 4, 20};
    int n = sizeof(List)/sizeof(List[0]);
    cout << "List: ";
    for (int i = 0; i < n; i++)
    {
        cout << List[i] << " ";
    }
    int key;
    cout << "\nEnter a key to search: ";
    cin >> key;
    cout << "Result: " << linear_search(List, n, key);
    return 0;
}