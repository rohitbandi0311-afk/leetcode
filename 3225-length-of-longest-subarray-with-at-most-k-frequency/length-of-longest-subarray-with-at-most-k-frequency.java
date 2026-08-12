import java.util.HashMap;
import java.util.Map;

class Solution {
    public int maxSubarrayLength(int[] nums, int k) {
        Map<Integer, Integer> freqMap = new HashMap<>();
        int left = 0;
        int maxLength = 0;

        for (int right = 0; right < nums.length; right++) {
            // Add current element to frequency map
            freqMap.put(nums[right], freqMap.getOrDefault(nums[right], 0) + 1);

            // If any element exceeds frequency k, shrink window from left
            while (freqMap.get(nums[right]) > k) {
                freqMap.put(nums[left], freqMap.get(nums[left]) - 1);
                left++;
            }

            // Update the max valid subarray length
            maxLength = Math.max(maxLength, right - left + 1);
        }

        return maxLength;
    }
}