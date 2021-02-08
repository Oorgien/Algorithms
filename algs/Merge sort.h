#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <deque>

std::vector<int> read() {
    std::vector<int> arr;
    while (std::cin.peek() != '\n'){
        int val = 0;
        std::cin >> val;
        arr.push_back(val);
    }
    return arr;
}

void merge_sort(std::vector<int> &arr,const int size) {
    if (size > 1) {
        int L = 0, R = 0;
        int s = size - size / 2;
        std::vector<int> left = { arr.begin(), arr.begin() + s };
        std::vector<int> right = { arr.begin() + s , arr.end() };
        merge_sort(left, left.size());
        merge_sort(right, right.size());

        std::vector<int> tmp(size);
        int k = 0;
        while (L != s || R != s) {
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
        arr = tmp;
    }
}

void show(std::vector<int> res) {
    for (auto item : res) {
        std::cout << item << " ";
    }
}

void compound() {
    std::vector<int> input = read();
    merge_sort(input, input.size());
    show(input);
}