#include <bits/stdc++.h>

using namespace std;

//#define LOCAL
#define N 4          // #rows/columns
#define B 15         // [B]lank tile id
#define PUZZLE (N*N)
#define MAX_STEPS 45 // given by the problem description
#define DIR 4        // 4 [DIR]ections

int dr[DIR] = {0, -1, 0, 1}; // must be right, up, left, down
int dc[DIR] = {1, 0, -1, 0}; // for the XOR operation to work
char dm[] = "RULD";          // [d]irection [m]ove

int p[PUZZLE];
int b_init_pos;      // [b]lank [init]ial [pos]ition
int lim;             // current [lim]it of the Iterative Deepening Search (IDS)
int pred[MAX_STEPS]; // [pre]viously used [d]irection to go to the current state

bool isViable()
{
    int sum;
    for (int i = 0; i < PUZZLE; ++i)
        for (int j = 0; j < i; ++j)
            if (p[j] > p[i]) ++sum;
    sum += b_init_pos / N + b_init_pos % N;
    sum -=          B / N +          B % N;
    return sum % 2 == 0;
}

int H()
{
    int h = 0;
    for (int pos = 0; pos < PUZZLE; ++pos)    // for all tile 'p[pos]'
    {                                         // compute Manhattan distance to goal state
        if (p[pos] == B) continue;
        h += abs( p[pos] / N - pos / N )      // position of 'p[pos]' in goal    state is 'p[pos]'
           + abs( p[pos] % N - pos % N );     // position of 'p[pos]' in current state is 'pos'
    }
    return h;
}

bool isValid(int r, int c)
{
    return 0 <= r && r < N && 0 <= c && c < N;
}

int Delta_H(int cur_r, int cur_c, int next_r, int next_c)
{
    int val = p[cur_r * N + cur_c]; // [val]ue of the tile being moved into the blank tile position
    int goal_r = val / N;           // position of 'val' in goal state is 'val'
    int goal_c = val % N;           // get row & column representation of the position
    return - ( abs(goal_r - cur_r ) + abs(goal_c - cur_c ) )
           + ( abs(goal_r - next_r) + abs(goal_c - next_c) );
}

bool dfs(int g, int h, int b_pos)
{
    if (g + h > lim) return false;
    if (h == 0) return true;    // found a solution!
    int r = b_pos / N;
    int c = b_pos % N;
    for (int d = 0; d < DIR; ++d)
    {
        if ( g != 0 && d == (pred[g] ^ 2) ) continue; // abort if this direction gets us back to parent state
        int next_r = r + dr[d];
        int next_c = c + dc[d];
        if ( !isValid(next_r, next_c) ) continue;
        int next_h = h + Delta_H(next_r, next_c, r, c); // O(1)
        int b_next_pos = next_r * N + next_c;
        swap(p[b_pos], p[b_next_pos]);
        pred[g+1] = d;

        if ( dfs(g + 1, next_h, b_next_pos) ) return true;

        swap(p[b_pos], p[b_next_pos]);
    }
    return false;
}

int ida_star()
{
    int init_h = H();
    lim = init_h;
    while (lim <= MAX_STEPS)
    {
        if ( dfs(0, init_h, b_init_pos) ) return lim;
        ++lim;
    }
    return -1;
}

void output(int steps)
{
    for (int i = 1; i <= steps; ++i)
        printf("%c", dm[ pred[i] ]);
}

int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    #endif // LOCAL
    int T;
    scanf("%d", &T);
    while (T--)
    {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
        {
            int pos = i * N + j;
            scanf("%d", &p[pos]);
            if (p[pos] == 0) p[pos] = B, b_init_pos = pos; // goal state 'p' is 0, 1, 2..14, 15
            else --p[pos];                                 // blank tile as 15
        }
        if ( !isViable() ) // must-consider condition otherwise TLE
        {
            printf("This puzzle is not solvable.\n");
            continue;
        }
        int ret = ida_star();
        if (ret == -1)
        {
            printf("This puzzle is not solvable.\n");
            continue;
        }
        output(ret), printf("\n");
    }
    return 0;
}
