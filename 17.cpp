#include <vector>
#include <numeric>
#include <bitset>
#include <algorithm>

using namespace std;

int getMinProcessingTime(vector<int> data, int processTimeA, int processTimeB) {
    int total_sum = 0;
    for (int x : data) total_sum += x;
    
    // Max possible sum is 100 * 1000 = 100000
    // Using bitset for ultra-fast subset sum DP
    bitset<100005> reachable;
    reachable[0] = 1;
    
    for (int x : data) {
        reachable |= (reachable << x);
    }
    
    int best_time = 2e9;
    
    for (int i = 0; i <= total_sum; ++i) {
        if (reachable[i]) {
            int timeA = i * processTimeA;
            int timeB = (total_sum - i) * processTimeB;
            best_time = min(best_time, max(timeA, timeB));
        }
    }
    
    return best_time;
}
