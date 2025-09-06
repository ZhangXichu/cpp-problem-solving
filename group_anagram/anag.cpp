// https://leetcode.com/problems/group-anagrams/description/

#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <array>
#include <algorithm>
#include <iostream>
#include <ranges>


std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs, std::unordered_map<std::string, std::vector<std::string>>& anagram_map) 
{

    for (const auto& str : strs) 
    {
        std::string str_sorted = str;
        std::sort(str_sorted.begin(), str_sorted.end());

        anagram_map[str_sorted].push_back(str);
    }


    std::vector<std::vector<std::string>> result;

    for (const auto& [key, vec] : anagram_map) {
        result.push_back(vec);
    }
        
    return result;

}


int main()
{
    std::unordered_map<std::string, std::vector<std::string>> anagram_map;

    // default test case 
    // "eat","tea","tan","ate","nat","bat"
    auto res = groupAnagrams(std::vector<std::string>{"","b",""}, anagram_map);

    std::cout << "Result: " << std::endl;
    for (const auto& vec : res) {
        for (const auto& str : vec) {
            std::cout << str.empty() << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}