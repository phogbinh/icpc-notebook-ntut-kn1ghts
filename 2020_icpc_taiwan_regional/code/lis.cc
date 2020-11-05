// UVa 481 - What Goes Up solved as Longest Increasing Subsequence (LIS) using
// greedy + divide & conquer algorithm in O(n log n).
#include <bits/stdc++.h>

using namespace std;

#define LOCAL

typedef vector<int> vi;

vi p;
vi a;

void print_lis(int i)
{
    if (p[i] == -1)
    {
        printf("%d\n", a[i]);
        return;
    }
    print_lis( p[i] );
    printf("%d\n", a[i]);
}

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int val;
    while (scanf("%d", &val) != EOF) a.push_back(val);
    int N = (int)a.size();
    int lis_length = 0;
    int lis_end = 0;
    vi L(N, 0);
    vi L_id(N, 0);
    p.assign(N, -1);
    for (int i = 0; i < N; ++i)
    {
        int pos = lower_bound( L.begin(), L.begin() + lis_length, a[i] ) - L.begin();
        L[pos] = a[i];                         // greedy - I am <= you (a[i] <= L[pos]). I am better.
        L_id[pos] = i;                         // which causes 'L' entry order to differ from 'a'.
        p[i] = (pos > 0) ? L_id[pos - 1] : -1; // but we have [p]arent array on our back.
        if (pos == lis_length)                 // not found a guy to replace. we have a longer LIS!
        {
            lis_length = pos + 1;
            lis_end = i;
        }
        if (pos == lis_length - 1) lis_end = i; // take the LIS that occurs last.
//        printf("LIS ending at a[%d]=%d is of length %d: ", i, a[i], pos+1);
//        print_lis(i);
//        printf("\n");
    }
    printf("%d\n-\n", lis_length);
    print_lis(lis_end);
    return 0;
}
