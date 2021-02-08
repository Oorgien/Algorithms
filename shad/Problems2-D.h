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

unsigned int cur = 0; // беззнаковое 32-битное число
unsigned int nextRand24(unsigned int a, unsigned int b) {
	cur = cur * a + b; // вычисляется с переполнениями
	return cur>> 8; // число от 0 до 2

}
unsigned int nextRand32(unsigned int a, unsigned int b) {
	unsigned int f = nextRand24(a,b), c = nextRand24(a, b);
	return (f << 8) ^ c; // число от 0 до 2

}

std::vector<unsigned int> read() {
	unsigned int n;
	unsigned int a, b;
	std::vector<unsigned int> res;
	std::cin >> n;
	std::cin >> a >> b;
	for (int i = 0; i < n; i++) {
		unsigned int tmp = nextRand32(a,b);
		res.push_back(tmp);
	}
	return res;
}

void solve(std::vector<unsigned int> &v) {
	std::nth_element(v.begin(), v.begin() + v.size()/2,  v.end());
	int64_t sum = 0;
	for (int i = 0; i < v.size(); i++) {
		int32_t num = v[(v.size() / 2)] - v[i];
		sum += std::abs(num);
	}
	std::cout << sum;
}

void compound() {
	std::vector<unsigned int> v = read();
	solve(v);
}