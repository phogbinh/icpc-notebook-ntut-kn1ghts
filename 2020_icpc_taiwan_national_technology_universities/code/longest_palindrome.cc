// This is a solution for UVa 11151 - Longest Palindrome. This DP solution takes
// time O(n^2).

#include <bits/stdc++.h>

using namespace std;

string word;

int memo[1010][1010];

int dp(int l, int r) {
    if (l == r) {
        return 1;
    }
    if (l + 1 == r) {
        if (word[l] == word[r]) {
            return 2;
        } else {
            return 1;
        }
    }
    if (memo[l][r] != -1) {
        return memo[l][r];
    }

    if (word[l] == word[r]) {
        return memo[l][r] = 2 + dp(l + 1, r - 1);
    } else {
        return memo[l][r] = max(dp(l, r - 1), dp(l + 1, r));
    }
}

int main() {
    int TC;
    getline(cin, word);
    TC = atoi(word.c_str());
    while (TC--) {
        getline(cin, word);
        if (word.length() == 0) {
            cout << "0" << endl;
            continue;
        }
        memset(memo, -1, sizeof(memo));
        int ans = dp(0, word.length() - 1);
        cout << ans << endl;
    }
    return 0;
}
