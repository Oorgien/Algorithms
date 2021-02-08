#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <deque>

void compound() {
    long long int w, h, n;
    std::cin >> w >> h >> n;

    long long int l = std::min(w, h);
    long long int r = std::max(w, h) * n;

    while (r - l > 1)
    {
        long long int m = (r + l) / 2;

        // m - side of a square, 
        // m/h - how many h will fit in m,
        // m/w - how many w will fit in m
        long long int k = (m / w) * (m / h);
        if (k < n) 
            l = m;
        else
            r = m;
    }

    std::cout << r;
}