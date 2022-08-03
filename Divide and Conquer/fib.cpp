#include <iostream>

using namespace std;

int fib_recursive(int n) // O(n)
{
    if (n == 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }
    else
    {
        return fib_recursive(n-2) + fib_recursive(n-1);
    }
}

int fib_dp(int n) // O(n)
{
    int n_2 = 0, n_1 = 1, fib;
    for (int i = 2; i <= n; i++)
    {
        fib = n_2 + n_1;
        n_2 = n_1;
        n_1 = fib;
    }
    return fib;
    
}

int main()
{
    cout << fib_recursive(9) << endl;
    cout << fib_dp(9) << endl;
    return 0;
}