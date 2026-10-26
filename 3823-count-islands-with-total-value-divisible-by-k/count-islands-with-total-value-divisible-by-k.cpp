#include <vector>
#include <queue>

class Solution {
public:
    int countIslands(std::vector<std::vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        
        int count = 0;
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // If we find an unvisited land cell (> 0)
                if (grid[i][j] > 0 && !visited[i][j]) {
                    long long islandSum = 0;
                    std::queue<std::pair<int, int>> q;
                    
                    q.push({i, j});
                    visited[i][j] = true;

                    while (!q.empty()) {
                        auto [r, c] = q.front();
                        q.pop();
                        
                        islandSum += grid[r][c];

                        for (int d = 0; d < 4; ++d) {
                            int nr = r + dr[d];
                            int nc = c + dc[d];

                            if (nr >= 0 && nr < m && nc >= 0 && nc < n && 
                                grid[nr][nc] > 0 && !visited[nr][nc]) {
                                visited[nr][nc] = true;
                                q.push({nr, nc});
                            }
                        }
                    }

                    // Check if the total value of the island is divisible by k
                    if (islandSum % k == 0) {
                        count++;
                    }
                }
            }
        }

        return count;
    }
};