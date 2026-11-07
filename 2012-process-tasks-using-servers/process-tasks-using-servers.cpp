#include <vector>
#include <queue>
#include <tuple>

using namespace std;

class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();
        
        // Min-heap for free servers: {weight, index}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> free_servers;
        for (int i = 0; i < n; ++i) {
            free_servers.push({servers[i], i});
        }
        
        // Min-heap for busy servers: {available_time, weight, index}
        priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<tuple<long long, int, int>>> busy_servers;
        
        vector<int> ans(m);
        long long curr_time = 0;
        
        for (int j = 0; j < m; ++j) {
            curr_time = max(curr_time, (long long)j);
            
            // If no servers are free, jump time to when the next server becomes available
            if (free_servers.empty() && !busy_servers.empty()) {
                curr_time = max(curr_time, get<0>(busy_servers.top()));
            }
            
            // Release all servers that have finished their tasks by curr_time
            while (!busy_servers.empty() && get<0>(busy_servers.top()) <= curr_time) {
                auto [avail_time, weight, index] = busy_servers.top();
                busy_servers.pop();
                free_servers.push({weight, index});
            }
            
            // Assign the current task to the top free server
            auto [weight, index] = free_servers.top();
            free_servers.pop();
            
            ans[j] = index;
            busy_servers.push({curr_time + tasks[j], weight, index});
        }
        
        return ans;
    }
};