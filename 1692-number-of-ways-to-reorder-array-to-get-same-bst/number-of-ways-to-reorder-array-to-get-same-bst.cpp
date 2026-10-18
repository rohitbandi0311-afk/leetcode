
class Solution {
    using ll = long long;
    static const int MOD = 1'000'000'007;

    vector<vector<ll>> comb;

    ll solve(vector<int>& nums) {
        int n = nums.size();

        if (n <= 2)
            return 1;

        vector<int> left, right;

        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[0])
                left.push_back(nums[i]);
            else
                right.push_back(nums[i]);
        }

        ll waysLeft = solve(left);
        ll waysRight = solve(right);

        ll ways = comb[n - 1][left.size()];
        ways = ways * waysLeft % MOD;
        ways = ways * waysRight % MOD;

        return ways;
    }

public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();

        comb.assign(n, vector<ll>(n, 0));

        for (int i = 0; i < n; i++) {
            comb[i][0] = comb[i][i] = 1;

            for (int j = 1; j < i; j++) {
                comb[i][j] =
                    (comb[i - 1][j - 1] +
                     comb[i - 1][j]) % MOD;
            }
        }

        return (solve(nums) - 1 + MOD) % MOD;
    }
};
