int res[MAX_V][MAX_V], mf, f, s, t;
vi p; // p stores the BFS spanning tree from s

void augment(int v, int minEdge)
{
    if (v == s) { f = minEdge; return; }
    else if ( p[v] != -1 )
    {
        augment( p[v], min(minEdge, res[ p[v] ][ v ]) );
        res[ p[v] ][ v ] -= f;
        res[ v ][ p[v] ] += f;
    }
}

// inside int main(): set up 'res', 's', and 't' with appropriate values
    mf = 0;
    while (true)    // O(V^3 * E) Edmonds Karp's algorithm
    {
        f = 0;
        vi dist(MAX_V, INF); dist[s] = 0;
        queue<int> q; q.push(s);
        p.assign(MAX_V, -1);
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            if (u == t) break; // immediately stop BFS if we already reach sink t
            for (int v = 0; v < MAX_V; ++v)
                if (res[u][v] > 0 && dist[v] == INF)
                    dist[v] = dist[u] + 1, q.push(v), p[v] = u;
        }
        augment(t, INF);   // find the min edge weight 'f' in this path, if any
        if (f == 0) break; // we cannot send any more flow ('f' = 0), terminate
        mf += f;           // we can still send a flow, increase the max flow!
    }
    printf("%d\n", mf);
