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


std::pair<std::vector<std::vector<int>>, int> read() {
	int m,n;
	std::cin >> m >> n;
	std::vector<std::vector<int>> res(m, std::vector<int>(n));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int tmp;
			std::cin >> tmp;
			res[i][j] = tmp;
		}
	}
	return std::make_pair(res, n);
}

//4 2
//1 4
//2 8
//3 7
//5 6

//3 3
//1 4 8 
//2 5 9
//3 6 10
//

std::vector<int> solve(int left_m, int right_m, std::vector<std::vector<int>>& v, int n) {
    
    if (right_m - left_m != 0) {
        std::vector<int> left = solve(left_m, left_m + (right_m - left_m) / 2, v, n);
        std::vector<int> right = solve(right_m - (right_m - left_m) / 2, right_m, v, n);

        std::vector<int> tmp(left.size() + right.size());
        int k = 0;
        int L = 0, R = 0;
        while (L != n || R != n) {
            if (left[L] < right[R]) {
                tmp[k++] = left[L];
                L++;
            }
            else {
                tmp[k++] = right[R];
                R++;
            }
            if (L == left.size()) {
                std::copy(right.begin() + R, right.end(), tmp.begin() + k);
                break;
            }
            if (R == right.size()) {
                std::copy(left.begin() + L, left.end(), tmp.begin() + k);
                break;
            }
        }
        return tmp;
    }
    else {
        //std::vector<int> tmp(n * 2);
        //int k = 0;
        //int L = 0, R = 0;
        //while (L != n || R != n) {
        //    if (v[left_m][L] < v[right_m][R]) {
        //        tmp[k++] = v[left_m][L];
        //        L++;
        //    }
        //    else {
        //        tmp[k++] = v[right_m][R];
        //        R++;
        //    }
        //    if (L == n) {
        //        std::copy(v[right_m].begin() + R, v[right_m].end(), tmp.begin() + k);
        //        break;
        //    }
        //    if (R == n) {
        //        std::copy(v[left_m].begin() + L, v[left_m].end(), tmp.begin() + k);
        //        break;
        //    }
        //}
        return v[left_m];
    }
}

void compound() {
    std::pair<std::vector<std::vector<int>>, int> p = read();
    if ((p.first.size() - 1) % 2 == 0 && p.first.size() > 1) {
        p.first[p.first.size() - 2] = solve(p.first.size()-2, p.first.size()-1, p.first, p.second);
        p.first.erase(p.first.end() - 1);
    }

    std::vector<int> res = solve(0, p.first.size()-1, p.first, p.second);
    
    for (auto& item : res) {
        std::cout << item << " ";
    }
}