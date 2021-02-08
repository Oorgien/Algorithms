#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <deque>

std::pair<std::vector<int>, std::vector<int>> read() {
    //sorted from min to max
    std::vector<int> sorted, query;
    int n, k;
    std::cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int tmp;
        std::cin >> tmp;
        sorted.push_back(tmp);
    }
    for (int j = 0; j < k; j++) {
        int tmp;
        std::cin >> tmp;
        query.push_back(tmp);
    }
	return std::make_pair(sorted, query);
}

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

int search_closest(int& q, std::vector<int>& sorted) {
	int r = bin_search(sorted, q);
	if (r == -1) {
		return sorted[0];
	}
	else if (r == sorted.size()-1 || abs(q - sorted[r]) <= abs(q - sorted[r + 1])) {
		return sorted[r];
	}
	else return sorted[r+1];
}

void solve(std::vector<int>& query, std::vector<int>& sorted){
    for (int i = 0; i < query.size(); i++) {
        int q = query[i];
        int answer = search_closest(q, sorted);
        std::cout << answer << std::endl;
    }
}

void compound() {
	std::pair<std::vector<int>, std::vector<int>> vectors = read();
	solve(vectors.second, vectors.first);
}