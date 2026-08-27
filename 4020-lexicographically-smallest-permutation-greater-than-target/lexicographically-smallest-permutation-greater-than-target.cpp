#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.length();
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        // Try matching target prefix as far as possible
        vector<int> freq = count;
        int match_len = 0;
        for (int i = 0; i < n; i++) {
            int idx = target[i] - 'a';
            if (freq[idx] > 0) {
                freq[idx]--;
                match_len++;
            } else {
                break;
            }
        }

        // Search backward from match_len for the first position we can increment
        for (int i = match_len; i >= 0; i--) {
            // Reconstruct available frequency counts up to position i
            vector<int> cur_freq = count;
            for (int k = 0; k < i; k++) {
                cur_freq[target[k] - 'a']--;
            }

            // Look for the smallest available character strictly greater than target[i]
            if (i < n) {
                int target_char = target[i] - 'a';
                int next_char = -1;
                for (int c = target_char + 1; c < 26; c++) {
                    if (cur_freq[c] > 0) {
                        next_char = c;
                        break;
                    }
                }

                if (next_char != -1) {
                    string result = target.substr(0, i);
                    result += (char)('a' + next_char);
                    cur_freq[next_char]--;

                    // Append all remaining characters in ascending order
                    for (int c = 0; c < 26; c++) {
                        while (cur_freq[c] > 0) {
                            result += (char)('a' + c);
                            cur_freq[c]--;
                        }
                    }
                    return result;
                }
            }
        }

        return "";
    }
};