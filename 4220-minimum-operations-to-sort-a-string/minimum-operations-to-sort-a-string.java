class Solution {
    public int minOperations(String s) {
        int n = s.length();
        
        // Helper to check if string is sorted
        boolean sorted = true;
        for (int i = 0; i < n - 1; i++) {
            if (s.charAt(i) > s.charAt(i + 1)) {
                sorted = false;
                break;
            }
        }
        if (sorted) return 0;
        
        // If length is 2 and not sorted, it's impossible
        if (n == 2) return -1;
        
        char minChar = s.charAt(0);
        char maxChar = s.charAt(0);
        for (int i = 0; i < n; i++) {
            char c = s.charAt(i);
            if (c < minChar) minChar = c;
            if (c > maxChar) maxChar = c;
        }
        
        // Check condition for 1 operation
        if (s.charAt(0) == minChar || s.charAt(n - 1) == maxChar) {
            return 1;
        }
        
        // Check condition for 3 operations
        // If unique max is at start and unique min is at end
        boolean uniqueMaxAtStart = (s.charAt(0) == maxChar) && (s.lastIndexOf(maxChar) == 0);
        boolean uniqueMinAtEnd = (s.charAt(n - 1) == minChar) && (s.indexOf(minChar) == n - 1);
        if (uniqueMaxAtStart && uniqueMinAtEnd) {
            return 3;
        }
        
        // Otherwise, it can be sorted in 2 operations
        return 2;
    }
}