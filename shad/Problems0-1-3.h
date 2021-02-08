#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>

std::pair<int, std::vector<std::vector<int>>> read() {
	size_t n;
	//= { std::vector<int>(3) };
	std::cin >> n;
	std::vector < std::vector<int>> res(n);
	for (int i = 0; i < n; i++) {
		int a, b, c;
		std::cin >> a >> b >> c;
		res[i].push_back(a);
		res[i].push_back(b);
		res[i].push_back(c);
	}
	return std::make_pair(n, res);
}

bool customLess(const std::vector<int> left, const std::vector<int> right) {
	return left[0] * left[2] * left[2] < right[0] * right[2] * right[2];
}

int solve(std::pair<int, std::vector<std::vector<int>>> p) {
	int n = p.first;
	std::vector < std::vector<int>> v = p.second;
	std::vector <std::vector<int>> l(n, std::vector<int>(3, 1));
	std::vector<int> res(3,0);
	// std::sort(v.begin(), v.end(), customLess);
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < n; i++) {
			for (int k = 0; k < i; k++) {
				if (v[i][j] > v[k][j] && l[i][j] < l[k][j] + 1) {
					l[i][j] = l[k][j] + 1;
				}
			}
			if (l[i][j] > res[j]) {
				res[j] = l[i][j];
			}
		}
	}
	auto pt = std::min_element(res.begin(), res.end());
	return *pt;
}