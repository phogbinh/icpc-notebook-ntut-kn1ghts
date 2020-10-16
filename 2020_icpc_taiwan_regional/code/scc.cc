// Tarjan O(V + E)
vi dfs_num, dfs_low, visited;
int dfsNumberCounter, numSCC;
vi S;

void tarjanSCC(int u)
{
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;    // dfs_low[u] <= dfs_num[u]
    S.push_back(u);    // stores 'u' in a vector baesd on order of visitation
    visited[u] = 1;
    for (int i = 0; i < (int)AL[u].size(); ++i) // [A]djacency [L]ist
    {
        int v = AL[u][i].first;
        if (dfs_num[v] == UNVISITED) tarjanSCC(v);
        if (visited[v]) dfs_low[u] = min( dfs_low[u], dfs_low[v] ); // condition for update
    }

    if (dfs_low[u] == dfs_num[u])    // if this is a root (start) of an SCC
    {                                // this part is done after recursion
        printf("SCC %d:", ++numSCC);
        while (true)
        {
            int v = S.back(); S.pop_back();
            visited[v] = 0;
            printf(" %d", v);
            if (u == v) break;
        }
        printf("\n");
    }
}

// inside int main()
    dfs_num.assign(V, UNVISITED);
    dfs_low.assign(V, 0);
    visited.assign(V, 0);
    dfsNumberCounter = numSCC = 0;
    for (int u = 0; u < V; ++u)
        if (dfs_num[u] == UNVISITED)
            tarjanSCC(u);
