#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <limits>

size_t binary_search_l(std::vector<int>& v, int& el) {
	int L=0, R=v.size();
	int m = std::floor((L + R) / 2.0);
	while ( L < R) {
		m = std::floor((L + R) / 2.0);
		if (v[m] < el) {
			L = m + 1;
			
		}
		else R = m;
	}
	return L;
}

size_t binary_search_r(std::vector<int>& v, int& el) {
	int L = 0, R = v.size();
	int m = std::floor((L + R) / 2.0);
	while ( L < R) {
		m = std::floor((L + R) / 2.0);
		if (v[m] > el) {
			R = m;
		}
		else L = m + 1;
	}
	return R-1;
}

int binary_search_more(std::vector<int>& v, int& el) {
	int n = v.size() - 1;
	int L = 0, R = v.size() - 1;
	int ind = std::floor((L + R) / 2.0);
	while (L <= R) {
		ind = std::floor((L + R) / 2.0);
		if (v[ind] > el) {
			R = ind - 1;
		}
		else if (v[ind] < el) { 
			L = ind + 1; 
		}
		else return ind;
	}
	return ind;
}

int solve(std::vector<int>& v, int& L, int& R) {
	int n = v.size();
	int l_ind = binary_search_l(v, L);
	int r_ind = binary_search_r(v, R);

	return r_ind - l_ind + 1;
}


/*
10
1 7 6 9 7 0 14 5 7 2
10
1 14
*/

/*
5
10 1 10 3 4
4
1 10
2 9
3 4
2 2
*/

void compound() {
	int n, k;
	std::vector<int> v;
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		int tmp;
		std::cin >> tmp;
		v.push_back(tmp);
	}
	std::cin >> k;
	std::sort(v.begin(), v.end());
	for (int i = 0; i < k; i++) {
		int L, R;
		std::cin >> L >> R;

		std:: cout << solve(v, L, R) << " ";
	}
}