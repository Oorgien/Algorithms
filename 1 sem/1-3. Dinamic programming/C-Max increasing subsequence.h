#pragma once
#include <iostream>
#include <vector>
#include <set>

int n, mode = 2;
std::vector<int> seq;
std::vector<int> d;
std::vector<int> prev;

void print(int i, std::vector<int> prev, std::vector<int> seq) {
	std::vector<int> ans;
	//pos.push_back(i);
	while (i != prev[i]) {
		ans.push_back(seq[i]);
		i = prev[i];
	}
	ans.push_back(seq[i]);
	std::cout << ans.size() << "\n";
	for (int j = ans.size() - 1; j >= 0; j--) {
		std::cout << ans[j] << " ";
	}
}

void solve(std::vector<int> prev, std::vector<int> d, std::vector<int> seq) {
	int max_id=0;
	for (int i = 0; i < n; i++) {
		int index = i;
		for (int j = 0; j < i; j++) {
			if ((seq[j] < seq[i]) && (d[j] + 1 > d[i])) {
				d[i] = d[j] + 1;
				index = j;
			}
			prev[i] = index;
			if (d[i] > d[max_id]) {
				max_id = i;
			}
		}
	}
	print(max_id, prev, seq);
}

//10
//1 -6 7 -10 5 -5 4 1 0 -8 
void compound() {
	std::cin >> n;
	seq.resize(n);
	d.resize(n, 1);
	prev.resize(n);

	for (int i = 0; i < n; i++) {
		std::cin >> seq[i];
	}
	solve(prev, d, seq);
}