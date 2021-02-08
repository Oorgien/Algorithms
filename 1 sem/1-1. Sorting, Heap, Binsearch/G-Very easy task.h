#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <deque>

int bin_search(std::vector<int>& a, int x)
{
    int l = -1;
    int r = a.size();
    while (r - l > 1)
    {
        int m = (r + l) / 2;
        if (a[m] <= x)
            l = m;
        else
            r = m;
    }
    return l;
}

void compound() {
	int n, x, y;
	std::cin >> n >> x >> y;

    n--;

    int l = -1;
    int r = n * std::max(x, y) + 1; // n * y - столько секунд будет печатать только второй принтер

    while (r - l> 1)
    {
        int m = (r + l) / 2; // m - potential amount of seconds
        if (m / x + m / y < n) // m / x - sheets for 1 printer, m / y - sheers for 2 printer
            l = m;
        else
            r = m;
    }

    std::cout << std::min(x, y) + r;
}