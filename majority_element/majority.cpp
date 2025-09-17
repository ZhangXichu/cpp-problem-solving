// leetcode

#include <vector>
#include <iostream>

class Solution {
public:
    int majorityElement(std::vector<int>& nums) 
    {
        int m_element = nums[0];
        int count = 0;

        for (auto n : nums)
        {
            if (n == m_element)
            {
                count += 1;
            } else {
                count -= 1;

                if (count <= 0)
                {
                    m_element = n;
                    count = 1;
                }
            } 
        }   

        return m_element;
    }
};


int main()
{
    Solution sol;

    std::vector<int> nums = { 2,2,1,0,1,2,2 };
    std::cout << sol.majorityElement(nums) << std::endl;
    
    return 0;
}