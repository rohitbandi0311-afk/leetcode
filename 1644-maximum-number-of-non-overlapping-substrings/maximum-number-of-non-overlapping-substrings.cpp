class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.length();
        vector<int> first(26, -1), last(26, -1);

        // Step 1: Record first and last occurrence of each character
        for (int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            if (first[c] == -1) {
                first[c] = i;
            }
            last[c] = i;
        }

        vector<pair<int, int>> intervals;

        // Step 2: Find valid substrings for each character
        for (int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            if (i != first[c]) continue; // Only process at the first occurrence

            int right = last[c];
            bool valid = true;

            for (int j = i; j <= right; ++j) {
                int currChar = s[j] - 'a';
                // If a character appears before our current start, this substring is invalid
                if (first[currChar] < i) {
                    valid = false;
                    break;
                }
                // Expand the right boundary if necessary
                right = max(right, last[currChar]);
            }

            if (valid) {
                intervals.push_back({right, i}); // store as {end, start} for easy sorting
            }
        }

        // Step 3: Sort by end index to apply greedy interval selection
        sort(intervals.begin(), intervals.end());

        vector<string> result;
        int prevEnd = -1;

        for (auto& interval : intervals) {
            int end = interval.first;
            int start = interval.second;

            // If the current interval doesn't overlap with the last chosen one
            if (start > prevEnd) {
                result.push_back(s.substr(start, end - start + 1));
                prevEnd = end;
            }
        }

        return result;
    }
};