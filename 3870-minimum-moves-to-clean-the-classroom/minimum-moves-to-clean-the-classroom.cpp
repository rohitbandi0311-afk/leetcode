#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

class Solution {
public:
    int minMoves(vector<string>& classroom, int maxEnergy) {
        int m = classroom.size();
        int n = classroom[0].size();
        
        int startX = -1, startY = -1;
        vector<pair<int, int>> litters;
        
        // Locate starting position 'S' and all litter cells 'L'
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (classroom[r][c] == 'S') {
                    startX = r;
                    startY = c;
                } else if (classroom[r][c] == 'L') {
                    litters.push_back({r, c});
                }
            }
        }
        
        int totalLitter = litters.size();
        int fullMask = (1 << totalLitter) - 1;
        
        // Map litter coordinates to their bit index
        auto getLitterIndex = [&](int r, int c) -> int {
            for (int i = 0; i < totalLitter; ++i) {
                if (litters[i].first == r && litters[i].second == c) {
                    return i;
                }
            }
            return -1;
        };
        
        // bestEnergy[r][c][mask] stores the maximum energy remaining at grid (r, c) with collected state 'mask'
        vector<vector<vector<int>>> bestEnergy(m, vector<vector<int>>(n, vector<int>(1 << totalLitter, -1)));
        
        // Queue state: {r, c, mask, currentEnergy}
        queue<tuple<int, int, int, int>> q;
        
        int initialMask = 0;
        int idx = getLitterIndex(startX, startY);
        if (idx != -1) {
            initialMask |= (1 << idx);
        }
        
        if (initialMask == fullMask) return 0;
        
        q.push({startX, startY, initialMask, maxEnergy});
        bestEnergy[startX][startY][initialMask] = maxEnergy;
        
        int moves = 0;
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                auto [r, c, mask, e] = q.front();
                q.pop();
                
                if (mask == fullMask) return moves;
                if (e == 0) continue; // Out of energy, cannot move further from this cell
                
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    
                    // Check boundaries and obstacles
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n || classroom[nr][nc] == 'X') {
                        continue;
                    }
                    
                    int nextEnergy = e - 1;
                    int nextMask = mask;
                    
                    // Reset energy if stepping onto 'R'
                    if (classroom[nr][nc] == 'R') {
                        nextEnergy = maxEnergy;
                    }
                    
                    // Collect litter if stepping onto 'L'
                    if (classroom[nr][nc] == 'L') {
                        int lIdx = getLitterIndex(nr, nc);
                        if (lIdx != -1) {
                            nextMask |= (1 << lIdx);
                        }
                    }
                    
                    // Prune states that don't improve the maximum remaining energy
                    if (nextEnergy > bestEnergy[nr][nc][nextMask]) {
                        bestEnergy[nr][nc][nextMask] = nextEnergy;
                        q.push({nr, nc, nextMask, nextEnergy});
                    }
                }
            }
            moves++;
        }
        
        return -1;
    }
};