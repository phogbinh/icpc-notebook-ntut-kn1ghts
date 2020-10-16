// Find articulation points & bridges solved with DFS O(V + E).
void articulationPointAndBridge(int u)
{
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;    // dfs_low[u] <= dfs_num[u]
    for (int i = 0; i < (int)AL[u].size(); ++i)    // [A]djacency [L]ist
    {
        int v = AL[u][i].first;
        if (dfs_num[v] == UNVISITED)    // a tree edge
        {
            dfs_parent[v] = u;
            if (u == dfsRoot) ++rootChildren;    // special case if 'u' is a root

            articulationPointAndBridge(v);

            if (dfs_low[v] >= dfs_num[u]) articulation_vertex[u] = true;
            if (dfs_low[v] > dfs_num[u]) printf("Edge (%d, %d) is a bridge\n", u, v);

            dfs_low[u] = min( dfs_low[u], dfs_low[v] );    // update dfs_low[u]
        }
        else if (v != dfs_parent[u]) dfs_low[u] = min( dfs_low[u], dfs_num[v] ); // update dfs_low[u]
    }
}

// inside int main()
    dfsNumberCounter = 0;
    dfs_num.assign(V, UNVISITED);
    dfs_low.assign(v, 0);
    dfs_parent.assign(V, 0);
    articulation_vertex.assign(V, 0);
    printf("Bridges:\n");
    for (int u = 0; u < V; ++u)
        if (dfs_num[u] == UNVISITED)
        {
            dfsRoot = u;
            rootChildren = 0;
            articulationPointAndBridge(u);
            articulation_vertex[dfsRoot] = (rootChildren > 1);    // special case
        }
    printf("Articulation Points:\n");
    for (int u = 0; u < V; ++u)
        if (articulation_vertex[u]) printf(" Vertex %d\n", u);
