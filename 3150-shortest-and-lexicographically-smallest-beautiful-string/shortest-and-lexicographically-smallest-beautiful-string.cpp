class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.length();
        string ans = "";
        int min_len = n + 1;
        
        int left = 0;
        int count = 0;
        
        for (int right = 0; right < n; ++right) {
            if (s[right] == '1') {
                count++;
            }
            
            // Shrink the window when we have exactly k ones
            while (count == k) {
                // Remove leading '0's to make the substring as short as possible
                while (left < right && s[left] == '0') {
                    left++;
                }
                
                int cur_len = right - left + 1;
                string cur_str = s.substr(left, cur_len);
                
                if (cur_len < min_len) {
                    min_len = cur_len;
                    ans = cur_str;
                } else if (cur_len == min_len) {
                    if (cur_str < ans) {
                        ans = cur_str;
                    }
                }
                
                // Shrink the window by moving left past the current '1'
                if (s[left] == '1') {
                    count--;
                }
                left++;
            }
        }
        
        return ans;
    }
};