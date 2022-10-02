#include <iostream>
#include <vector>
#include <string>

//head tail compare

using namespace std;

class Solution {
public:
    string longestPalindrome(string s)
    {
        int size = s.size();
        int cnt = 0;
        int max = 0;

        string tempt;
        string palindrome;
        vector <char> curr;

        for (int i = 0; i < size; i++)
        {
            if (i == 0)
            {
                curr.push_back(s[i]);
                cnt++;
                palindrome += s[i];
            }
            else
            {
                bool dup = false;
                bool doubledup = false;
                //Check for dup or double dup
                for (auto x = curr.begin(); x != curr.end(); x++)
                {
                    //Double dup
                    if (x != curr.end()-1)
                    {
                        if ( i != size - 1 && x != curr.begin() && *(x+1) == s[i-1])
                        {
                            if (*x == s[i] && *(x-1) == s[i+1])
                            {
                                doubledup = true;
                                curr.push_back(s[i]);
                                cnt = curr.size();
                                break;
                            }
                        }
                    }

                    //Dup
                    if (x != curr.end()-1)
                    {
                        if (*x == s[i] && *(x+1) == s[i-1])
                        {
                            dup = true;
                            for (auto y = curr.begin(); y != x; y++)
                            {
                                tempt += *y;
                            }
                            curr.erase(curr.begin(), x);
                            curr.push_back(s[i]);
                            cnt = curr.size();
                            
                            string currtempt;
                            for (auto c : curr)
                            {
                                currtempt += c; 
                            }

                            int mid = cnt/2;
                            int tail = cnt - 1;
                            int head = 0;
                            bool pld = true;

                            while (tail != mid && head != mid)
                            {
                                if (currtempt[head] != currtempt[tail])
                                {
                                    if (s[i] != s[i-1])
                                    {
                                        pld = false;
                                    }
                                }
                                head++;
                                tail--;
                            }

                            if (pld)
                            {
                                if (cnt > max)
                                {
                                    max = cnt;
                                    if (!palindrome.empty())
                                    {
                                        palindrome = "";
                                    }
                                    int m = 1;
                                    for (int n = (tempt.size() - 1); n >= 0; n--)
                                    {
                                        
                                        if (tempt[n] == s[i+m])
                                        {
                                            palindrome = tempt[n] + palindrome;
                                            cnt++;
                                            m++;
                                        }
                                    }
                                    for (auto c : curr)
                                    {
                                        palindrome += c;
                                    }

                                    m=1;
                                    for (int n = (tempt.size() - 1); n >= 0; n--)
                                    {
                                        
                                        if (tempt[n] == s[i+m])
                                        {
                                            palindrome += tempt[n];
                                            cnt++;
                                            m++;
                                        }
                                    }
                                }
                            }
                        

                            if (s[i] != s[i-1])
                            {
                                tempt += *(curr.begin());
                                curr.erase(curr.begin());
                                cnt = curr.size();
                            }

                            break;
                        }
                    }

                    if (x == curr.end()-1)
                    {
                        if (*x == s[i])
                        {
                            dup = true;
                            for (auto y = curr.begin(); y != x; y++)
                            {
                                tempt += *y;
                            }
                            curr.erase(curr.begin(), x);

                            curr.push_back(s[i]);
                            cnt = curr.size();
                            if (cnt > max)
                            {
                                max = cnt;
                                if (!palindrome.empty())
                                {
                                    palindrome = "";
                                }
                                for (auto c : curr)
                                {
                                    palindrome += c;
                                } 
                            }

                            if (s[i] != s[i-1])
                            {
                                curr.erase(curr.begin());
                                cnt = curr.size();
                            }
                            
                            break;
                        }
                    }
                }

                if (!dup && !doubledup)
                {
                    curr.push_back(s[i]);
                    cnt++;
                }
            }
        }
        return palindrome;
    }

};

int main()
{
    string s = "bananas";
    //string s = "xaabacxcabaaxcabaax";
    Solution x;
    string palindrome = x.longestPalindrome(s);
    cout << palindrome;
    return 0;
}