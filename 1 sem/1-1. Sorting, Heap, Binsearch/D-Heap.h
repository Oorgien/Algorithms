#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

void sift_up(std::vector<int>& a, int& el) {
	a.push_back(el);
	int n = a.size();
	size_t i = n-1;
	while (i > 0 && a[i] > a[(i - 1) / 2]) {
		std::swap(a[i], a[(i - 1 )/ 2]);
		i = (i - 1) / 2;
	}
}

void sift_down(std::vector<int>& a, int& i) {
	bool flag = true;
	int j = i;
	while (flag) {
		if (2 * i + 1 < a.size() && a[2 * i + 1] > a[j]) {
			j = 2 * i + 1;
		}
		if (2 * i + 2 < a.size() && a[2 * i + 2] > a[j]) {
			j = 2 * i + 2;
		}
		if (i == j) flag = false;
		std::swap(a[i], a[j]);
		i = j;
	}
}

int remove(std::vector<int>& a) {
	int max = a[0];
	std::swap(a[a.size() - 1], a[0]);
	a.erase(a.end() - 1);
	int i = 0;
	sift_down(a, i);
	return max;
}

void insert(std::vector<int>& a, int& el) {
	sift_up(a, el);
}

void compound() {
	int n = 0;
	std::cin >> n;
	std::vector<int> a;
	for (int i = 0; i < n; i++) {
		int q, el;
		std::cin >> q;
		if (q == 0) {
			std::cin >> el;
			insert(a, el);
		}
		else if (q == 1) {
			std::cout << remove(a) << std::endl;
		}
	}
}