#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.length();
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        // Check if palindrome permutation is possible
        int odd_count = 0;
        int odd_char = -1;
        for (int i = 0; i < 26; i++) {
            if (count[i] % 2 != 0) {
                odd_count++;
                odd_char = i;
            }
        }

        if (odd_count > 1) return "";

        int m = n / 2;
        vector<int> half_count(26, 0);
        for (int i = 0; i < 26; i++) {
            half_count[i] = count[i] / 2;
        }

        // Helper function to build the full palindrome from first half and middle character
        auto buildPalindrome = [&](const string& half, char mid) {
            string full = half;
            if (n % 2 != 0) {
                full += mid;
            }
            string rev = half;
            reverse(rev.begin(), rev.end());
            full += rev;
            return full;
        };

        // Try prefix length i matching target[0...i-1]
        for (int i = m; i >= 0; i--) {
            // Check if current target prefix target[0...i-1] can be built using half_count
            vector<int> cur_half = half_count;
            bool valid_prefix = true;
            for (int k = 0; k < i; k++) {
                int char_idx = target[k] - 'a';
                if (cur_half[char_idx] > 0) {
                    cur_half[char_idx]--;
                } else {
                    valid_prefix = false;
                    break;
                }
            }
            if (!valid_prefix) continue;

            string pref = target.substr(0, i);

            // Determine starting character at position i
            int start_char = (i == m) ? 0 : (target[i] - 'a' + 1);

            for (int c = start_char; c < 26; c++) {
                if (i < m && cur_half[c] == 0) continue;

                vector<int> temp_half = cur_half;
                string temp_pref = pref;

                if (i < m) {
                    temp_half[c]--;
                    temp_pref += (char)('a' + c);
                }

                // Fill the rest of the half greedily with smallest available characters
                for (int ch = 0; ch < 26; ch++) {
                    while (temp_half[ch] > 0) {
                        temp_pref += (char)('a' + ch);
                        temp_half[ch]--;
                    }
                }

                char mid = (odd_char != -1) ? (char)('a' + odd_char) : ' ';
                string candidate = buildPalindrome(temp_pref, mid);

                if (candidate > target) {
                    return candidate;
                }
            }
        }

        return "";
    }
};