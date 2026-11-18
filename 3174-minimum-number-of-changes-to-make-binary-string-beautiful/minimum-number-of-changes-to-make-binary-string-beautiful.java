class Solution {
    public int minChanges(String s) {
        int changes = 0;
        // Iterate through the string in steps of 2
        for (int i = 0; i < s.length(); i += 2) {
            // If adjacent characters don't match, we need 1 change
            if (s.charAt(i) != s.charAt(i + 1)) {
                changes++;
            }
        }
        return changes;
    }
}