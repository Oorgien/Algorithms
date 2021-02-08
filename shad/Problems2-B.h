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


std::vector<std::pair<int, int>> read() {
	int n;
	std::cin >> n;
	std::vector<std::pair<int, int>> res;
	for (int i = 0; i < n; i++) {
		int tmp;
		std::cin >> tmp;
		res.push_back(std::make_pair(tmp, i));
	}
	return res;
}

bool comp(const std::pair<int, int>  &l, const std::pair<int,int> &r) {
	return l.first < r.first;
}

void solve(std::vector<std::pair<int, int>> &v) {
	int n = v.size();
	std::sort(v.begin(), v.end(), comp);
	int i = 0;
	int j = 2;
	int sum = v[i].first + v[i + 1].first;
	while(j < n){
		if (v[j].first > v[i].first + v[i + 1].first && j-i > 1) {
			sum = sum - v[i].first;
			i++;
		}
		else {
			sum += v[j].first;
			j++;
		}
		
	}
	std::cout << sum << std::endl;
	std::vector<int> res;
	for (int p = i; p < j; p++) {
		res.push_back(v[p].second);	
	}
	std::sort(res.begin(), res.end());
	
	for (auto &item: res) {
		std::cout << item + 1 << " ";
	}
}

void compound() {
	std::vector<std::pair<int, int>> v = read();
	solve(v);
}