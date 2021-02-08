#pragma once
#include <iostream>
#include <vector>

const int MOD = 1000000000;

void compound() {
	long long int n;
	std::cin >> n;
	std::vector< std::vector<long long int>> d(n, std::vector< long long int>(10));
	std::vector< std::vector<long long int>> nums = {
		{4,6}, //0
		{6,8}, //1
		{7,9}, //2
		{4,8}, //3
		{0,3,9}, //4
		{}, //5
		{0,1,7}, //6
		{2,6}, //7
		{1,3}, //8
		{2,4}, //9
	};
	for (int i = 0; i < 10; i++) {
		if (i != 0 && i != 8) {
			d[0][i] = 1;
		}
	}
	
	for (int i = 1; i < n; i++) {
		d[i][0] = (d[i - 1][4] + d[i-1][6]) % MOD;
		d[i][1] = (d[i - 1][6] + d[i-1][8]) % MOD;
		d[i][2] = (d[i - 1][7] + d[i-1][9]) % MOD;
		d[i][3] = (d[i - 1][4] + d[i-1][8]) % MOD;
		d[i][4] = (d[i - 1][0] + d[i-1][3] + d[i-1][9]) % MOD;
		d[i][5] = 0;
		d[i][6] = (d[i - 1][0] + d[i - 1][1] + d[i - 1][7]) % MOD;
		d[i][7] = (d[i - 1][2] + d[i-1][6]) % MOD;
		d[i][8] = (d[i - 1][1] + d[i-1][3]) % MOD;
		d[i][9] = (d[i - 1][2] + d[i-1][4]) % MOD;
	}
	long long int ans = 0;
	
	for (int i = 0; i < 10; i++) {
		ans = (ans + d[n - 1][i]) % MOD;
	}
	std::cout << ans << std::endl;
}