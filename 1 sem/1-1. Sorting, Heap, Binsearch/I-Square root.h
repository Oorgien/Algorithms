#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <deque>
#include <iomanip>

double const EPS = 10e-6;

double f(double x)
{
    return x * x + sqrt(x);
}

int compound()
{
    double c;
    std::cin >> c;

    double l = 1;
    double r = 1;
    while (f(r) < c)
        r *= 2;

    while (r - l > EPS)
    {
        double m = (l + r) / 2;
        if (f(m) < c)
            l = m;
        else
            r = m;
    }

    std::cout << std::fixed << std::setprecision(6) << r;
}