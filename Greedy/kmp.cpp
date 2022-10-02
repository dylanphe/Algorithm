//Solve string matching problem
#include <iostream>

using namespace std;

void genLPS(int LPS[], int size, string pattern)
{
    int i = 0;
    int j = 1; 
    LPS[i] = 0;
    while(j < size)
    {
        if (pattern[i] == pattern[j])
        {
            LPS[j] = i+1;
            i++;
            j++;
        }
        else 
        {
            if (i != 0)
            {
                i = LPS[i-1];
            }
            else 
            {
                LPS[j] = 0;
                j++;
            }
        }
    }
}

void kmp (string s, string pattern)
{
    int psize = pattern.size();
    int ssize = s.size();

    int LPS[psize];
    genLPS(LPS, psize, pattern);
    for (int i = 0; i < psize; i++)
    {
        cout << LPS[i] << " "; 
    }
    cout << endl;

    int i = 0;
    int j = 0;
    int start;
    int end;
    while (i < ssize)
    {
        if (s[i] == pattern[j])
        {
            if (j == 0)
            {
                start = i;
            }
            if (j == (psize-1))
            {
                end = i;
                cout << s[start] << " " << s[end] << endl;
                cout << start << " " << end;
                return;
            }
            i++;
            j++;
        }
        else
        {
            if ( j == 0 )
            {
                i++;
            }
            else 
            {
                j = LPS[j-1];
                start = i - j; 
            }
        }

    }
}

int main() 
{
    string s = "aaaaaaab";
    string pattern = "aaab";
    /*string s = "abcdefgh";
    string pattern = "def";*/
    kmp(s, pattern);
    return 0;
}