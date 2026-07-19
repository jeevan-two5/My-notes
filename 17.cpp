int getMinProcessingTime(vector<int> data, int processTimeA, int processTimeB) {
    int total = 0;
    for (int x : data) total += x;
    
    bitset<100005> dp;
    dp[0] = 1;
    
    for (int x : data) {
        dp |= (dp << x);
    }
    
    int ans = 2e9;
    for (int i = 0; i <= total; ++i) {
        if (dp[i]) {
            int cost = max(i * processTimeA, (total - i) * processTimeB);
            if (cost < ans) ans = cost;
        }
    }
    return ans;
}
