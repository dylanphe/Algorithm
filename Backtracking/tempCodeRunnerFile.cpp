result[i] = 1;
    int sum = curr + s[i];
    int remain = total - s[i];
    if ((sum <= m))
    {
        if (sum == m)
        {
            for (int k = 0; k < n; k++)
            {
                cout << result[k] << " ";
            }
            cout << endl;
            return;
        }
        
        solvesofs(sum, remain, n, m, s, result, i+1);
    }

    result[i] = 0;
    sum -= s[i];
    int next = sum + remain;
    if (next > m)
    {
        solvesofs(sum, remain, n, m, s, result, i+1); 
    }
    else 
    {
        return;
    }