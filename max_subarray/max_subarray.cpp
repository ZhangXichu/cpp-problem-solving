// https://leetcode.com/problems/maximum-subarray/description/

#include <vector>
#include <iostream>
#include <algorithm>

class Solution {
public:
    int maxSubArray(std::vector<int>& nums) 
    {
        int current_sum = nums[0];
        int max_sum = current_sum;

        for (int i = 1; i < nums.size(); i++)
        {
            current_sum = std::max(nums[i], current_sum + nums[i]);
            max_sum = std::max(current_sum, max_sum);
        }

        return max_sum;
    }
};


int main()
{
    Solution sol;

    std::vector v = {-2,1,-3,4,-1,2,1,-5,4};

    std::cout << sol.maxSubArray(v) << std::endl;

    return 0;
}