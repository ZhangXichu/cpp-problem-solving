// https://leetcode.com/problems/number-of-islands/description/

#include <vector>
#include <utility> 
#include <unordered_map>
#include <queue>
#include <iostream>

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const
    {
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ hash2;
    }
};

struct pair_equal
{
    template <class T1, class T2>
    bool operator() (const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) 
    {
        std::unordered_map<std::pair<int, int>, bool, pair_hash, pair_equal> visited;

        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[0].size(); ++j)
            {
                visited[{i, j}] = false;
            }
        }

        int num_islands = 0;

        num_islands += num_islands_aux(grid, visited, {0, 0});

        int num_unvisited = 0;
        for (const auto& [key, value] : visited) {
            if (!value) {
                ++num_unvisited;
            }
        }

        while (num_unvisited > 0) {

            num_unvisited = 0;

            for (auto &[idx, v] : visited)
            {
                if (!v)
                {
                    std::cout << "Starting new island at: (" << idx.first << ", " << idx.second << ")\n";
                    num_islands += num_islands_aux(grid, visited, idx);
                    num_unvisited--;
                }
            }
        }

        std::cout << "Visited matrix:\n";
        print_visited(visited);

        return num_islands;
    }


private:
    int num_islands_aux(std::vector<std::vector<char>>& grid, std::unordered_map<std::pair<int, int>, bool, pair_hash, pair_equal>& visited, std::pair<int, int> start) 
    {
        std::queue<std::pair<int, int>> q;

        q.emplace(start);
        if (grid[start.first][start.second] == '0')
        {
            return 0;
        }

        visited[start] = true;

        while (!q.empty())
        {
            std::cout << "Queue content: ";

            auto [i, j] = q.front();

            auto neighbors = adjacent(i, j, grid.size(), grid[0].size());

            for (auto [v1, v2] : neighbors)
            {
                std::cout << "(" << v1 << ", " << v2 << ") ";
            }   
            std::cout << "\n";

            for (const auto& neighbor : neighbors)
            {
                int x = neighbor.first;
                int y = neighbor.second;

                if ((grid[x][y] == '1') && (!visited[{x, y}]))
                {
                    visited[{x, y}] = true;
                    q.push({x, y});
                }
            }

            q.pop();
        }

        return 1;
    }


    std::vector<std::pair<int, int>> adjacent(int i, int j, int num_rows, int num_cols)
    {
        std::vector<std::pair<int, int>> result;
        
        if (i > 0)
        {
            result.emplace_back(i - 1, j);
        }

        if (i < num_rows - 1)
        {
            result.emplace_back(i + 1, j);
        }

        if (j > 0)
        {
            result.emplace_back(i, j - 1);
        }

        if (j < num_cols - 1)
        {
            result.emplace_back(i, j + 1);
        }

        return result;
    }

    void print_visited(const std::unordered_map<std::pair<int,int>, bool, pair_hash, pair_equal>& visited) {
        if (visited.empty()) return;

        // find bounds
        int max_row = 0, max_col = 0;
        for (auto& [key, _] : visited) {
            max_row = std::max(max_row, key.first);
            max_col = std::max(max_col, key.second);
        }

        // print matrix
        for (int r = 0; r <= max_row; ++r) {
            for (int c = 0; c <= max_col; ++c) {
                auto it = visited.find({r, c});
                if (it != visited.end() && it->second) {
                    std::cout << "1 ";
                } else {
                    std::cout << "0 ";
                }
            }
            std::cout << "\n";
        }
    }
};


int main()
{
    std::vector<std::vector<char>> grid = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };

    // std::vector<std::vector<char>> grid = {
    //     {'1','1','0','0','0'},
    //     {'1','1','0','0','0'},
    //     {'0','0','1','0','0'},
    //     {'0','0','0','1','1'}
    // };

    //     std::vector<std::vector<char>> grid = {
    //     {'1','0','0','0','0'},
    //     {'0','1','0','0','0'},
    //     {'0','0','1','0','0'},
    //     {'0','0','0','1','1'}
    // };

    Solution solution;
    int res = solution.numIslands(grid);

    std::cout << "Number of islands: " << res << "\n";

    return 0;
}