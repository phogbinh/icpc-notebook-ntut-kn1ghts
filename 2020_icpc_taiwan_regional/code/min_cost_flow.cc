// UVa 10594 - Data Flow solved as Min-Cost Flow (MCF) problem using Edmonds Ka-
// rp and Bellman Ford algorithms with total time O(V^2 * E^3).
#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define INF 1000000000000000 // 10^15
#define bwd 0 // [b]ack[w]ar[d] direction
#define fwd 1 // [f]or[w]ar[d] direction
#define MAX_V 200

typedef vector<int> vi;
typedef long long int ll;
typedef pair<ll, ll> ll2;
typedef vector<ll> vll;

int V;
vector<vi> AL;
ll res[MAX_V][MAX_V][2], cst[MAX_V][MAX_V][2];
ll mf, f, min_cost;
int s, t;
vector< pair<int, ll> > p;
ll FLOW, CAPACITY;

void augment(int v, ll minEdge)
{
    if (v == s) { f = minEdge; return; }
    else if ( p[v].first != -1 )
    {
        augment( p[v].first, min(minEdge, res[ p[v].first ][ v ][ p[v].second ]) );
        res[ p[v].first ][ v ][ p[v].second ] -= f;
        res[ v ][ p[v].first ][ p[v].second ] += f;
    }
}

void trace_cost(int v)
{
    if (p[v].first == -1) return;
    min_cost += cst[ p[v].first ][ v ][ p[v].second ] * f;
    trace_cost(p[v].first);
}

void min_cost_flow()
{
    min_cost = 0;
    mf = 0;
    while (true)
    {
        f = 0;
        p.assign(MAX_V, make_pair(-1, -1));
        vll dist(V, INF); dist[s] = 0;
        for (int i = 0; i < V - 1; ++i)
            for (int u = 0; u < V; ++u)
                for (int j = 0; j < (int)AL[u].size(); ++j)
                {
                    int v = AL[u][j];
                    for (int dir = 0; dir <= 1; ++dir)
                        if (res[u][v][dir] > 0 && dist[u] + cst[u][v][dir] < dist[v])
                        {
                            dist[v] = dist[u] + cst[u][v][dir];
                            p[v] = make_pair(u, dir);
                        }
                }
        augment(t, INF);
        if (f == 0) break;
        f = min(f, FLOW - mf);
        trace_cost(t);
        mf += f;
        if (mf == FLOW) break;
    }
    if (mf < FLOW) printf("Impossible.\n");
    else printf("%lld\n", min_cost);
}

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int E;
    while (scanf("%d %d", &V, &E) != EOF)
    {
        AL.assign(V, vi());
        memset(res, 0, sizeof res);
        memset(cst, 0, sizeof cst);
        for (int i = 0; i < E; ++i)
        {
            int u, v;
            ll w;
            scanf("%d %d %lld", &u, &v, &w);
            u--; v--; // 0-based index
            AL[u].push_back(v);
            AL[v].push_back(u);

            res[u][v][fwd] = res[v][u][bwd] = 1; // real edges
            cst[u][v][fwd] = cst[v][u][bwd] = w;

            res[u][v][bwd] = res[v][u][fwd] = 0; // additional reversed edges
            cst[u][v][bwd] = cst[v][u][fwd] = -w;
        }

        scanf("%lld %lld", &FLOW, &CAPACITY);
        for (int u = 0; u < V; ++u)
            for (int v = 0; v < V; ++v)
            {
                res[u][v][fwd] *= CAPACITY;
                res[v][u][bwd] *= CAPACITY;
            }

        s = 0;
        t = V-1;
        min_cost_flow();
    }
    return 0;
}
