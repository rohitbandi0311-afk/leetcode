#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.length();
        // dp[i] will store the max palindromes in prefix s[0...i-1]
        vector<int> dp(n + 1, 0);

        // Helper lambda to check and expand palindromes around centers
        auto checkAndExpand = [&](int l, int r) {
            while (l >= 0 && r < n && s[l] == s[r]) {
                if (r - l + 1 >= k) {
                    dp[r + 1] = max(dp[r + 1], dp[l] + 1);
                }
                l--;
                r++;
            }
        };

        for (int i = 0; i < n; ++i) {
            dp[i + 1] = max(dp[i + 1], dp[i]);
            // Odd length palindromes centered at i
            checkAndExpand(i, i);
            // Even length palindromes centered between i and i+1
            if (i + 1 < n) {
                checkAndExpand(i, i + 1);
            }
        }

        return dp[n];
    }
};