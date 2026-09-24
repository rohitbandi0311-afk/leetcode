class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
            int temp = nums[i];
            int digitSum = 0;
            
            // Handle 0 explicitly if needed, though loop handles it since 0 % 10 = 0
            while (temp > 0) {
                digitSum += temp % 10;
                temp /= 10;
            }
            
            // If nums[i] is 0, its digit sum is 0
            if (nums[i] == 0 && i == 0) {
                return 0;
            }
            
            if (digitSum == i) {
                return i;
            }
        }
        return -1;
    }
};