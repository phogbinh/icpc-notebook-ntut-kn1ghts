// This problem is a solution for UVa 10004 - Bicoloring. In this problem, we
// want to check if a graph is bipartite (or 2/bi-colorable) using BFS.

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

const int INF = 1e9;

int main() {
  int n;
  while (scanf("%d", &n), n) {
    // adjacency list u - v_1, v_2, ..., v_k
    vector<vi> AL(n, vi());                      // notice: vi, not vii
    int l; scanf("%d", &l);
    while (l--) {
      int a, b; scanf("%d %d", &a, &b);
      AL[a].push_back(b);
      AL[b].push_back(a);                        // bidirectional
    }
    int s = 0;
    queue<int> q; q.push(s);
    vi color(n, INF); color[s] = 0;
    bool isBipartite = true;                     // add a Boolean flag
    while (!q.empty() && isBipartite) {          // as with original BFS
      int u = q.front(); q.pop();
      for (int j = 0; j < (int)AL[u].size(); j++) {
        int v = AL[u][j];
        if (color[v] == INF) {                   // don't record distances
          color[v] = 1-color[u];                 // just record two colors
          q.push(v);
        }
        else if (color[v] == color[u]) {         // u & v have same color
          isBipartite = false;                   // a coloring conflict :(
          break;                                 // optional speedup
        }
      }
    }
    printf("%sBICOLORABLE.\n", (isBipartite ? "" : "NOT "));
  }
  return 0;
}
