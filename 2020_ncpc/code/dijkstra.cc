
// Dijkstra implementation for negative weight edges O((V + E) log V)
    vi dist(V, INF); dist[s] = 0;
    priority_queue< ii, vii, greater<ii> > pq;
    pq.push( ii(0, s) );
    while (!pq.empty())
    {
        ii front = pq.top(); pq.pop();
        int d = front.first;
        int u = front.second;
        if (d > dist[u]) continue;
        for (int i = 0; i < (int)AL[u].size(); ++i) // [A]djacency [L]ist
        {
            ii vw = AL[u][i];
            int v = vw.first;
            int w = vw.second;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;    // relax operation
                pq.push( ii(dist[v], v) );
            }
        }
    } // this variant can cause duplicate items in the priority queue
