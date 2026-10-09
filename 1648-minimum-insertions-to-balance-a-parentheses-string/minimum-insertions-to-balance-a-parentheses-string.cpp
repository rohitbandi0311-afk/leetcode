class Solution {
public:
    int minInsertions(string s) {
        int insertions = 0;
        int open = 0; // Tracks unmatched '('
        
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                open++;
            } else {
                // We need a pair of ')'
                // Check if the next character is also ')'
                if (i + 1 < s.length() && s[i + 1] == ')') {
                    i++; // Skip the next ')' as it forms a valid pair
                } else {
                    // We are missing one ')' to form a pair
                    insertions++;
                }
                
                // Match with an open '(' if available
                if (open > 0) {
                    open--;
                } else {
                    // No open '(' available, so we need to insert a '('
                    insertions++;
                }
            }
        }
        
        // Any remaining unmatched '(' each need two ')' characters
        insertions += open * 2;
        
        return insertions;
    }
};