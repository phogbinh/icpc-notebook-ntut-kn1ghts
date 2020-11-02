// TopCoder ChessMatchup solved with Hungarian algorithm O(n^3).
#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_N 100
#define INF 1000000000

typedef vector<int> vi;

int N;
int cost[MAX_N][MAX_N];
int max_match;
int lx[MAX_N], ly[MAX_N]; // labels of X and Y parts
int xy[MAX_N]; // xy[x] - vertex that is matched with x
int yx[MAX_N]; // yx[y] - vertex that is matched with y
bool S[MAX_N], T[MAX_N]; // sets S and T in algorithm
int slack[MAX_N]; // as in the algorithm description
int slackx[MAX_N]; // slackx[y] such a vertex, that l(slackx[y]) + l(y) - w(slackx[y],y) = slack[y]
int pre[MAX_N]; // [pre]vious array for memorizing alternating paths

void init_labels()
{
    memset(lx, 0, sizeof lx);
    memset(ly, 0, sizeof ly);
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++) lx[x] = max(lx[x], cost[x][y]);
}

void update_labels()
{
    int x, y, delta = INF; // init delta as infinity
    for (y = 0; y < N; y++) // calculate delta using slack
        if ( !T[y] ) delta = min(delta, slack[y]);
    for (x = 0; x < N; x++) // update X labels
        if ( S[x] ) lx[x] -= delta;
    for (y = 0; y < N; y++) // update Y labels
        if ( T[y] ) ly[y] += delta;
    for (y = 0; y < N; y++) // update slack array
        if ( !T[y] ) slack[y] -= delta;
}

// x - current vertex,prevx - vertex from X before x in the alternating path, so
// we add edges (prevx, xy[x]), (xy[x], x)
void add_to_tree(int x, int prevx)
{
    S[x] = true; // add x to S
    pre[x] = prevx; // we need this when augmenting
    for (int y = 0; y < N; y++) // update slacks, because we add new vertex to S
        if (lx[x] + ly[y] - cost[x][y] < slack[y])
        {
            slack[y] = lx[x] + ly[y] - cost[x][y];
            slackx[y] = x;
        }
}

void augment() // main function of the algorithm
{
    if (max_match == N) return; // matching is perfect
    int x, y;
    int root = -1;
    int q[MAX_N], wr = 0, rd = 0; // q - queue for bfs, wr,rd - write and read pos in queue
    memset(S, false, sizeof S); // init set S
    memset(T, false, sizeof T); // init set T
    memset(pre, -1, sizeof pre); // init set prev - for the alternating tree
    for (x = 0; x < N; ++x) // finding root of the tree
        if (xy[x] == -1)
        {
            q[wr++] = root = x;
            pre[x] = -2;
            S[x] = true;
            break;
        }
    for (y = 0; y < N; ++y) // initializing slack array
    {
        slack[y] = lx[root] + ly[y] - cost[root][y];
        slackx[y] = root;
    }

    while (true) // main cycle
    {
        while (rd < wr) // building tree with bfs cycle
        {
            x = q[rd++]; // current vertex from X part
            for (y = 0; y < N; ++y) // iterate through all edges in equality graph
                if (cost[x][y] == lx[x] + ly[y] && !T[y])
                {
                    if (yx[y] == -1) break; // an exposed vertex in Y found, so augmenting path exists!
                    T[y] = true;            // else just add y to T,
                    q[wr++] = yx[y];        // add vertex yx[y], which is matched with y, to the queue
                    add_to_tree( yx[y], x ); // add edges (x,y) and (y,yx[y]) to the tree
                }
            if (y < N) break; // augmenting path found!
        }
        if (y < N) break; // augmenting path found!
        update_labels(); // augmenting path not found, so improve labeling
        wr = rd = 0;
        // in this cycle we add edges that were added to the equality graph as a
        // result of improving the labeling, we add edge (slackx[y], y) to the
        // tree if and only if !T[y] && slack[y] == 0, also with this edge we a-
        // dd another one (y, yx[y]) or augment the matching, if y was exposed.
        for (y = 0; y < N; ++y)
            if ( !T[y] && slack[y] == 0 )
            {
                if (yx[y] == -1) // exposed vertex in Y found - augmenting path exists!
                {
                    x = slackx[y];
                    break;
                }
                // else just add y to T
                T[y] = true;
                if (!S[yx[y]])
                {
                    q[wr++] = yx[y]; // add vertex yx[y], which is matched with y, to the queue
                    add_to_tree( yx[y], slackx[y] ); // and add edges (x,y) and (y, yx[y]) to the tree
                }
            }
        if (y < N) break; // augmenting path found!
    } // end main cycle
    if (y < N) // we found augmenting path!
    {
        ++max_match; // increment matching in this cycle we inverse edges along augmenting path
        for (int cx = x, cy = y, ty;
                           cx != -2;
              cx = pre[cx], cy = ty)
        {
            ty = xy[cx];
            yx[cy] = cx;
            xy[cx] = cy;
        }
        augment(); // recall function, go to step 1 of the algorithm
    }
}

int max_weight_perfect_bipartite_matching()
{
    int ret = 0; // weight of the optimal matching
    max_match = 0; // number of vertices in current matching
    memset(xy, -1, sizeof xy);
    memset(yx, -1, sizeof yx);
    init_labels(); // step 0
    augment(); // steps 1-3
    for (int x = 0; x < N; ++x) ret += cost[ x ][ xy[x] ];
    return ret;
}

class ChessMatchup
{
public:
    static int maximumScore(vi us, vi them)
    {
        N = (int)us.size(); // for TopCoder submission
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (us[i] > them[j]) cost[i][j] = 2;
                else if (us[i] == them[j]) cost[i][j] = 1;
                else cost[i][j] = 0;
        return max_weight_perfect_bipartite_matching();
    }
};

int main()
{
#ifdef LOCAL
    freopen("in2", "r", stdin);
#endif
    int us[MAX_N], them[MAX_N];
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) scanf("%d", &us[i]);
    for (int i = 0; i < N; ++i) scanf("%d", &them[i]);
    printf( "%d\n", ChessMatchup::maximumScore( vi(us, us+N), vi(them, them+N) ) );
    return 0;
}
