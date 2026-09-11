class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        vector<int> count(10, 0);
        for (int d : digits) {
            count[d]++;
        }
        
        int uniqueEvenCount = 0;
        
        // Iterate through all possible 3-digit even numbers
        for (int num = 100; num <= 999; num += 2) {
            int h = num / 100;         // Hundreds place
            int t = (num / 10) % 10;   // Tens place
            int u = num % 10;          // Units place
            
            // Count frequency of digits needed for this number
            vector<int> need(10, 0);
            need[h]++;
            need[t]++;
            need[u]++;
            
            // Check if we have enough of each digit in our input
            bool possible = true;
            for (int i = 0; i < 10; i++) {
                if (need[i] > count[i]) {
                    possible = false;
                    break;
                }
            }
            
            if (possible) {
                uniqueEvenCount++;
            }
        }
        
        return uniqueEvenCount;
    }
};