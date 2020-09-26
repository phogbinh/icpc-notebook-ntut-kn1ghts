// This is a solution for UVa 10382 - Watering Grass. The problem is a variant
// of Interval Covering problem, which is solved by O(n) Greedy algorithm.

#include <bits/stdc++.h>

#define pb push_back
#define not_set -1

using namespace std;

typedef pair<double, double> dd;
typedef vector<dd> vdd;
typedef enum { STOP = 0,
               CONTINUE } status;

int n, l, w;
vdd spinklers;
int answer;
double pivot;

struct sort_compare_t {
    bool operator()(dd a, dd b) const {
        return a.first < b.first || (a.first == b.first && a.second > b.second);
    }
} sort_compare;

void InputSpinklers() {
    for (int i = 0; i < n; i++) {
        double x, r;  // must be double otherwise WA.
        scanf("%lf %lf", &x, &r);
        if (w > 2 * r)  // ignore spinklers that cannot cover the width of the strip.
        {
            continue;
        }
        if (w == 2 * r)  // ignore spinklers that produce no intervals.
        {
            continue;
        }
        double dx = sqrt(r * r - w * w / 4.0);
        spinklers.pb(dd(x - dx, x + dx));
    }
}

status Check(int& j) {
    if (j == not_set)  // there is an interval after pivot that cannot be covered.
    {
        return STOP;
    }
    // record j.
    answer++;
    pivot = spinklers[j].second;
    if (pivot >= l)  // solution found!
    {
        return STOP;
    }
    j = not_set;
    return CONTINUE;
}

void SolveIntervalCovering() {
    sort(spinklers.begin(), spinklers.end(), sort_compare);
    answer = 0;
    pivot = 0.0;
    int j = not_set;
    int iter = 0;
    while (true) {
        if (iter == spinklers.size())  // iterated through all spinklers/intervals.
        {
            Check(j);
            break;
        }

        if (spinklers[iter].first <= pivot) {
            if (pivot < spinklers[iter].second)  // note the next candidate down!
            {
                if (j == not_set || spinklers[iter].second > spinklers[j].second)  // note down the most right candidate.
                {
                    j = iter;
                }
                iter++;
            } else  // skip intervals that are completely covered by the previously selected ones.
            {
                iter++;
            }
        } else  // out bound.
        {
            if (Check(j) == STOP) {
                break;
            }
        }
    }

    if (pivot >= l) {
        printf("%d\n", answer);
    } else {
        printf("-1\n");
    }
}

int main() {
    while (scanf("%d %d %d", &n, &l, &w) != EOF) {
        spinklers.clear();
        InputSpinklers();
        SolveIntervalCovering();
    }
}