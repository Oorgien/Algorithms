#pragma once
#include <vector>
#include <iostream>
#include <utility>
#include <stack>
//5
//20 10 1 5 3
//
std::vector<int> solve(std::vector<int>& v,const int n) {
	std::stack<int> s;
	std::vector<int> res(n);
	for (int i = 0; i < n; i++) {
		int a = v[i];
		int b = 0;
		if (!s.empty()) {
			b = v[s.top()];
		}
		if (!s.empty()) {
			if (v[i] > v[s.top()]) {
				while (!s.empty() && v[i] > v[s.top()]) {
					res[s.top()] = i + 1;
					s.pop();
				}
				s.push(i);
			}
			else if (v[i] < v[s.top()]) {
				s.push(i);
			}
		}
		else {
			s.push(i);
		}
	}
	while (!s.empty()) {
		if (res[s.top()] == 0) {
			res[s.top()] = -1;
			s.pop();
		}
	}
	return res;
}

std::pair<std::vector<int>, int> read() {
	int n = 0;
	std::cin >> n;
	std::vector<int> v;
	for (int i = 0; i < n; i++) {
		int tmp;
		std::cin >> tmp;
		v.push_back(tmp);
	}
	return std::make_pair(v, n);
}