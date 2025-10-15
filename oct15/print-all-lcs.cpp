#include <bits/stdc++.h>
using namespace std;

// Recursive function for LCS length (with memoization)
int LCSLength(string &s1, string &s2, int i, int j, vector<vector<int>> &dp) {
    if (i == 0 || j == 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];

    if (s1[i - 1] == s2[j - 1])
        return dp[i][j] = 1 + LCSLength(s1, s2, i - 1, j - 1, dp);
    else
        return dp[i][j] = max(LCSLength(s1, s2, i - 1, j, dp),
                              LCSLength(s1, s2, i, j - 1, dp));
}

// Function to find all LCS strings using the dp table
set<string> getAllLCS(string &s1, string &s2, int i, int j, vector<vector<int>> &dp) {
    set<string> result;

    // Base case
    if (i == 0 || j == 0) {
        result.insert("");
        return result;
    }

    // If characters match
    if (s1[i - 1] == s2[j - 1]) {
        set<string> temp = getAllLCS(s1, s2, i - 1, j - 1, dp);
        for (auto str : temp)
            result.insert(str + s1[i - 1]);
    } else {
        if (dp[i - 1][j] >= dp[i][j - 1])
            result.merge(getAllLCS(s1, s2, i - 1, j, dp));
        if (dp[i][j - 1] >= dp[i - 1][j])
            result.merge(getAllLCS(s1, s2, i, j - 1, dp));
    }

    return result;
}

int main() {
    string s1, s2;
    cout << "Enter first string: ";
    cin >> s1;
    cout << "Enter second string: ";
    cin >> s2;

    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

    int len = LCSLength(s1, s2, n, m, dp);
    cout << "\nLength of Longest Common Subsequence: " << len << endl;

    set<string> allLCS = getAllLCS(s1, s2, n, m, dp);

    cout << "All possible LCS strings of length " << len << ":\n";
    for (auto &str : allLCS)
        cout << str << endl;

    return 0;
}
