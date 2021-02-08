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
	std::list<int> second, first;
	int querries;
	std::string	q;
	std::cin >> querries;
	while (querries > 0) {
		std::cin >> q;
		int id;
		if (q == "+") {
			std::cin >> id;
			second.push_back(id);
		}
		else if (q == "*") {
			std::cin >> id;
			second.push_front(id);
		}
		else if (q == "-") {
			std::cout << first.front() << std::endl;
			first.pop_front();
		}
		if (second.size() > first.size()) {
			int x = second.front();
			first.push_back(x);
			second.pop_front();
		}
		querries--;
	}
}