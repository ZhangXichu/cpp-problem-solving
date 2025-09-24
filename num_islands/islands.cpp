// https://leetcode.com/problems/number-of-islands/description/

#include <vector>
#include <utility> 
#include <unordered_map>
#include <queue>

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

        std::queue<std::pair<int, int>> q;

        q.emplace(0, 0);
        visited.emplace(std::make_pair(0, 0), true);

        while (!q.empty())
        {
            auto [i, j] = q.front();

            auto neighbors = adjacent(i, j, grid.size(), grid[0].size());

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
    }


private:
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
};


int main()
{
    // TODO: test the BFS
    // TODO: run BFS again for all the unvisited nodes that equals to '1'

    return 0;
}