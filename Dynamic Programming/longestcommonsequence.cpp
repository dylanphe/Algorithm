/*Algorithm
-Create a table of size [n+1][m+1], where n is the size of s1 and m is the size of s2
-Fill up the table by comparing each letter in s1 with ever letter in s2 then continue
    -If the letters are the same, add 1 to the current val
    -If the letters are different, fill it with the max length of either the new seq made by the current letter or the old seq made by the new letter
-To find the seq, starting from [n][m]
    -Check to see if the letter are the same, if so, add them to the seq
    -If not, 
        -If L[i-1][j] >= L[i][j-1], go up one row
        -Else, go back one column 
*/
#include <iostream>

using namespace std;

void lcs(string s1, string s2)
{
    int n = s1.size();
    int m = s2.size();

    int L[n+1][m+1] = {0};

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            //The first extra row and column are 0
            if (i == 0 || j == 0)
            {
                L[i][j] = 0;
            }
            //If they match, we add 1 to L[i][j]
            else if (i > 0 && j > 0 && s1[i-1] == s2[j])
            {
                L[i][j] = 1 + L[i-1][j-1];
            }
            //If it doesn't, we take the max of the last letter result (i-1) or of the current letter result (j-1) 
            else 
            {
                if (L[i-1][j] > L[i][j-1])
                {
                    L[i][j] = L[i-1][j];
                }
                else 
                {
                    L[i][j] = L[i][j-1];
                }
            }
        }
    }

    int index = L[n][m];
    char LCS[index+1];
    LCS[index] = '\0';

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            cout << L[i][j] << " ";
        }
        cout << endl;
    }

    int i = n, j = m;
    while (i > 0 && j > 0)
    {
        cout << s1[i-1] << " ";
        cout << s2[j-1] << " ";
        cout << endl;
        if (s1[i-1] == s2[j-1])
        {
            LCS[index - 1] = s1[i - 1];
            i--;
            j--;
            index--;
        }
        //if the letter in the last row made the longest seq, go to last row
        else if (L[i-1][j] >= L[i][j-1])
        {
            i--;
        }
        else 
        {
            j--;
        }
    }

    cout << "\nLength of LCS = " << L[n][m] << endl;
    cout << "LCS = " << LCS;
}

int main()
{
    string s1 = "abcdefghij";
    string s2 = " ecdgi";
    lcs(s1, s2);
    return 0;
}