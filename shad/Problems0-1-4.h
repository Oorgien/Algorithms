#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <deque>

std::tuple< int, std::vector<int>, int, std::vector<int> > read() {
    int n;
    std::cin >> n;
    std::vector<int> arr;
    for (int i = 0; i < n; i++) {
        int val = 0;
        std::cin >> val;
        arr.push_back(val);
    }
    int k;
    std::cin >> k;
    std::vector<int> query;
    for (int i = 0; i < k; i++) {
        std::string val;
        std::cin >> val;
        if (val == "R") query.push_back(1);
        else query.push_back(0);
    }
    return std::make_tuple(n, arr, k, query);
}

void solve1(int n, std::vector<int> arr, int k, std::vector<int> query) {
    int L = 0, R = 0;

    std::deque<int> s;
    s.push_back(0);
    for (int i = 0; i < k; i++) {
        if (query[i] == 0) {
            L++;
            while (!s.empty() && L > s.front()) s.pop_front();
            //while (arr[L] > arr[s.back()] && !s.empty()) {
            //    s.pop_back();
            //}
            //s.push_back(L);
            std::cout << arr[s.front()] << " ";
        }
        if (query[i] == 1) {
            R++;
            while (!s.empty() && arr[R] > arr[s.back()]) {
                s.pop_back();
            }
            s.push_back(R);
            std::cout << arr[s.front()] << " ";
        }
    }
}


void show(std::vector<int> res) {
    for (auto item : res) {
        std::cout << item << " ";
    }
}

void compound() {
    std::tuple< int, std::vector<int>, int, std::vector<int> > input = read();
    solve1(std::get<0>(input), std::get<1>(input), std::get<2>(input), std::get<3>(input));
}