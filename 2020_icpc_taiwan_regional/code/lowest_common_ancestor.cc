// UVa 12238 - Ants Colony solved with Lowest Common Ancestor (LCA) using Range
// Minimum Query (RMQ) reduction and Spare Table data structure.
#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define root 0
#define MAX_N 100050
#define MAX_AN (2*MAX_N)
#define LOG_TWO_AN 20

typedef long long int ll;
typedef pair<int, ll> il;
typedef vector<il> vil;

int N;
vector< vil > CH; // [CH]ildren
ll dist[MAX_N];
int a[MAX_AN]; // RMQ [a]rray
int a_N;
int a2t[MAX_AN]; // RMQ [a]rray index -> [t]ree index
int t2a[MAX_N]; // [t]ree index -> RMQ [a]rray index

int _A[MAX_AN]; // RMQ member array (must be global otherwise MLE)
int SpT[MAX_AN][LOG_TWO_AN]; // [Sp]arse [T]able
class RMQ    // [R]ange [M]inimum [Q]uery
{
public:
    RMQ(int n, int A[])    // DP pre-process
    {
        for (int i = 0; i < n; ++i)
        {
            _A[i] = A[i];
            SpT[i][0] = i; // RMQ of sub-array starting at index [i] with length 2^[0] = 1
        }
        // the two nested loops below have overall time complexity O(n log n)
        for (int j = 1; (1<<j) <= n; ++j)    // for each [j] such that 2^j <= n. O(log n)
            for (int i = 0; i + (1<<j) - 1 < n; ++i)    // for each valid [i]. O(n)
                if (_A[ SpT[i][j-1] ] < _A[ SpT[ i + ( 1<<(j-1) ) ][j-1] ])    // RMQ
                    SpT[i][j] = SpT[i][j-1];    // start at index i         of length 2^(j-1)
                else                            // start at index i+2^(j-1) of length 2^(j-1)
                    SpT[i][j] = SpT[ i + ( 1<<(j-1) ) ][j-1];
    }

    int query(int i, int j)    // O(1)
    {
        int k = (int)floor( log( (double)j-i+1 ) / log(2.0) );    // find [k] such that 2^k <= (j-i+1)
        if (_A[ SpT[i][k] ] <= _A[ SpT[j - (1<<k) + 1][k] ]) return SpT[i][k];
        else return SpT[j - (1<<k) + 1][k];
    }
};

void build_dist(int u)
{
    for (int i = 0; i < (int)CH[u].size(); ++i)
    {
        int v = CH[u][i].first;
        dist[v] = dist[u] + CH[u][i].second;
        build_dist(v);
    }
}

void build_rmq(int u, int depth)
{
    a[a_N] = depth;
    a2t[a_N] = u;
    t2a[u] = a_N;
    ++a_N;
    for (int i = 0; i < (int)CH[u].size(); ++i)
    {
        int v = CH[u][i].first;
        build_rmq(v, depth + 1);
        a[a_N] = depth;
        a2t[a_N] = u;
        ++a_N;
    }
}

void preprocess()
{
//    for (int u = 0; u < N; ++u)
//        for (int i = 0; i < (int)CH[u].size(); ++i)
//            printf("%d->%d: %lld\n", u, CH[u][i].first, CH[u][i].second);
    dist[root] = 0;
    build_dist(root);
//    for (int u = 0; u < N; ++u) printf("%lld ", dist[u]);
//    printf("\n");
    a_N = 0;
    build_rmq(root, 0);
//    for (int i = 0; i < a_N; ++i) printf("%d ", a[i]);
//    printf("\n");
//    for (int i = 0; i < a_N; ++i) printf("%d ", a2t[i]);
//    printf("\n");
//    for (int u = 0; u < N; ++u) printf("node %d: %d\n", u, t2a[u]);
//    printf("\n");
}

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int Q;
    while (scanf("%d", &N), N)
    {
        CH.assign( N, vil() );
        for (int i = 1; i < N; ++i)
        {
            int parent;
            ll cost;
            scanf("%d %lld", &parent, &cost);
            CH[parent].push_back( make_pair(i, cost) );
        }
        preprocess();
        RMQ rmq(a_N, a);
        scanf("%d", &Q);
        for (int i = 0; i < Q; ++i)
        {
            if (i != 0) printf(" ");
            int s, t;
            scanf("%d %d", &s, &t);
            int l = min(t2a[s], t2a[t]);
            int r = max(t2a[s], t2a[t]);
            int lca = a2t[ rmq.query(l, r) ]; // [l]owest [c]ommon [a]ncestor
            printf("%lld", dist[s] + dist[t] - 2*dist[lca]);
        }
        printf("\n");
    }
    return 0;
}
