import java.util.HashSet;

class Solution {
    public int missingInteger(int[] nums) {
        // Step 1: Find the longest sequential prefix sum
        int sum = nums[0];
        for (int i = 1; i < nums.length; i++) {
            if (nums[i] == nums[i - 1] + 1) {
                sum += nums[i];
            } else {
                break;
            }
        }
        
        // Step 2: Store all elements in a HashSet for quick lookup
        HashSet<Integer> set = new HashSet<>();
        for (int num : nums) {
            set.add(num);
        }
        
        // Step 3: Find the smallest integer >= sum that is missing from the set
        int x = sum;
        while (set.contains(x)) {
            x++;
        }
        
        return x;
    }
}