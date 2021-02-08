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

struct Node {
	int value;
	int parent;
	int min;
	int max;
	int size;
};

Node get(std::vector<Node> &Union, int el) {
	if (Union[el].parent != el)
		return Union[el] = get(Union, Union[el].parent);
	// return parent of value
	return Union[el];
}

void join(std::vector<Node> &Union, int el1, int el2) {
	Node x = get(Union, el1);
	Node y = get(Union, el2);
	if (x.value == y.value)
		return;
	int min = std::min(x.min, y.min);
	int max = std::max(x.max, y.max);
	int size = x.size + y.size;
	if (x.size <= y.size) {
		Node tmp = {y.value, y.parent, min, max, size };
		Union[x.value].parent = tmp.value;
		Union[y.value] = tmp;
	}
	else {
		Node tmp = {x.value, x.parent, min, max, size };
		Union[x.value] = tmp;
		Union[y.value].parent = tmp.value;
	}
}

void compound() {
	int n;
	std::cin >> n;
	std::vector<Node> Union(n + 1);//pos - element, value - parent
	for (int i = 1; i <= n; i++) {
		Node tmp = {i, i, i, i, 1};
		Union[i] = tmp;
	}

	std::string s;
	while (std::cin >> s) {
		if (s == "union") {
			int el1, el2;
			std::cin >> el1 >> el2;
			join(Union, el1, el2);
		}
		else if (s == "get") {
			int el;
			std::cin >> el;
			Node parent = get(Union, el);
			std::cout << parent.min << " " << parent.max << " " << parent.size << std::endl;
		}
	}

}