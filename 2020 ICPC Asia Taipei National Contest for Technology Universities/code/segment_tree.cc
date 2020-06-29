// This is a solution for UVa12299 - RMQ with Shifts. In this problem, we are
// given an array of integers A and a list of queries of 2 types:
//     1. query(L, R) returns the minimum value in A[L...R].
//     2. shift(i_1, i_2, ..., i_k) performs a left "circular shift" of A[i_1],
//        A[i_2], ..., A[i_k]. For example, if A = {6, 2, 4, 8, 5, 1, 4}, then
//        shift(2, 4, 5, 7) yields 6, 8, 4, 5, 4, 1, 2. After that, shift(1, 2)
//        yields 8, 6, 4, 5, 4, 1, 2.

#include <bits/stdc++.h>

#define LEFT_CHILD(x) ((x << 1) + 1)
#define RIGHT_CHILD(x) ((x << 1) + 2)
#define INF 99999999
#define MAX_N 100005

using namespace std;

int queryParams[35], numbers[MAX_N], queryParamsCount;
string inputQuery;

struct node_t {
    int left, right, minValue;
} nodes[4 * MAX_N];

void build(int left, int right, int x = 0) {
    nodes[x].left = left;
    nodes[x].right = right;
    if (left == right) {
        nodes[x].minValue = numbers[left];
        return;
    }
    int mid = (left + right) / 2;
    build(left, mid, LEFT_CHILD(x));
    build(mid + 1, right, RIGHT_CHILD(x));
    nodes[x].minValue = min(nodes[LEFT_CHILD(x)].minValue, nodes[RIGHT_CHILD(x)].minValue);
}

void parseInputQuery() {
    queryParamsCount = 0;
    queryParams[queryParamsCount] = 0;
    // Parse input query starting from after opening parenthesis i.e. index 6.
    for (int i = 6; i < inputQuery.length(); i++) {
        if ('0' <= inputQuery[i] && inputQuery[i] <= '9') {
            queryParams[queryParamsCount] = queryParams[queryParamsCount] * 10 + (int)(inputQuery[i] - '0');
        }
        else {
            queryParams[++queryParamsCount] = 0; // next query parameter!
        }
    }
}

int query(int left, int right, int x = 0) {
    if (left <= nodes[x].left && nodes[x].right <= right) {
        return nodes[x].minValue;
    }
    int mid = (nodes[x].left + nodes[x].right) / 2;
    int ans = INF;
    if (left <= mid) {
        ans = min(ans, query(left, right, LEFT_CHILD(x)));
    }
    if (mid < right) {
        ans = min(ans, query(left, right, RIGHT_CHILD(x)));
    }
    return ans;
}

void setValue(int position, int newValue, int x = 0) {
    if (nodes[x].left == position && nodes[x].right == position) {
       nodes[x].minValue = newValue;
       return;
    }
    int mid = (nodes[x].left + nodes[x].right) / 2;
    if (position <= mid) {
        setValue(position, newValue, LEFT_CHILD(x));
    }
    if (mid < position) {
        setValue(position, newValue, RIGHT_CHILD(x));
    }
    nodes[x].minValue = min(nodes[LEFT_CHILD(x)].minValue, nodes[RIGHT_CHILD(x)].minValue);
}

int main()
{
    int n, q, placeholder;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> numbers[i];
    }
    build(1, n);
    while (q--) {
        cin >> inputQuery;
        if (inputQuery[0] == 'q') { // perform operation query.
            parseInputQuery();
            cout << query(queryParams[0], queryParams[1]) << '\n';
        }
        else if (inputQuery[0] == 's') { // perform operation shift.
            parseInputQuery();
            placeholder = numbers[queryParams[0]];
            for (int i = 1; i < queryParamsCount; i++) {
                setValue(queryParams[i - 1], numbers[queryParams[i]]);
                numbers[queryParams[i - 1]] = numbers[queryParams[i]];
            }
            setValue(queryParams[queryParamsCount - 1], placeholder);
            numbers[queryParams[queryParamsCount - 1]] = placeholder;
        }
    }
    return 0;
}
