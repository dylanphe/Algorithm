/* Two  x + y = sum m */
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

void twoSum(vector<int> nums, int target) {
    int i = 0;
    unordered_map<int, int> Ymap; 
    for (auto x : nums) {
        //If ymap doesn't contain the key difference
        if (Ymap.find(target - x) == Ymap.end()) {
            Ymap.insert(make_pair(x, i));
            i++;
        }
        //Key difference is found
        else {
            cout << Ymap.at(target - x) << " ";
            cout << i;
            return;
        }
    }
}

int main() {
    int target = 9;
    vector<int> nums = {2,7,11,15};
    twoSum(nums, target);
}