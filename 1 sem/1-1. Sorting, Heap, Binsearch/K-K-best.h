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

std::vector<size_t> sort_indexes(const std::vector<double>& v) {

	// initialize original index locations
	std::vector<size_t> idx(v.size());
	std::iota(idx.begin(), idx.end(), 0);

	// sort indexes based on comparing values in v
	// using std::stable_sort instead of std::sort
	// to avoid unnecessary index re-orderings
	// when v contains elements of equal values 
	std::stable_sort(idx.begin(), idx.end(),
		[&v](size_t i1, size_t i2) {return v[i1] > v[i2]; });

	return idx;
}

std::vector<double> value, weight;
int n, k;

double const EPS = 10e-5;

double f(double m) {
	double res=0;
	std::vector<double> a(n);
	for (int i = 0; i < value.size(); i++) {
		a[i] += value[i] - m * weight[i];
	}
	std::stable_sort(a.begin(), a.end(), std::greater<double>());
	for (int i = 0; i < k; i++) {
		res += a[i];
	}
	return res;
}



void compound() {

	std::cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int v, w;
		std::cin >> v >> w;
		value.push_back(v);
		weight.push_back(w);
	}
	double l = -1;
	double r = 0;
	for (int i = 0; i < n; i++) {
		r = std::max(r, (double) value[i] / weight[i]);
	}
	r += 1;
	double m;
	while (r - l > EPS) {
		m = (r + l) / 2;
		if (f(m) > 0)
			l = m;
		else
			r = m;
	}
	std::vector<double> a(n), b(n);
	for (int i = 0; i < n; i++) {
		a[i]= b[i] = value[i] - r * weight[i];
 	}

	//std::stable_sort(b.begin(), b.end(), std::greater<double>());
	std::vector<size_t> indexes = sort_indexes(b);
	for (int i = 0; i < k; i++) {
		std::cout << indexes[i] + 1 << '\n';
	}
}