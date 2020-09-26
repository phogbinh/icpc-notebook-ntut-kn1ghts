// All-Pairs Shortest Paths (APSP) solved with Floyd Warshall O(V^3).
// inside int main()
    // precondition: AdjMat[i][j] contains the weight of edge (i, j)
    // or INF (1B) if there is no such edge
    // AdjMat is a 32-bit signed integer array
    for (int k = 0; k < V; ++k)    // remember that loop order is k->i->j
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                AdjMat[i][j] = min( AdjMat[i][j], AdjMat[i][k] + AdjMat[k][j] );
