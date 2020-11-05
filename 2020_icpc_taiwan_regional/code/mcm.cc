// ACM Timus 1099 - Work Scheduling solved as Max Cardinality Matching (MCM) us-
// ing Edmonds Matching algorithm in O(V^2 * E).
#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_V 500

struct edge_t
{
    int v;
    edge_t* n; // [n]ext
};

typedef edge_t* edge_ptr;

int V;
edge_t pool[MAX_V*MAX_V*2];
edge_ptr p_top = pool;
edge_ptr adj[MAX_V];
int match[MAX_V];
int qh, qt;
int q[MAX_V];
int father[MAX_V], base[MAX_V];
bool inq[MAX_V], inb[MAX_V];

void add_edge(int u, int v)
{
    p_top->v = v, p_top->n = adj[u], adj[u] = p_top++;
    p_top->v = u, p_top->n = adj[v], adj[v] = p_top++;
}

int LCA(int root, int u, int v) // [L]owest [C]ommon [A]ncestor
{
    static bool inp[MAX_V];
    memset(inp, 0, sizeof inp);
    while (true)
    {
        inp[ u=base[u] ] = true;
        if (u==root) break;
        u = father[ match[u] ];
    }

    while (true)
    {
        if (inp[ v=base[v] ]) return v;
        else v = father[ match[v] ];
    }
}

void mark_blossom(int lca, int u)
{
    while (base[u] != lca)
    {
        int v = match[u];
        inb[ base[u] ] = inb[ base[v] ] = true;
        u = father[v];
        if (base[u] != lca) father[u] = v;
    }
}

void blossom_contraction(int s, int u, int v)
{
    int lca = LCA(s, u, v);
    memset(inb, 0, sizeof inb);
    mark_blossom(lca, u);
    mark_blossom(lca, v);
    if (base[u] != lca) father[u] = v;
    if (base[v] != lca) father[v] = u;
    for (int u = 0; u < V; ++u)
        if (inb[ base[u] ])
        {
            base[u] = lca;
            if (!inq[u]) inq[ q[++qt]=u ] = true;
        }
}

int find_augmenting_path(int s)
{
    memset(inq, 0, sizeof inq);
    memset(father, -1, sizeof father);
    for (int u = 0; u < V; ++u) base[u] = u;
    inq[ q[ qh=qt=0 ]=s ] = true;
    while (qh <= qt)
    {
        int u = q[qh++];
        for (edge_ptr p_e = adj[u]; p_e; p_e = p_e->n)
        {
            int v = p_e->v;
            if (base[u] == base[v] || match[u] == v) continue;
            if ( (v==s)
              || (match[v] != -1 && father[ match[v] ] != -1) )
            {
                blossom_contraction(s, u, v);
            }
            else if (father[v] == -1)
            {
                father[v] = u;
                if (match[v] == -1) return v;
                else if (!inq[ match[v] ]) inq[ q[++qt]=match[v] ] = true;
            }
        }
    }
    return -1;
}

bool augment_path(int s, int t)
{
    int v, w;
    int u = t;
    while (u != -1)
    {
        v = father[u];
        w = match[v];
        match[v] = u;
        match[u] = v;
        u = w;
    }
    return t != -1;
}

int edmonds()
{
    int match_N = 0;
    memset(match, -1, sizeof match);
    for (int u = 0; u < V; ++u)
        if (match[u] == -1) match_N += augment_path( u, find_augmenting_path(u) );
    return match_N;
}

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    scanf("%d", &V);
    int u, v;
    while (scanf("%d %d", &u, &v) != EOF)
    {
        --u; --v; // 0-based index
        add_edge(u, v);
    }
    printf("%d\n", edmonds() * 2);
    bool visited[MAX_V];
    memset(visited, false, sizeof visited);
    for (int u = 0; u < V; ++u)
        if (!visited[u] && match[u] != -1)
        {
            visited[u] = visited[ match[u] ] = true;
            printf("%d %d\n", u+1, match[u]+1); // 1-based index
        }
    return 0;
}
