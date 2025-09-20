// https://leetcode.com/problems/reverse-pairs/description/

#include <vector>
#include <iostream>
#include <algorithm>

class Solution {
public:
    int reversePairs(std::vector<int>& nums) {
        return reverse_pairs_re(nums, 0, nums.size()-1);
    }

private:
    int reverse_pairs_re(std::vector<int>& nums, int l, int r)
    {
        if (l == r ) {
            return 0;
        }

        int m = l + (r - l) / 2;

        // left part
        // right part
        // passes m
        std::vector<int> l_arr(nums.begin() + l, nums.begin() + m + 1);
        std::vector<int> r_arr(nums.begin() + m + 1, nums.begin() + r + 1);

        std::sort(l_arr.begin(), l_arr.end());
        std::sort(r_arr.begin(), r_arr.end());

        long long res = 0;

        for (int n: r_arr)
        {
            auto it = std::upper_bound(l_arr.begin(), l_arr.end(), 2LL*n);
            res += std::distance(it, l_arr.end());
        }

        return (int)(reverse_pairs_re(nums, l, m) + reverse_pairs_re(nums, m+1, r) + res);
    }

    int print_arr(std::vector<int>& v)
    {
        for (int x : v) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        return v.size();
    }
};

int main()
{
    Solution sol;

    std::vector<int> arr = { 2147483647,2147483647,2147483647,2147483647,2147483647,2147483647 };

    int res = sol.reversePairs(arr);

    std::cout << "Result: " << res << std::endl;

    return 0;
}

// TODO: use modified merge sort for better time complexity
