class NeighborSum {
private:
    int n;
    vector<vector<int>> g;
    // Store coordinates (r, c) for each value in the grid
    vector<pair<int, int>> pos;

public:
    NeighborSum(vector<vector<int>>& grid) {
        g = grid;
        n = grid.size();
        pos.resize(n * n);
        
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                pos[grid[r][c]] = {r, c};
            }
        }
    }
    
    int adjacentSum(int value) {
        auto [r, c] = pos[value];
        int sum = 0;
        
        // Up, Down, Left, Right directions
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                sum += g[nr][nc];
            }
        }
        
        return sum;
    }
    
    int diagonalSum(int value) {
        auto [r, c] = pos[value];
        int sum = 0;
        
        // Top-Left, Top-Right, Bottom-Left, Bottom-Right directions
        int dr[] = {-1, -1, 1, 1};
        int dc[] = {-1, 1, -1, 1};
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                sum += g[nr][nc];
            }
        }
        
        return sum;
    }
};

/**
 * Your NeighborSum object will be instantiated and called as such:
 * NeighborSum* obj = new NeighborSum(grid);
 * int param_1 = obj->adjacentSum(value);
 * int param_2 = obj->diagonalSum(value);
 */