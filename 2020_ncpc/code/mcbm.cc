// Max Cardinality Bipartite Matching (MCBM) solved with augmenting path algorithm O(VE).
vi match, vis;

int Aug(int l)    // return 1 if an augmenting path is found & 0 otherwise
{
    if (vis[l]) return 0;
    vis[l] = 1;
    for (int i = 0; i < (int)AL[l].size(); ++i) // [A]djacency [L]ist
    {
        int r = AL[l][i];    // edge weight not needed -> vector< vi > AL
        if ( match[r] == -1 || Aug(match[r]) )
        {
            match[r] = l;
            return 1;    // found 1 matching
        }
    }
    return 0;            // no matchings
}

// inside int main()
    // build unweighted bipartite graph with directed edge left->right set
    int MCBM = 0;
    match.assign(V, -1); // V is the number of vertices in bipartite graph
    for (int l = 0; i < N; ++l)    // N = size of the left set
    {
        vis.assign(N, 0);    // reset before each recursion
        MCBM += Aug(l);
    }
    printf("Found %d matchings\n", MCBM);
