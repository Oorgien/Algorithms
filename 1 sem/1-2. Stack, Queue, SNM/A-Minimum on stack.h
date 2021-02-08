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

class MinStack {
public:
	void add(int& el) {
		s.push(s.empty() ? el : std::min(el, s.top()));
	}
	void del() {
		s.pop();
	}
	int show_min() {
		return s.top();
	}
private:
	std::stack<int> s;
	int min;
};

void compound() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	MinStack s;
	int q;
	std::cin >> q;
	while (q > 0) {
		int op;
		std::cin >> op;
		if (op == 1) {
			int tmp;
			std::cin >> tmp;
			s.add(tmp);
		}
		else if (op == 2) {
			s.del();
		}
		else if (op == 3) {
			std::cout << s.show_min() << std::endl;
		}
		q--;
	}


}