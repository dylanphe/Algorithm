#include <iostream>
#include <vector>

using namespace std;


void solvesofs(int curr, int total, int n, int m, int s[], int result[], int i)
{
    result[i] = 1;
    int sum = curr + s[i];
    int remain = total - s[i];
    if ((sum <= m))
    {
        if (sum == m)
        {
            for (int k = 0; k < n; k++)
            {
                if (result[k] == 1)
                {
                    cout << s[k] << " ";
                }
            }
            cout << endl;
            result[i] = 0;
            return;
        }
        
        solvesofs(sum, remain, n, m, s, result, i+1);
    }

    result[i] = 0;
    sum -= s[i];
    int next = sum + remain;
    if (next >= m)
    {
        solvesofs(sum, remain, n, m, s, result, i+1); 
    }
    else 
    {
        return;
    }
}

void sofs(int n, int m, int s[])
{
    int curr = 0;
    int total = 0;
    int result[n] = {0};

    for (int i = 0; i < n; i++)
    {
        total += s[i];
    }

    solvesofs(curr, total, n, m, s, result, 0);
}

int main()
{
    int n = 6;
    int m = 30;
    int s[n] = {5,10,12,13,15,18};
    sofs(n, m, s);
    return 0;
}