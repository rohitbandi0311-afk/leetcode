class Solution {
    public int maximumLengthSubstring(String s) {
        // Array to store the frequency of each lowercase English letter
        int[] count = new int[26];
        int maxLength = 0;
        int left = 0;
        
        // Expand the window with the right pointer
        for (int right = 0; right < s.length(); right++) {
            char rightChar = s.charAt(right);
            count[rightChar - 'a']++;
            
            // If the character count exceeds 2, shrink the window from the left
            while (count[rightChar - 'a'] > 2) {
                char leftChar = s.charAt(left);
                count[leftChar - 'a']--;
                left++;
            }
            
            // Update the maximum length found so far
            maxLength = Math.max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
}