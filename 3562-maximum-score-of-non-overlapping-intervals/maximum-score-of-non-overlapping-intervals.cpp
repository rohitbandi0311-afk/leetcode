class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        // Augment intervals with their original indices: [l, r, weight, original_index]
        vector<vector<long long>> a(n, vector<long long>(4));
        for (int i = 0; i < n; ++i) {
            a[i][0] = intervals[i][0];
            a[i][1] = intervals[i][1];
            a[i][2] = intervals[i][2];
            a[i][3] = i;
        }

        // Sort by right boundary, then by weight, then by original index
        sort(a.begin(), a.end(), [](const vector<long long>& x, const vector<long long>& y) {
            if (x[1] != y[1]) return x[1] < y[1];
            if (x[2] != y[2]) return x[2] < y[2];
            return x[3] < y[3];
        });

        // dp[i][j] stores {max_weight, vector_of_indices} for prefix i and j intervals
        // We track up to 4 intervals.
        vector<vector<pair<long long, vector<int>>>> dp(n, vector<pair<long long, vector<int>>>(5, { -1, {} }));

        auto compare = [](const pair<long long, vector<int>>& p1, const pair<long long, vector<int>>& p2) {
            if (p1.first != p2.first) return p1.first < p2.first;
            return p1.second > p2.second; // lexicographically smaller is preferred
        };

        for (int i = 0; i < n; ++i) {
            // Binary search to find the rightmost interval whose end < a[i][0]
            int low = 0, high = i - 1, idx = -1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (a[mid][1] < a[i][0]) {
                    idx = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            for (int j = 1; j <= 4; ++j) {
                // Option 1: Exclude current interval
                if (i > 0) {
                    dp[i][j] = dp[i - 1][j];
                }

                // Option 2: Include current interval
                pair<long long, vector<int>> candidate = { a[i][2], { (int)a[i][3] } };
                if (idx != -1 && dp[idx][j - 1].first != -1) {
                    candidate.first += dp[idx][j - 1].first;
                    candidate.second = dp[idx][j - 1].second;
                    candidate.second.push_back((int)a[i][3]);
                    sort(candidate.second.begin(), candidate.second.end());
                } else if (j > 1) {
                    // Cannot form j intervals if sub-problem isn't valid
                    continue;
                }

                // Update dp[i][j] if candidate is better or equal with smaller lexicographical order
                if (dp[i][j].first == -1 || candidate.first > dp[i][j].first || 
                   (candidate.first == dp[i][j].first && candidate.second < dp[i][j].second)) {
                    dp[i][j] = candidate;
                }
            }
        }

        pair<long long, vector<int>> best = { -1, {} };
        for (int j = 1; j <= 4; ++j) {
            if (dp[n - 1][j].first != -1) {
                if (best.first == -1 || dp[n - 1][j].first > best.first || 
                   (dp[n - 1][j].first == best.first && dp[n - 1][j].second < best.second)) {
                    best = dp[n - 1][j];
                }
            }
        }

        return best.second;
    }
};