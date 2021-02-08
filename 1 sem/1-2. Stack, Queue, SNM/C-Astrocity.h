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

void compound() {
	int querries, q;
	std::vector<int> Q((10e+5) + 1);
	std::vector<int> ids_to_positions((10e+5)+1);
	std::cin >> querries;
	int head=0, tail = 0;
	while (querries > 0) {
		std::cin >> q;
		if (q == 1) {
			int id;
			std::cin >> id;
			Q[tail] = id;
			ids_to_positions[id] = tail;
			tail++;
		}
		else if (q == 2) {
			Q[head] = 0;
			head++;
		}
		else if (q == 3) {
			Q[tail] = 0;
			tail--;
		}
		else if (q == 4) {
			int id;
			std::cin >> id;
			std::cout << ids_to_positions[id]-head << std::endl;
		}
		else if (q == 5) {
			std::cout << Q[head] << std::endl;
		}
		querries--;
	}
}