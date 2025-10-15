#include <bits/stdc++.h>
using namespace std;

int LCS(string &s1, string &s2, int i, int j, vector<vector<int>> &dp) {
    // Base Case
    if (i == 0 || j == 0)
        return 0;

    // If already computed
    if (dp[i][j] != -1)
        return dp[i][j];

    // If last characters match
    if (s1[i - 1] == s2[j - 1])
        return dp[i][j] = 1 + LCS(s1, s2, i - 1, j - 1, dp);
    
    // If not match, take max of excluding one character
    return dp[i][j] = max(LCS(s1, s2, i - 1, j, dp), LCS(s1, s2, i, j - 1, dp));
}

int main() {
    string s1, s2;
    cout << "Enter first string: ";
    cin >> s1;
    cout << "Enter second string: ";
    cin >> s2;

    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

    cout << "Length of Longest Common Subsequence: " << LCS(s1, s2, n, m, dp) << endl;

    return 0;
}
// O(m*n)
