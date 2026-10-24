#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class Solution {
private:
    int calculateDayOfYear(std::string date) {
        static const std::vector<int> daysInMonths = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int month = std::stoi(date.substr(0, 2));
        int day = std::stoi(date.substr(3, 2));
        
        int dayOfYear = day;
        for (int i = 0; i < month - 1; ++i) {
            dayOfYear += daysInMonths[i];
        }
        return dayOfYear;
    }

public:
    int countDaysTogether(std::string arriveAlice, std::string leaveAlice, std::string arriveBob, std::string leaveBob) {
        int aliceArrival = calculateDayOfYear(arriveAlice);
        int aliceLeave = calculateDayOfYear(leaveAlice);
        int bobArrival = calculateDayOfYear(arriveBob);
        int bobLeave = calculateDayOfYear(leaveBob);
        
        int overlapStart = std::max(aliceArrival, bobArrival);
        int overlapEnd = std::min(aliceLeave, bobLeave);
        
        if (overlapStart <= overlapEnd) {
            return overlapEnd - overlapStart + 1;
        }
        return 0;
    }
};