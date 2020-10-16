#include <bits/stdc++.h>
#define qtr ios::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define int long long
#define MOD 1000000
using namespace std;

int inv(int a, int m){
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if(m == 1){
        return 0;
    }
    while(a > 1){
        q = a/m;
        t = m;
        m = a%m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if(x1 < 0){
        x1 += m0;
    }
    return x1;
}

int findMinX(vector<int> num, vector<int> rem, int k){
    int prod = 1;
    for(int i = 0; i < k; i++) prod *= num[i];
    int result = 0;
    for(int i = 0; i < k; i++){
        int pp = prod / num[i];
        result += rem[i] * inv(pp, num[i]) * pp;
    }
    return result % prod;
}

int32_t main() { //qtr
    int n = 3;
    vector<int> rem, factor;
    rem.resize(n);
    factor.resize(n);
    for(int i = 0; i < n; i++){
        cin >> factor[i];
    }
    for(int i = 0; i < n; i++){
        cin >> rem[i];
    }
    cout << findMinX(factor, rem, n) << endl;
}