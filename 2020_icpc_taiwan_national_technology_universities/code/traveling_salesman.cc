// This is a solution for UVa 10496 - Collecting Beepers. The problem is a
// variant of the Traveling Salesman Problem (TSP): Given n cities and their
// pairwise distances in the form of a matrix 'dist' of size n * n, compute the
// minimum cost of making a tour that starts from any city s, goes through all
// the other n - 1 cities exactly once, and finally returns to the city s. In
// this case, the salesman is Karel in a 2D world who can only move along the
// x and y axis. The cities are beepers whose coordinates are given, from which
// pairwise distances can be calculated. Algorithm takes time O(2^n * n^2).
// INPUT: The first line is the number of test cases. The first line of each
// test case is world's size (x-size and y-size). Next is the starting position
// of Karel. Next is the number of beepers. Next are the beepers' x- and y-
// coordinates.
// OUTPUT: For each test case, output the minimum distance to move from Karel's
// starting position to each of the beepers and back to the starting position.

#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))

const int MAX_n = 11;

int dist[MAX_n][MAX_n], memo[MAX_n][1<<(MAX_n-1)]; // Karel + max 10 beepers

int dp(int u, int mask) {                        // mask = free coordinates
  if (mask == 0) return dist[u][0];              // close the loop
  int &ans = memo[u][mask];
  if (ans != -1) return ans;                     // computed before
  ans = 2000000000;
  int m = mask;
  while (m) {                                    // up to O(n)
    int two_pow_v = LSOne(m);                    // but this is fast
    int v = __builtin_ctz(two_pow_v)+1;          // offset v by +1
    ans = min(ans, dist[u][v] + dp(v, mask^two_pow_v)); // keep the min
    m -= two_pow_v;
  }
  return ans;
}

int main() {
  int TC; scanf("%d", &TC);
  while (TC--) {
    int xsize, ysize; scanf("%d %d", &xsize, &ysize); // these two values are not used
    int x[MAX_n], y[MAX_n];
    scanf("%d %d", &x[0], &y[0]);
    int n; scanf("%d", &n); ++n;                 // include Karel
    for (int i = 1; i < n; ++i)                  // Karel is at index 0
      scanf("%d %d", &x[i], &y[i]);
    for (int i = 0; i < n; ++i)                  // build distance table
      for (int j = i; j < n; ++j)
        dist[i][j] = dist[j][i] = abs(x[i]-x[j]) + abs(y[i]-y[j]); // Manhattan distance
    memset(memo, -1, sizeof memo);
    printf("The shortest path has length %d\n", dp(0, (1<<(n-1))-1)); // DP-TSP
  }
  return 0;
}
