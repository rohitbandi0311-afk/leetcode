class Solution {
    public int uniquePaths(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        long MOD = 1_000_000_007;

        // go[i][j][0]: target if we move down into (i, j)
        // go[i][j][1]: target if we move right into (i, j)
        // Stored as: [target_i, target_j] or [-1, -1]
        int[][][][] go = new int[m][n][2][2];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                go[i][j][0][0] = -1; go[i][j][0][1] = -1;
                go[i][j][1][0] = -1; go[i][j][1][1] = -1;
            }
        }

        // Compute jump targets in reverse order (bottom-up, right-to-left) to avoid re-tracing chains
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                for (int d = 0; d < 2; d++) {
                    int currI = i, currJ = j, currD = d;
                    
                    if (grid[currI][currJ] == 0) {
                        go[i][j][d][0] = currI;
                        go[i][j][d][1] = currJ;
                    } else {
                        // If it's a mirror (1), follow the reflection chain
                        int nextI = currI, nextJ = currJ, nextD = currD;
                        if (currD == 0) {
                            nextJ++;
                            nextD = 1;
                        } else {
                            nextI++;
                            nextD = 0;
                        }

                        if (nextI >= 0 && nextI < m && nextJ >= 0 && nextJ < n) {
                            go[i][j][d][0] = go[nextI][nextJ][nextD][0];
                            go[i][j][d][1] = go[nextI][nextJ][nextD][1];
                        } else {
                            go[i][j][d][0] = -1;
                            go[i][j][d][1] = -1;
                        }
                    }
                }
            }
        }

        long[][][] dp = new long[m][n][2];

        // Base cases from start (0, 0)
        if (n > 1) {
            int nextI = go[0][1][1][0];
            int nextJ = go[0][1][1][1];
            if (nextI >= 0 && nextI < m && nextJ >= 0 && nextJ < n) {
                dp[nextI][nextJ][1] = (dp[nextI][nextJ][1] + 1) % MOD;
            }
        }
        if (m > 1) {
            int nextI = go[1][0][0][0];
            int nextJ = go[1][0][0][1];
            if (nextI >= 0 && nextI < m && nextJ >= 0 && nextJ < n) {
                dp[nextI][nextJ][0] = (dp[nextI][nextJ][0] + 1) % MOD;
            }
        }

        // Standard DP propagation
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int d = 0; d < 2; d++) {
                    if (dp[i][j][d] == 0) continue;
                    if (i == m - 1 && j == n - 1) continue;

                    // Move Down to (i + 1, j)
                    if (i + 1 < m) {
                        int nextI = go[i + 1][j][0][0];
                        int nextJ = go[i + 1][j][0][1];
                        if (nextI >= 0 && nextI < m && nextJ >= 0 && nextJ < n) {
                            dp[nextI][nextJ][0] = (dp[nextI][nextJ][0] + dp[i][j][d]) % MOD;
                        }
                    }
                    // Move Right to (i, j + 1)
                    if (j + 1 < n) {
                        int nextI = go[i][j + 1][1][0];
                        int nextJ = go[i][j + 1][1][1];
                        if (nextI >= 0 && nextI < m && nextJ >= 0 && nextJ < n) {
                            dp[nextI][nextJ][1] = (dp[nextI][nextJ][1] + dp[i][j][d]) % MOD;
                        }
                    }
                }
            }
        }

        return (int) ((dp[m - 1][n - 1][0] + dp[m - 1][n - 1][1]) % MOD);
    }
}