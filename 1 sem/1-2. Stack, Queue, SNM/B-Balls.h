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

/// <summary>
/// 10 3 4 5 5 4 4 4 1 3 3
/// 10 1 4 5 5 4 4 4 1 1 3
/// </summary>

void compound() {
	size_t n;
	std::cin >> n;
	std::vector<int> a(n);
	std::vector<int> size(n);

	int last = -1;
	int cnt = 0;
	int res = 0;

	for (int i = 0; i < n; i++) {
		int x;
		std::cin >> x;
		if (x == last) {
			res++;
		}
		else if (cnt && a[cnt - 1]==x) {
			if (size[cnt - 1] == 2) {
				cnt--;
				res += 3;
				last = x;
			}
			else {
				last = -1;
				size[cnt - 1]++;
			}
		}
		else {
			last = -1;
			a[cnt] = x;
			size[cnt++]=1;
			
		}
	}
	std::cout << res;
}