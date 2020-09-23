// Find connected components of an undirected graph using DFS.

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

enum { UNVISITED, VISITED };                     // basic flags

vector<vii> AL;                                  // adjacency list
vi dfs_num; 

void dfs(int u) {                                // normal usage
  printf(" %d", u);                              // this vertex is visited
  dfs_num[u] = VISITED;                          // mark u as visited
  for (int j = 0; j < (int)AL[u].size(); j++) {
    ii vw = AL[u][j];
    if (dfs_num[vw.first] == UNVISITED)          // to avoid cycle
      dfs(vw.first);                             // recursively visits v
  }
}

int main() {
  int V; scanf("%d", &V);
  AL.assign(V, vii());
  for (int u = 0; u < V; ++u) {
    int k; scanf("%d", &k);
    while (k--) {
      int v, w; scanf("%d %d", &v, &w);          // neighbors of vertex u
      AL[u].push_back(ii(v, w));
    }
  }

  dfs_num.assign(V, UNVISITED);                  // init V elements of UNVISITED
  int numCC = 0;
  for (int u = 0; u < V; ++u)                    // for each u in [0..V-1]
    if (dfs_num[u] == UNVISITED)                 // if that u is unvisited
      printf("CC %d:", ++numCC), dfs(u), printf("\n"); // 3 lines here!
  printf("There are %d connected components\n", numCC);

  return 0;
}

/*
Sample input:
9
1 1 0
3 0 0 2 0 3 0
2 1 0 3 0
3 1 0 2 0 4 0
1 3 0
0
2 7 0 8 0
1 6 0
1 6 0

Expected:
CC 1: 0 1 2 3 4
CC 2: 5
CC 3: 6 7 8
There are 3 connected components
*/
