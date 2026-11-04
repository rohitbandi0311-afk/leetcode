#include <vector>
#include <set>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        int numWindows = n - x + 1;
        vector<long long> cost(numWindows, 0);
        
        multiset<long long> leftMax;
        multiset<long long> rightMin;
        long long leftSum = 0, rightSum = 0;
        
        auto balance = [&]() {
            while (leftMax.size() > rightMin.size() + 1) {
                long long val = *leftMax.rbegin();
                leftMax.erase(leftMax.find(val));
                leftSum -= val;
                rightMin.insert(val);
                rightSum += val;
            }
            while (rightMin.size() > leftMax.size()) {
                long long val = *rightMin.begin();
                rightMin.erase(rightMin.find(val));
                rightSum -= val;
                leftMax.insert(val);
                leftSum += val;
            }
        };
        
        // Initialize the first window
        vector<long long> firstWindow(nums.begin(), nums.begin() + x);
        sort(firstWindow.begin(), firstWindow.end());
        
        int midCount = (x + 1) / 2;
        for (int i = 0; i < midCount; i++) {
            leftMax.insert(firstWindow[i]);
            leftSum += firstWindow[i];
        }
        for (int i = midCount; i < x; i++) {
            rightMin.insert(firstWindow[i]);
            rightSum += firstWindow[i];
        }
        
        long long median = *leftMax.rbegin();
        cost[0] = (leftMax.size() * median - leftSum) + (rightSum - rightMin.size() * median);
        
        // Slide the window
        for (int i = 1; i <= n - x; i++) {
            long long outgoing = nums[i - 1];
            long long incoming = nums[i + x - 1];
            
            // Remove outgoing element
            auto it = leftMax.find(outgoing);
            if (it != leftMax.end()) {
                leftMax.erase(it);
                leftSum -= outgoing;
            } else {
                it = rightMin.find(outgoing);
                if (it != rightMin.end()) {
                    rightMin.erase(it);
                    rightSum -= outgoing;
                }
            }
            
            // Add incoming element
            if (!leftMax.empty() && incoming <= *leftMax.rbegin()) {
                leftMax.insert(incoming);
                leftSum += incoming;
            } else {
                rightMin.insert(incoming);
                rightSum += incoming;
            }
            
            balance();
            
            median = *leftMax.rbegin();
            cost[i] = (leftMax.size() * median - leftSum) + (rightSum - rightMin.size() * median);
        }
        
        // Dynamic Programming to choose k non-overlapping windows
        vector<long long> prevDp(numWindows + 2, 1e16);
        for (int i = 0; i <= numWindows + 1; i++) {
            prevDp[i] = 0;
        }
        
        for (int j = 1; j <= k; j++) {
            vector<long long> currDp(numWindows + 1, 1e16);
            long long minSoFar = 1e16;
            
            for (int i = 1; i <= numWindows; i++) {
                int prevIdx = max(0, i - x);
                minSoFar = min(minSoFar, prevDp[prevIdx]);
                currDp[i] = min(currDp[i - 1], minSoFar + cost[i - 1]);
            }
            prevDp = currDp;
        }
        
        return prevDp[numWindows];
    }
};