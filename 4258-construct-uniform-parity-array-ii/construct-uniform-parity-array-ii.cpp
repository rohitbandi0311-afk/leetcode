#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    bool uniformArray(std::vector<int>& nums1) {
        int min_odd = INT_MAX;
        
        for (int x : nums1) {
            if (x % 2 != 0) {
                min_odd = std::min(min_odd, x);
            }
        }
        
        // If there are no odd numbers, all elements are already even -> true
        if (min_odd == INT_MAX) {
            return true;
        }
        
        // Otherwise, try making all elements odd.
        // Every even number must be strictly greater than min_odd to be flipped to odd.
        for (int x : nums1) {
            if (x % 2 == 0 && x < min_odd) {
                return false;
            }
        }
        
        return true;
    }
};