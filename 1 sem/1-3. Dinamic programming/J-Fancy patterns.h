#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <unordered_set>

using namespace std;

void compound() {
	int n, m;
	cin >> n >> m;
	if (n > m) {
		swap(n, m);
	}
	vector<unordered_set<int>> vec(1 << n);
	vector<vector<int>> dp(2);
	// m always > n
	for (int x = 0; x < (1 << n); x++) {
		for (int y = x; y < (1 << n); y++) {
			bool flag = true;
			for (int j = 0; j < n - 1; j++)
				if ((x >> j & 1) == (y >> j & 1)
					&& (y >> j & 1) == (x >> (j + 1) & 1)
					&& (x >> (j + 1) & 1) == (y >> (j + 1) & 1))
				{
					flag = false;
					break;
				}
			if (flag) {
				vec[x].insert(y);
				vec[y].insert(x);
			}
		}
	}

	for (int x = 0; x < 1 << n; x++)
	{
		dp[0].push_back(1);
		dp[1].push_back(0);
	}

	for (int i = 1; i < m; i++) {
		for (int x = 0; x < (1 << n); x++) {
			// перебираем все состояния, в которые можно перейти из x
			for (int y : vec[x]) {
				dp[1][x] += dp[0][y];
			}
		}
		dp[0] = dp[1];
		for (int x = 0; x < (1 << n); x++) {
			dp[1][x] = 0;
		}
	}

	long long res = 0;
	for (int i = 0; i < 1 << n; i++) {
		res += dp[0][i];
	}
	cout << res;

}