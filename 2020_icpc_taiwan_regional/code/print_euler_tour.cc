// Given an Eulerian-tour graph - a connected undirected graph whose vertices a-
// ll have even degrees, produce its Euler tour. The graph is unweighted, stored
// in an adjacency list where the second attribute in edge info pair is a boole-
// an '1' (edge can still be used) or '0' (edge can no longer be used).
list<int> cyc;    // we need list for fast insertion in the middle

void EulerTour(list<int>::iterator i, int u)
{
    for (int j = 0; j < (int)AL[u].size(); ++j) // [A]djacency [L]ist
    {
        ii& vw = AL[u][j];
        int v = vw.first;
        if (vw.second)    // if this edge can still be used
        {
            vw.second = 0;    // remove this edge
            // remove bi-directional edge
            for (int k = 0; k < (int)AL[v].size(); ++k)
            {
                ii& uw = AL[v][k];
                if (uw.first == u && uw.second)
                {
                    uw.second = 0;
                    break;
                }
            }
            // continue the tour
            EulerTour(cyc.insert(i, u), v);
        }
    }
}

// inside int main()
    cyc.clear();
    EulerTour(cyc.end(), 0);    // 'cyc' contains an Euler tour starting at vertex '0'
    for (list<int>::iterator i = cyc.begin(); i != cyc.end(); ++i)
        printf("%d\n", *i);
