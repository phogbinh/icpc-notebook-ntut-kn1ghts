// All-Pairs Shortest Paths (APSP) solved with Floyd Warshall O(V^3).
// inside int main()
    // precondition: AdjMat[i][j] contains the weight of edge (i, j)
    // or INF (1B) if there is no such edge
    // AdjMat is a 32-bit signed integer array
    // let p be a 2D parent matrix, where p[i][j] is the last vertex before j
    // on a shortest path from i to j, i.e. i -> ... -> p[i][j] -> j
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            p[i][j] = i;    // initialize the parent matrix
    for (int k = 0; k < V; ++k)    // remember that loop order is k->i->j
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                if (AdjMat[i][k] + AdjMat[k][j] < AdjMat[i][j])
                {
                    AdjMat[i][j] = AdjMat[i][k] + AdjMat[k][j];
                    p[i][j] = p[k][j];
                }
// print shortest paths
void printPath(int i, int j)
{
    if (i != j) printPath(i, p[i][j]);
    printf(" %d", j);
}
