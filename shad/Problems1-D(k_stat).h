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

std::pair<int, std::vector<std::vector<int>>> read() {
	size_t n, k;
	std::cin >> n >> k;
	std::vector < std::vector<int>> res(n, std::vector<int>(2, 0));
	for (int i = 0; i < n; i++) {
		int x,y;
		std::cin >> x >> y;
		res[i][0] = x;
		res[i][1] = y;
	}
	return std::make_pair(k, res);
}

double k_stat(std::vector<double>& distances,const int left, const int right, const int k) {
	int n = right - left;
	if (left == right) {
		return distances[k];
	}
	int piv = left + (n+1) / 2;
	if (distances[piv] < distances[left]) {
		std::swap(distances[piv], distances[left]);
	}
	if (distances[left + n] < distances[left]) {
		std::swap(distances[left], distances[left + n]);
	}
	if (distances[left + n] < distances[piv]) {
		std::swap(distances[piv], distances[left + n]);
	}
	double pivot = distances[piv];
	int pos = left;
	for (int i = left; i <= right; i++) {
		if (distances[i] < pivot) {
			std::swap(distances[pos++], distances[i]);
		}
	}
	int left_eq = std::max(pos - 1,0);
	int right_eq = pos;
	for (int i = left; i <= right; i++) {
		if (distances[i] == pivot && i < pos && left_eq>left ) {
			std::swap(distances[left_eq--], distances[i]);
		}
		if (distances[i] == pivot && i > pos && right_eq < right) {
			std::swap(distances[right_eq++], distances[i]);
		}
	}
	double res = 0;
	if (k == pos || (distances[left] - distances[right]) == 0) {
		return distances[k];
	}
	if (k > right_eq) {
		res = k_stat(distances, right_eq, right, k);
	}
	else {
		res = k_stat(distances, left, left_eq, k);
	}
	return res;
}

//3 3
//0 5
//3 4
//- 4 - 3

void solve(std::pair<int, std::vector<std::vector<int>>> &p) {
	int k = p.first;
	int n = p.second.size();
	std::vector<std::vector<int>> dots = p.second;
	double min_r = 1001;
	// можно сделать при помощи двоичного поиска
	for (int i = -1000; i <= 1000; i++) {
		std::vector<double> distances(n);
		for (int j = 0; j < n; j++) {
			distances[j] = std::sqrt(pow((i - dots[j][0]), 2) + pow(dots[j][1],2));
		}
		double k_s = k_stat(distances, 0, distances.size()-1, k-1);
		min_r = min_r > k_s ? k_s : min_r;
	}
	std::cout << std::fixed << std::setprecision(6) << min_r;
}



void compound() {
	std::pair<int, std::vector<std::vector<int>>> p = read();
	solve(p);
}