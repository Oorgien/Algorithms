#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

void set(vector<long long>& tree, int i, int v, int x, int lx, int rx) {
    // i - index to insert in
    // v - what to insert
    // x - index of tree
    // lx - left border
    // rx - right border

    if (rx == lx) {
        tree[x] = v;
    }
    else {
        int m = (rx + lx) / 2;
        if (i <= m) {
            set(tree, i, v, 2 * x + 1, lx, m);
        }
        else {
            set(tree, i, v, 2 * x + 2, m+1, rx);
        }
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];

    }
}

void build(vector<long long>& tree, vector<long long>& a, int tl, int tr, int i) {
    if (tl == tr) {
        tree[i] = a[tl];
    }
    else {
        int m = (tl + tr) / 2;
        build(tree, a, tl, m, i * 2 + 1);
        build(tree, a, m + 1, tr, i * 2 + 2);
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }
}

long long sum(vector<long long>& tree,
    int lx, int rx,
    int l, int r,
    int x) {
    if (lx >= l && rx <= r) {
        return tree[x];
    }
    if (l > rx || r < lx) {
        return 0;
    }
    
    int m = lx + (rx - lx) / 2;
    long long sl = sum(tree, lx, m, l, r, 2 * x + 1);
    long long sr = sum(tree, m + 1, rx, l, r, 2 * x + 2);
    return sl + sr;
}

long long sum_2(vector<long long>& t, 
    int v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && r == tr)
        return t[v];
    int tm = (tl + tr) / 2;
    return sum_2(t, v * 2 + 1, tl, tm, l, min(r, tm))
        + sum_2(t, v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);
}

void compound() {
    int n;
    cin >> n;
    int k = ceil(log2(n));
    vector<long long> tree((1 << 19) * 2 - 1); // Округляем до ближайшей степени двойки сверху
    vector<long long> a;

    for (int i = 0; i < n; i++) {
        // cin >> tree[n - 1 + i];
        long long el;
        cin >> el;
        a.push_back(el);
    }
    build(tree, a, 0, n - 1, 0);


    // for ( int i = n-2; i >= 0; i--){
    //     tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    // }

    string query;
    while (cin >> query) {
        if (query == "set") {
            long long i, v;
            cin >> i >> v;
            set(tree, i-1, v, 0, 0, n-1);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << sum(tree, 0, n - 1, l - 1, r - 1, 0) << endl;
            //cout << sum_2(tree, 0, 0, n - 1, l - 1, r - 1) << endl;
        }
    }

}