class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        vector<int> cnt(3, 0);
        for (int stone : stones) {
            cnt[stone % 3]++;
        }
        
        int c0 = cnt[0], c1 = cnt[1], c2 = cnt[2];
        
        if (c0 % 2 == 0) {
            return c1 >= 1 && c2 >= 1;
        } else {
            return abs(c1 - c2) > 2;
        }
    }
};
