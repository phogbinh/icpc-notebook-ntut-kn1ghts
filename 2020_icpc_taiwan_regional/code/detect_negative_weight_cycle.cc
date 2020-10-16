// Bellman Ford's O(VE)
    vi dist(V, INF); dist[s] = 0;
    for (int i = 0; i < V - 1; ++i)    // relax all E edges V - 1 times
        for (int u = 0; u < V; ++u)    // these two loops = O(E)
            for (int j = 0; j < (int)AL[u].size(); ++j) // [A]djacency [L]ist
            {
                ii vw = AL[u][j];
                dist[vw.first] = min( dist[vw.first], dist[u] + vw.second ); // relax
            }
