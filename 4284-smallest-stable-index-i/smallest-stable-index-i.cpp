class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> suffixMin(n);
        
        suffixMin[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffixMin[i] = min(suffixMin[i + 1], nums[i]);
        }
        
        int currentMax = INT_MIN;
        for (int i = 0; i < n; ++i) {
            currentMax = max(currentMax, nums[i]);
            if (currentMax - suffixMin[i] <= k) {
                return i;
            }
        }
        
        return -1;
    }
};