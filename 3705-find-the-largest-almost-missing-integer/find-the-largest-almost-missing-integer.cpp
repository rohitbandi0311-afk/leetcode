class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> subarray_count;

        // Count how many subarrays of size k contain each element
        for (int i = 0; i <= n - k; ++i) {
            unordered_set<int> unique_elements(nums.begin() + i, nums.begin() + i + k);
            for (int num : unique_elements) {
                subarray_count[num]++;
            }
        }

        // Find the maximum number that appeared in exactly 1 subarray
        int ans = -1;
        for (auto& [num, count] : subarray_count) {
            if (count == 1) {
                ans = max(ans, num);
            }
        }

        return ans;
    }
};