#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int maxPair(const std::vector<int>& increasing,
	const std::vector<int>& decreasing, int pos) {
	return std::max(increasing[pos], decreasing[pos]);
}

int solution(const std::vector<int>& increasing,
	const std::vector<int>& decreasing, int length) {
	int leftBorder = 0;
	int rightBorder = length - 1;

	while (leftBorder <= rightBorder) {
		int med = std::floor((leftBorder + rightBorder) / 2.0);
		if (increasing[med] - decreasing[med] > 0) {
			rightBorder = med - 1;
		}
		else {
			leftBorder = med + 1;
		}
	}
	int ans = 0;
	if (rightBorder + 1 == length)
		ans = rightBorder;
	else
		ans = rightBorder + 1;
	if (ans == 0)
		return 1;
	if (maxPair(increasing, decreasing, ans) >
		maxPair(increasing, decreasing, ans - 1)) {
		return ans;
	}
	return ans + 1;
}

void compound() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int number, anotherNumber, length, queries;
	std::cin >> number >> anotherNumber >> length;
	std::vector < std::vector < int  >>   firstArray(number);
	for (int i = 0; i < number; ++i) {
		firstArray[i].resize(length);
		for (int j = 0; j < length; ++j) {
			std::cin >> firstArray[i][j];
			if (std::cin.peek() == '\n') {
				break;
			}
		}
	}
	std::vector < std::vector < int >>  secondArray(anotherNumber);
	for (int i = 0; i < anotherNumber; ++i) {
		secondArray[i].resize(length);
		for (int j = 0; j < length; ++j) {
			std::cin >> secondArray[i][j];
			if (std::cin.peek() == '\n') {
				break;
			}
		}
	}

	std::cin >> queries;
	int indexerFirst, indexerSecond;
	std::vector<int> answers(queries);
	for (int z = 0; z < queries; ++z) {
		std::cin >> indexerFirst >> indexerSecond;
		answers[z] = solution(firstArray[indexerFirst - 1],
			secondArray[indexerSecond - 1], length);
	}
	for (const auto& element : answers) {
		std::cout << element << " ";
	}
	std::cout << std::endl;
}