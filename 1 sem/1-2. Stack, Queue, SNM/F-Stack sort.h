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
#include <numeric> 
#include <queue>
#include <list>

void compound() {
	int n;
	std::cin >> n;
	std::stack<int> s;
	std::vector<int> v(n);
	std::vector<std::string> words;

	for (int i = 0; i < n; i++) {
		std::cin >> v[i];
	}
	int last = 0;
	for (int i = 0; i < n; i++) {
		if (s.empty() || (v[i] < s.top() && last < v[i])) {
			s.push(v[i]);
			words.push_back("push");
		}
		else if (v[i] < last && v[i] < s.top()) {
			std::cout << "impossible" << std::endl;
			return;
		}

		else if (v[i] > s.top()) {
			while (!s.empty() && v[i] > s.top()) {
				last = s.top();
				s.pop();
				words.push_back("pop");
			}
			s.push(v[i]);
			words.push_back("push");
		}
		if (i == n - 1 && !s.empty()) {
			while (!s.empty()) {
				s.pop();
				words.push_back("pop");
			}
		}
	}
	
	for (auto word : words) {
		std::cout << word << std::endl;
	}
}