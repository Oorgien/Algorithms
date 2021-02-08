#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <limits>
#include <cmath>

class tree {
public:
	struct Node {

		long long value = 0;
		Node* left = nullptr;
		Node* right = nullptr;
		long long sum = 0;
		long long min = 0;
		long long max = 0;
		int height = 0;
	};

	long long Get_sum(Node* node) {
		return node == nullptr ? 0 : node->sum;
	}
	long long Get_min(Node* node) {
		return node == nullptr ? std::numeric_limits<int>::max() : node->min;
	}
	long long Get_max(Node* node) {
		return node == nullptr ? std::numeric_limits<int>::min() : node->max;
	}

	int height(Node* node) {
		return node == nullptr ? -1 : node->height;
	}

	Node* SingleLeftRotate(Node* a) {
		Node* b = a->right;
		Node* c = b->left;
		b->left = a;
		a->right = c;

		a->height = std::max(height(c), height(a->left)) + 1;
		b->height = std::max(height(b->right), height(a)) + 1;

		a->max = std::max(a->value,
			std::max(Get_max(c), Get_max(a->left)));
		a->min = std::min(a->value,
			std::min(Get_min(c), Get_min(a->left)));

		b->max = std::max(b->value,
			std::max(Get_max(b->right), Get_max(a)));
		b->max = std::min(b->value,
			std::min(Get_min(b->right), Get_min(a)));
		a->sum = Recalc_Sum(a);
		b->sum = Recalc_Sum(b);
		return b;
	}

	Node* SingleRightRotate(Node* a) {
		Node* b = a->left;
		Node* c = b->right;
		b->right = a;
		a->left = c;

		a->height = std::max(height(c), height(a->right)) + 1;
		b->height = std::max(height(b->left), height(a)) + 1;

		a->max = std::max(a->value,
			std::max(Get_max(c), Get_max(a->right)));
		a->min = std::min(a->value,
			std::min(Get_min(c), Get_min(a->right)));

		b->max = std::max(b->value,
			std::max(Get_max(b->left), Get_max(a)));
		b->min = std::min(b->value,
			std::min(Get_min(b->left), Get_min(a)));
		a->sum = Recalc_Sum(a);
		b->sum = Recalc_Sum(b);
		return b;
	}

	Node* DoubleRightRotate(Node* a) {
		a->left = SingleLeftRotate(a->left);
		return SingleRightRotate(a);
	}

	Node* DoubleLeftRotate(Node* a) {
		a->right = SingleRightRotate(a->right);
		return SingleLeftRotate(a);
	}

	Node* insert(long long key, Node* node) {
		if (node == nullptr) {
			node = new Node;
			node->value = key;
			node->left = nullptr;
			node->right = nullptr;
			node->sum = key;
			node->min = key;
			node->max = key;
		}
		else if (key < node->value) {
			node->left = insert(key, node->left);

			if (height(node->left) - height(node->right) == 2) {
				if (height(node->left->right) <= height(node->left->left)) {
					node = SingleRightRotate(node);
				}
				else {
					node = DoubleRightRotate(node);
				}
			}
			node->sum = Recalc_Sum(node);
			//node->min = Min(node);
			//node->max = Max(node);
			node->height = std::max(height(node->left), height(node->right)) + 1;
			node->max = std::max(node->value,
				std::max(Get_max(node->left), Get_max(node->right)));
			node->min = std::min(node->value,
				std::min(Get_min(node->left), Get_min(node->right)));

		}
		else if (key > node->value) {
			node->right = insert(key, node->right);


			if (height(node->right) - height(node->left) == 2) {
				if (height(node->right->left) <= height(node->right->right)) {
					node = SingleLeftRotate(node);
				}
				else {
					node = DoubleLeftRotate(node);
				}
			}
			node->sum = Recalc_Sum(node);
			//node->min = Min(node);
			//node->max = Max(node);
			node->height = std::max(height(node->left), height(node->right)) + 1;
			node->max = std::max(node->value,
				std::max(Get_max(node->left), Get_max(node->right)));
			node->min = std::min(node->value,
				std::min(Get_min(node->left), Get_min(node->right)));
		}
		
		return node;
	}
	/*
	Node* insert(long long key, Node* node) {
		if (node == nullptr) {
			node = new Node;
			node->value = key;
			node->left = nullptr;
			node->right = nullptr;
			node->sum = key;
			node->min = key;
			node->max = key;
		}
		else if (key < node->value) {
			node->left = insert(key, node->left);
			node->sum = Recalc_Sum(node);
			node->min = Min(node);
			node->max = Max(node);
		}
		else if (key > node->value) {
			node->right = insert(key, node->right);
			node->sum = Recalc_Sum(node);
			node->min = Min(node);
			node->max = Max(node);
			
		}
		return node;
	}
	*/
	//sum in the subtree
	long long Recalc_Sum(Node* node) {
		if (node == nullptr) return 0;
		else {
			return  Get_sum(node->left) + Get_sum(node->right) + node->value;
		}
	}

	long long Min(Node* node) {
		if (node == nullptr) return std::numeric_limits<long long>::max();
		else {
			return std::min(Get_min(node->left), std::min(Get_min(node->left), node->value));
		}
	}

	long long Max(Node* node) {
		if (node == nullptr) return std::numeric_limits<long long>::min();
		else {
			return std::max(Get_max(node->right), std::max(Get_max(node->left), node->value));
		}
	}

	long long Sum(Node* node, long long& l, long long& r) {
		if (node == nullptr) return 0;
		else if (node->min >= l && node->max <= r) return node->sum;
		else if (node->value < l) return Sum(node->right, l, r);
		else if (node->value > r) return Sum(node->left, l, r);
		else return Sum(node->left, l, r) + Sum(node->right, l, r) + node->value;
	}

	Node* get_root() {
		return root;
	}
private:
	Node* root = nullptr;
};

void compound() {
	std::string oper;
	std::string prev = "";
	long long y = 0;
	long long q;
	std::cin >> q;
	tree tr;
	tree::Node* root = tr.get_root();
	for (int i = 0; i < q; i++) {
		std::cin >> oper;
		if (oper == "+") {
			long long tmp;
			std::cin >> tmp;
			if (prev == "" || prev != "?") {
				root = tr.insert(tmp, root);
			}
			else {
				long long p = 1'000'000'000;
				root = tr.insert((tmp + y) % p, root);
			}
		}
		else {
			long long l, r;
			std::cin >> l >> r;
			y = tr.Sum(root, l, r);
			std::cout << y << std::endl;
		}
		prev = oper;
	}
}

