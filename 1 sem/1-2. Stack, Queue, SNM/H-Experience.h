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
	int exp;
	int parent;
	int rank;
};

int get(std::vector<Node>& Union, int el) {
	if (Union[el].parent != el)
		return el = get(Union, Union[el].parent);
	// return parent of value
	return el;
}

int get_exp(std::vector<Node>& Union, int el) {
	if (Union[el].parent != el)
		return Union[el].exp + get_exp(Union, Union[el].parent);
	// return parent of value
	return Union[el].exp;
}

void join(std::vector<Node>& Union, int el1, int el2) {
	int x = get(Union, el1);
	int y = get(Union, el2);
	if (x == y)
		return;
	// подвешиваем x -> y
	if (Union[x].rank > Union[y].rank) {
		std::swap(x, y);
	}
	int rank = std::max(Union[x].rank + 1, Union[y].rank);
	//int exp = Union[x].exp + Union[y].exp;
	Union[x].parent = y;
	Union[x].exp -= Union[y].exp;
	Union[y].rank = rank;
}

void add(std::vector<Node>& Union, int el, int exp) {
	int parent = get(Union, el);
	Union[parent].exp += exp;
}
void compound() {
	int n, m;
	std::cin >> n >> m;
	std::vector<Node> Union(n + 1);//pos - element, value - parent
	for (int i = 1; i <= n; i++) {
		Node tmp = { 0, i, 0 };
		Union[i] = tmp;
	}

	std::string s;
	for (int i = 0; i < m; i++) {
		std::cin >> s;
		if (s == "join") {
			int el1, el2;
			std::cin >> el1 >> el2;
			join(Union, el1, el2);
		}
		else if (s == "get") {
			int el;
			std::cin >> el;
			int exp = get_exp(Union, el);
			std::cout << exp << std::endl;
		}
		else if (s == "add") {
			int el, exp;
			std::cin >> el >> exp;
			add(Union, el, exp);
		}
	}

}