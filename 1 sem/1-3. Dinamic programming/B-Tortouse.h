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
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int>> coins(n, std::vector<int>(m)), d(n, std::vector<int>(m));;
	std::vector<std::vector<char>> actions(n, std::vector<char>(m));

	for (int i = 0; i < n; i++) 
		for (int j = 0; j < m; j++) 
			std::cin >> coins[i][j];
	d[0][0] = coins[0][0];
	for (int i = 1; i < n; i++)
	{
		d[i][0] = d[i - 1][0] + coins[i][0];
		actions[i][0] = 'D';
	}
	for (int i = 1; i < m; i++)
	{
		d[0][i] = d[0][i - 1] + coins[0][i];
		actions[0][i] = 'R';
	}

	
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			//if (i - 1 >= 0 && j - 1 >= 0) {
				if (coins[i - 1][j] > coins[i][j - 1]) {
					d[i][j] = d[i - 1][j] + coins[i][j];
					actions[i][j] = 'D';
				}
				else  {
					d[i][j] = d[i][j - 1] + coins[i][j];
					actions[i][j] = 'R';
				}
			//}
			/*else {
				if (i - 1 >= 0 && j - 1 < 0) {
					d[i][j] = d[i - 1][j] + coins[i][j];
					actions[i][j] = "D";
				}
				else if (j - 1 >= 0 && i - 1 < 0) {
					d[i][j] = d[i][j - 1] + coins[i][j];
					actions[i][j] = "R";
				}
			}*/
		}
	}

	std::cout << d[n - 1][m - 1] << std::endl;
	int i = n - 1, j = m-1;

	std::vector<char> res;
	while (i > 0 || j > 0) {
		res.push_back(actions[i][j]);
		if (actions[i][j] == 'D') {
			i--;
		}
		else {
			j--;
		}
	}
	for (int k = res.size()-1; k >= 0; k--) {
		std::cout << res[k];
	}
}