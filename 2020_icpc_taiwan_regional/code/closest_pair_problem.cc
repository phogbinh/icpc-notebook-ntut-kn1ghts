// UVa 10245 - The Closest Pair Problem solved in O(n log n).
#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_N 10050
#define INF 1000000000

typedef pair<double, double> dd;
typedef vector<dd> vdd;

dd a[MAX_N];

double dist(dd i, dd j)
{
    return sqrt( pow(i.first - j.first, 2.f) + pow(i.second - j.second, 2.f) );
}

double closest(int lo, int hi, vdd& y_sort)
{
    if (lo>hi) return INF;
    if (lo==hi)
    {
        y_sort.push_back(a[lo]);
        return INF;
    }

    // divide & conquer
    int mid = (lo+hi) / 2;
    vdd ys_o, ys_t;
    double d1 = closest(lo,    mid, ys_o);
    double d2 = closest(mid+1, hi,  ys_t);

    // merge sort
    int N_O = (int)ys_o.size();
    int N_T = (int)ys_t.size();
    int i = 0;
    int j = 0;
    while (true)
    {
        if (i >= N_O && j >= N_T) break;
        if (i >= N_O)
        {
            y_sort.push_back(ys_t[j++]);
            continue;
        }
        if (j >= N_T)
        {
            y_sort.push_back(ys_o[i++]);
            continue;
        }
        if ( ys_o[i].second < ys_t[j].second
          || (ys_o[i].second==ys_t[j].second && ys_o[i].first < ys_t[j].first) ) y_sort.push_back(ys_o[i++]);
          else y_sort.push_back(ys_t[j++]);
    }
//    for (int i = 0; i < (int)y_sort.size(); ++i)
//        printf("%lf %lf\n", y_sort[i].first, y_sort[i].second);
//    printf("\n");

    // retrieve d3 to combine
    if (lo + 1 == hi) return dist(a[lo], a[hi]);

    double d = min(d1, d2);
    double x_left = a[mid].first - d;
    double x_right = a[mid].first + d;
    vdd b;
    for (int i = 0; i < (int)y_sort.size(); ++i)
        if (x_left <= y_sort[i].first && y_sort[i].first <= x_right) b.push_back(y_sort[i]);

    double ret = d;
    for (int i = 1; i < (int)b.size(); ++i)
        for (int j = max(0, i-15); j < i; ++j)
            ret = min( ret, dist(b[i], b[j]) );

    return ret;
}

int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    #endif // LOCAL
    int N;
    while (scanf("%d", &N), N)
    {
        for (int i = 0; i < N; ++i) scanf("%lf %lf", &a[i].first, &a[i].second);
        sort(a, a+N);
//        for (int i = 0; i < N; ++i) printf("%lf %lf\n", a[i].first, a[i].second);
        vdd y_sort;
        double ret = closest(0, N-1, y_sort);
        if (ret<10000) printf("%.4lf\n", ret);
        else printf("INFINITY\n");
    }
    return 0;
}
