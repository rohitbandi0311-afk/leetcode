public class Solution {
    public boolean winnerSquareGame(int n) {
        boolean dp[] = new boolean[n + 1];
        dp[0] = false;
        if (n == 1) {
            return true;
        }
        dp[1] = true;
        dp[2] = false;

        for (int i = 3; i < n + 1; i++) {
            dp[i] = false;
            for (int j = 1; j * j <= i; j++) {
                if (dp[i - j * j] == false || i - j * j == 0) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
}