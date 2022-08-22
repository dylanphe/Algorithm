/* Median of two sorted list */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
    {
        int s1 = nums1.size();
        int s2 = nums2.size();
        int total = s1 + s2;
        int mid = total/2;

        double Atmid, Atmid1;

        int cnt = 0;
        auto i = nums1.begin();
        auto j = nums2.begin();
        while (i != nums1.end() && j != nums2.end())
        {
            int curr;
            if (*i <= *j)
            {
                curr = *i;
                //cout << curr << " ";
                i++;
            }
            else 
            {
                curr = *j;
                //cout << curr << " ";
                j++;
            }

            if (cnt == mid-1)
            {
                Atmid1 = curr;
            }

            if (cnt == mid)
            {
                Atmid = curr;
                cnt++;
                break;
            }

            cnt++;
        }

         

        while (i != nums1.end() && cnt <= mid)
        {
            int curr;
            curr = *i;
            //cout << curr << " ";
            i++;

            if (cnt == mid-1)
            {
                Atmid1 = curr;
            }

            if (cnt == mid)
            {
                Atmid = curr;
            }

            cnt++;
        }

        while (j != nums2.end() && cnt <= mid)
        {
            int curr;
            curr = *j;
            //cout << curr << " ";
            j++;

            if (cnt == mid-1)
            {
                Atmid1 = curr;
            }

            if (cnt == mid)
            {
                Atmid = curr;
            }

            cnt++;
        }   
        
        if (total%2 == 0)
        {
            return (Atmid+Atmid1)/2;
        }

        return Atmid;
    }
};

int main()
{
    vector <int> num1 = {1, 3};
    vector <int> num2 = {2};
    Solution s;
    double res = s.findMedianSortedArrays(num1, num2);
    cout << res << " ";
    return 0;
}