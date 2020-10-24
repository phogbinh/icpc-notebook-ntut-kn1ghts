// 2-SAT Problem demonstrated with 2018 ICPC Korea Regional - Problem K.
#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define blue(k) (k<<1)
#define red(k) (blue(k) + 1)
#define UNVISITED -1
#define neg(v) (v ^ 1) // [neg]ation of

typedef vector<int> vi;

int K, N;
int V;
vector<vi> AL;
bool possible = true;
vi sccNum;

int getVertex(pair<int, char> p)
{
    return p.second == 'B' ? blue(p.first) : red(p.first);
}

pair<int, char> negation(pair<int, char> p)
{
    return make_pair(p.first, p.second == 'B' ? 'R' : 'B');
}

void createEdge(pair<int, char> p, pair<int, char> q)
{
    int u, v;
    u = getVertex( negation(p) );
    v = getVertex( q );
//    printf("%d->%d\n", u, v);
    AL[u].push_back(v);

    u = getVertex( negation(q) );
    v = getVertex( p );
//    printf("%d->%d\n\n", u, v);
    AL[u].push_back(v);
}

vi dfs_num, dfs_low, visited;
int dfsNumberCounter, numSCC;
vi S;

void tarjanSCC(int u)
{
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
    S.push_back(u);
    visited[u] = 1;
    for (int i = 0; i < (int)AL[u].size(); ++i)
    {
        int v = AL[u][i];
        if (dfs_num[v] == UNVISITED) tarjanSCC(v);
        if (visited[v]) dfs_low[u] = min( dfs_low[u], dfs_low[v] );
    }

    if (dfs_low[u] == dfs_num[u])
    {
        set<int> st;
        ++numSCC;
//        printf("SCC %d:", numSCC);
        while (true)
        {
            int v = S.back(); S.pop_back();
            visited[v] = 0;

            if ( st.find(neg(v)) != st.end() ) possible = false;
            st.insert(v);

            sccNum[v] = numSCC;    // Tarjan produces SCCs in reversed topo order
//            printf(" %d", v);
            if (u==v) break;
        }
//        printf("\n");
    }
}

void work()
{
    sccNum.assign(V, 0);
    dfs_num.assign(V, UNVISITED);
    dfs_low.assign(V, 0);
    visited.assign(V, 0);
    dfsNumberCounter = numSCC = 0;
    for (int u = 0; u < V; ++u)
        if (dfs_num[u] == UNVISITED)
            tarjanSCC(u);

    if (!possible)
    {
        printf("-1\n");
        return;
    }

    for (int i = 1; i <= K; ++i)
        printf("%c", sccNum[blue(i)] > sccNum[red(i)] ? 'R' : 'B'); // 2-SAT assignment based on reversed topo order
    printf("\n");
}

int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    #endif // LOCAL
    scanf("%d %d", &K, &N);
    V = 2 * K + 2;
    AL.assign(V, vi());
    for (int i = 0; i < N; ++i)
    {
        pair<int, char> a[3];
        for (int j = 0; j < 3; ++j) scanf("%d %c", &a[j].first, &a[j].second);
//        for (int j = 0; j < 3; ++j) printf("%d %c ", a[j].first, a[j].second);
//        printf("\n");
        createEdge(a[0], a[1]);
        createEdge(a[0], a[2]);
        createEdge(a[1], a[2]);
    }

    work();

    return 0;
}