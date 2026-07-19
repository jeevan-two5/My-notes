
/*
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
} */


#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Helper DFS to compute initial depths from the root (node 1)
void getDepths(int u, int p, int d, const vector<vector<int>>& adj, vector<int>& depth) {
    depth[u] = d;
    for (int v : adj[u]) {
        if (v != p) {
            getDepths(v, u, d + 1, adj, depth);
        }
    }
}

// Feasibility check function using bottom-up greedy strategy
bool check(int target_height, int max_ops, const vector<vector<int>>& adj, const vector<int>& depth) {
    int ops = 0;
    bool possible = true;

    auto dfs = [&](auto& self, int u, int p) -> int {
        if (!possible) return 0;
        
        int current_max = depth[u];
        for (int v : adj[u]) {
            if (v != p) {
                int child_max = self(self, v, u);
                if (child_max > target_height) {
                    // Forced to cut the edge to child v and move it to the root
                    ops++;
                    // The new max depth within this detached subtree when attached to root
                    int new_child_max = child_max - depth[v] + 1;
                    if (new_child_max > target_height) {
                        possible = false;
                    }
                } else {
                    current_max = max(current_max, child_max);
                }
            }
        }
        return current_max;
    };

    int root_max = dfs(dfs, 1, 0);
    if (root_max > target_height) possible = false;

    return possible && (ops <= max_ops);
}

int getMinimumHeight(int tree_nodes, vector<int> tree_from, vector<int> tree_to, int max_operations) {
    vector<vector<int>> adj(tree_nodes + 1);
    for (size_t i = 0; i < tree_from.size(); ++i) {
        adj[tree_from[i]].push_back(tree_to[i]);
        adj[tree_to[i]].push_back(tree_from[i]);
    }

    vector<int> depth(tree_nodes + 1, 0);
    getDepths(1, 0, 0, adj, depth);

    int low = 1, high = tree_nodes, ans = tree_nodes;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid, max_operations, adj, depth)) {
            ans = mid;
            high = mid - 1; // Try to find a smaller valid height
        } else {
            low = mid + 1;  // Increase target height boundary
        }
    }

    return ans;
}

