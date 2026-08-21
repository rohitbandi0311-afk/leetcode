#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
private:
    long long gcd(long long a, long long b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    long long lcm(long long a, long long b) {
        if (a == 0 || b == 0) return 0;
        return (a / gcd(a, b)) * b;
    }

    // Counts number of amounts <= x that can be formed
    long long countAmounts(long long x, const vector<int>& coins) {
        int n = coins.size();
        long long count = 0;

        // Iterate through all 2^n - 1 non-empty subsets
        for (int mask = 1; mask < (1 << n); ++mask) {
            long long currentLcm = 1;
            int bitCount = 0;

            for (int i = 0; i < n; ++i) {
                if ((mask >> i) & 1) {
                    bitCount++;
                    currentLcm = lcm(currentLcm, coins[i]);
                    // Avoid unnecessary overflow if LCM exceeds x
                    if (currentLcm > x) break;
                }
            }

            if (currentLcm <= x) {
                if (bitCount % 2 == 1) {
                    count += x / currentLcm;
                } else {
                    count -= x / currentLcm;
                }
            }
        }
        return count;
    }

public:
    long long findKthSmallest(vector<int>& coins, int k) {
        long long low = 1;
        long long minCoin = *min_element(coins.begin(), coins.end());
        long long high = minCoin * k;
        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (countAmounts(mid, coins) >= k) {
                ans = mid;
                high = mid - 1; // Try to find a smaller valid amount
            } else {
                low = mid + 1;  // Not enough amounts, move right
            }
        }

        return ans;
    }
};