// Max 1D Range Sum solved with Jay Kadane O(n).
// inside int main()
    int n = 9;
    int A[] = { 4, -5, 4, -3, 4, 4, -4, 4, -5 }; // a sample array A
    int sum = 0;
    int ans = 0; // important, 'ans' must be initialized to 0
    for (int i = 0; i < n; ++i)
    {
        sum += A[i];
        ans = max(ans, sum);
        if (sum < 0) sum = 0;
    }
    printf("Max 1D Range Sum = %d\n", ans);
