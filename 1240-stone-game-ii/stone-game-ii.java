class Solution {
    private int[] suffixSum;
    private int[][] memo;

    public int stoneGameII(int[] piles) {
        int n = piles.length;
        suffixSum = new int[n];
        memo = new int[n][n + 1];

        // Precompute suffix sums from the end of the array
        suffixSum[n - 1] = piles[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }

        return dfs(piles, 0, 1);
    }

    private int dfs(int[] piles, int i, int m) {
        // If we can take all remaining piles, take them all
        if (i + 2 * m >= piles.length) {
            return suffixSum[i];
        }

        // Return memoized result if available
        if (memo[i][m] != 0) {
            return memo[i][m];
        }

        int maxStones = 0;

        // Try all possible valid moves X (1 <= X <= 2m)
        for (int x = 1; x <= 2 * m; x++) {
            // Stones the current player gets = Total remaining stones - Opponent's optimal stones from next state
            int opponentStones = dfs(piles, i + x, Math.max(m, x));
            int currentStones = suffixSum[i] - opponentStones;
            maxStones = Math.max(maxStones, currentStones);
        }

        return memo[i][m] = maxStones;
    }
}