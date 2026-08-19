#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> rowMasks;
        
        // Track reserved seats for columns 2 through 9
        for (const auto& seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];
            if (col >= 2 && col <= 9) {
                rowMasks[row] |= (1 << (col - 2));
            }
        }
        
        // Rows without reserved seats can fit 2 groups of 4
        int totalGroups = (n - rowMasks.size()) * 2;
        
        // Bitmasks for the 4-seat blocks
        int leftMask   = 0b00001111; // Seats 2, 3, 4, 5
        int middleMask = 0b00111100; // Seats 4, 5, 6, 7
        int rightMask  = 0b11110000; // Seats 6, 7, 8, 9
        
        for (const auto& [row, mask] : rowMasks) {
            bool leftPossible   = (mask & leftMask) == 0;
            bool middlePossible = (mask & middleMask) == 0;
            bool rightPossible  = (mask & rightMask) == 0;
            
            if (leftPossible && rightPossible) {
                totalGroups += 2;
            } else if (leftPossible || rightPossible || middlePossible) {
                totalGroups += 1;
            }
        }
        
        return totalGroups;
    }
};