/* #3 longest substrings without repeating characters */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:

    int lengthOfLongestSubstring(string s) {
        int size = s.length();
        int cnt = 0;
        int max = 0;
        vector<char> seq;
        for (int i = 0; i < size; i++) 
        {
            
            if (i==0)
            {
                seq.push_back(s[i]);
                max++;
                cnt++;
            }
            else 
            {
                //Check for duplicate
                bool dup = false;
                for (auto x = seq.begin(); x != seq.end(); x++)
                {
                    //if true, remove from the element from index 0 to that element
                    if ( *x == s[i] )
                    {
                        dup = true; 
                        seq.erase(seq.begin(), x + 1);
                        break;
                    }
                }

                if (dup)
                {
                    if (cnt >= max)
                    {
                        max = cnt;
                    }
                    seq.push_back(s[i]);
                    cnt = seq.size();
                }
                else
                {

                    cnt++;
                    seq.push_back(s[i]);
                }
            }
        }

        if (cnt > max)
        {
            return cnt;
        }
        
        return max;
        
    }
};

int main()
{
    string s1 = "pwwkew";
    Solution length;
    int max = length.lengthOfLongestSubstring(s1);
    cout << max;

    return 0;
}