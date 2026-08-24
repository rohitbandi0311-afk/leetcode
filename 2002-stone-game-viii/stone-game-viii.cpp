#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    int stoneGameVIII(std::vector<int>& stones) {
        int n = stones.size();
        std::vector<long long> pref(n);
        pref[0] = stones[0];
        for (int i = 1; i < n; ++i) {
            pref[i] = pref[i - 1] + stones[i];
        }

        // Base case: picking the entire array (index n - 1)
        long long max_diff = pref[n - 1];

        // Traverse backwards from n - 2 down to 1
        for (int i = n - 2; i >= 1; --i) {
            max_diff = std::max(max_diff, pref[i] - max_diff);
        }

        return max_diff;
    }
};