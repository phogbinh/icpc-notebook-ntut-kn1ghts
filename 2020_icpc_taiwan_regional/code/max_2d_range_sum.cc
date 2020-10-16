// Max 2D Range Sum - UVa 108 - solved with DP O(n^4).
// Abridged problem statement: Given an n x n square matrix of integers A where
// each integer ranges from [-127..127], find a sub-matrix of A with the maximum
// sum.
#include <bits/stdc++.h>
using namespace std;
int A[200][200];
int main() {
  int n; scanf("%d", &n);                        // square matrix size
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      scanf("%d", &A[i][j]);
      if (i > 0) A[i][j] += A[i-1][j];           // add from top
      if (j > 0) A[i][j] += A[i][j-1];           // add from left
      if (i > 0 && j > 0) A[i][j] -= A[i-1][j-1];// avoid double count
    }                                            // inclusion-exclusion
  int maxSubRect = -127*100*100;                 // the lowest possible val
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)                  // start coordinate
      for (int k = i; k < n; ++k)
        for (int l = j; l < n; ++l) {            // end coord
          int subRect = A[k][l];                 // from (0, 0) to (k, l)
          if (i > 0) subRect -= A[i-1][l];       // O(1)
          if (j > 0) subRect -= A[k][j-1];       // O(1)
          if (i > 0 && j > 0) subRect += A[i-1][j-1]; // O(1)
          maxSubRect = max(maxSubRect, subRect); // the answer is here
        }
  printf("%d\n", maxSubRect);
  return 0;
}
