class Solution {
public:
    int reverseDegree(string s) {
        long long totalDegree = 0;
        int n = s.length();
        for (int i = 0; i < n; ++i) {
            // Position in reversed alphabet: 'a' = 26, 'b' = 25, ..., 'z' = 1
            long long revAlphabetPos = 26 - (s[i] - 'a');
            // 1-indexed position in the string
            long long stringPos = i + 1;
            
            totalDegree += revAlphabetPos * stringPos;
        }
        return totalDegree;
    }
};