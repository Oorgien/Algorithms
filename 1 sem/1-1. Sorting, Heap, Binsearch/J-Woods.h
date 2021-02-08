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

double const EPS = 10e-5;
double Vp, Vf, a;

double f(double x)
{
    return (sqrt((1 - a) * (1 - a) + x * x)) / Vp
        + (sqrt((1 - x) * (1 - x) + a * a)) / Vf;
}

int compound()
{
    std::cin >> Vp >> Vf;
    std::cin >> a;

    double l = 0;
    double r = 1;

    while (r - l > EPS)
    {
        double x = (2 * l + r) / 3;
        double y = (l + 2 * r) / 3;
        if (f(x) > f(y))
            l = x;
        else
            r = y;
    }

    std::cout << std::fixed << std::setprecision(6) << r;
}