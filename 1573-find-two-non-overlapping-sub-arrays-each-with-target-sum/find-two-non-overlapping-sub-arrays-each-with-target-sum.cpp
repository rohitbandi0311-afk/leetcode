#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

class Solution {
public:
    int minSumOfLengths(std::vector<int>& arr, int target) {
        int n = arr.size();
        // min_len[i] stores the minimum length of a subarray with sum = target 
        // ending at or before index i.
        std::vector<int> min_len(n, INT_MAX);
        
        std::unordered_map<int, int> prefix_sum_map;
        prefix_sum_map[0] = -1; // To handle subarrays starting from index 0
        
        int current_sum = 0;
        int min_ans = INT_MAX;
        int best_so_far = INT_MAX;
        
        for (int r = 0; r < n; ++r) {
            current_sum += arr[r];
            
            int required = current_sum - target;
            if (prefix_sum_map.find(required) != prefix_sum_map.end()) {
                int l = prefix_sum_map[required] + 1;
                int curr_length = r - l + 1;
                
                // If there is a valid non-overlapping subarray to the left
                if (l > 0 && min_len[l - 1] != INT_MAX) {
                    min_ans = std::min(min_ans, curr_length + min_len[l - 1]);
                }
                
                // Update best_so_far ending at or before r
                best_so_far = std::min(best_so_far, curr_length);
            }
            
            min_len[r] = best_so_far;
            prefix_sum_map[current_sum] = r;
        }
        
        return min_ans == INT_MAX ? -1 : min_ans;
    }
};