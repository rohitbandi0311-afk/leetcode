import java.util.List;

class Solution {
    public int minimumSumSubarray(List<Integer> nums, int l, int r) {
        int minSum = Integer.MAX_VALUE;
        int n = nums.size();
        
        // Iterate over all possible starting positions of the subarray
        for (int i = 0; i < n; i++) {
            int currentSum = 0;
            // Extend the subarray length from l to r
            for (int j = i; j < n; j++) {
                currentSum += nums.get(j);
                int len = j - i + 1;
                
                // Check if length is within [l, r] and the sum is positive
                if (len >= l && len <= r) {
                    if (currentSum > 0) {
                        minSum = Math.min(minSum, currentSum);
                    }
                }
                
                // If length exceeds r, we can stop expanding this subarray
                if (len > r) {
                    break;
                }
            }
        }
        
        return minSum == Integer.MAX_VALUE ? -1 : minSum;
    }
}