
import java.util.*;

class Solution {
    public long countNonDecreasingSubarrays(int[] nums, int k) {

        int n = nums.length;

        Deque<Integer> dq = new ArrayDeque<>();

        long cost = 0;
        long ans = 0;

        int j = n - 1;

        // Traverse from right to left
        for (int i = n - 1; i >= 0; i--) {

            int num = nums[i];

            // Merge smaller groups into the current group
            while (!dq.isEmpty() &&
                   nums[dq.peekLast()] < num) {

                int l = dq.pollLast();

                int r = dq.isEmpty() ? j + 1 : dq.peekLast();

                // Increase all elements in this group
                cost += (long) (r - l) * (num - nums[l]);
            }

            // Add current index
            dq.offerLast(i);

            // Shrink window while cost exceeds k
            while (cost > k) {

                cost -= nums[dq.peekFirst()] - nums[j];

                if (dq.peekFirst() == j) {
                    dq.pollFirst();
                }

                j--;
            }

            // Count all valid subarrays ending at or before j
            ans += j - i + 1;
        }

        return ans;
    }
}
