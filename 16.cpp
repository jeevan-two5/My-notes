#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
int ops_needed;

// Returns the height of the subtree at node u
int dfs(int u, int p, int H) {
    vector<int> ch_heights;
    for (int v : adj[u]) {
        if (v != p) {
            ch_heights.push_back(dfs(v, u, H));
        }
    }
    
    // Sort heights to greedily disconnect the largest subtrees first
    sort(ch_heights.begin(), ch_heights.end());
    
    // Allowed height for children of node u
    int max_allowed = (u == 1) ? (H - 1) : (H - 2);
    
    while (!ch_heights.empty() && ch_heights.back() + 1 > max_allowed) {
        ops_needed++;
        ch_heights.pop_back(); // Move this subtree to the root
    }
    
    if (ch_heights.empty()) return 0;
    return ch_heights.back() + 1;
}

int getMinimumHeight(int tree_nodes, vector<int> tree_from, vector<int> tree_to, int max_operations) {
    adj.assign(tree_nodes + 1, vector<int>());
    for (size_t i = 0; i < tree_from.size(); ++i) {
        adj[tree_from[i]].push_back(tree_to[i]);
        adj[tree_to[i]].push_back(tree_from[i]);
    }
    
    int low = 1, high = tree_nodes - 1, ans = tree_nodes - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        ops_needed = 0;
        
        dfs(1, 0, mid);
        
        if (ops_needed <= max_operations) {
            ans = mid;
            high = mid - 1; // Try to find a smaller height
        } else {
            low = mid + 1;  // Increase height limit
        }
    }
    
    return ans;
}
