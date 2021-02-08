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
	int n, k;
	std::cin >> n >> k;
	std::vector<int> coins(n);
	std::vector<int> d(n);//coins for i-th state
	std::vector<int> p(n); //previous state

	for (int i = 1; i < n-1; i++) {
		std::cin >> coins[i];
	}

	int max_id = 0;
	for (int i = 1; i < n; i++) {
		if (max_id < i - k || d[i - 1] > d[max_id]) {
			max_id = i - 1;
			for (int j = i - 1; j >= i - k; j--) {
				if (j >= 1 && d[j] >= d[max_id]) {
					max_id = j;
				}
			}
		}
		d[i] = d[max_id] + coins[i];
		p[i] = max_id;
	}

	std::cout << d[n - 1] << std::endl;
	int it = n-1;
	std::vector<int> ans;
	while (it != 0) {
		ans.push_back(it);
		it = p[it];
	}
	std::cout << ans.size() << std::endl;
	ans.push_back(0);
	for (int i = ans.size()-1; i >= 0 ; i--) {
		std::cout << ans[i]+1 << " ";
	}
}

//10 5
//-1 -2 -6 -2 -10 8 1 -3