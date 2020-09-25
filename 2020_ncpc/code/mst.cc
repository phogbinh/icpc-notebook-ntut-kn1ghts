// Minimum Spanning Tree (MST) solved with Kruskal O(E log V)
// inside int main()
    vector< pair<int, ii> > EdgeList;    // (weight, two vertices) of the edge
    for (int i = 0; i < E; ++i)
    {
        scanf("%d %d %d", &u, &v, &w);
        EdgeList.push_back( make_pair( w, ii(u, v) ) );
    }
    sort(EdgeList.begin(), EdgeList.end()); // sort by edge weight O(E log E)
    int mst_cost = 0;
    UnionFind UF(V);    // all V are disjoint sets initially
    for (int i = 0; i < E; ++i)
    {
        pair<int, ii> front = EdgeList[i];
        if (!UF.isSameSet(front.second.first, front.second.second))
        {
            mst_cost += front.first;
            UF.unionSet(front.second.first, front.second.second);
        }
    }
    printf("MST cost = %d\n", mst_cost);
