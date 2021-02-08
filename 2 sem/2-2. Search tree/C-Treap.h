#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <limits>


class Treap {
public:
	int num = 0;
	struct Node {
		Node(int data = 0, bool isSero = true) {
			value = data;
			zero = true;
			size = 1;
			left = right = nullptr;
			p = rand() * rand();
		}
		int value;
		size_t size;
		int p;
		bool zero;
		Node* right, *left;
	};

	Node* searchNull(Node* t, int& ind) {
		Node* cur = t;
		ind = getSize(cur->left);

		while (getZero(cur)) {
			if (cur->left != nullptr && getZero(cur->left)) {
				cur = cur->left;
				ind = ind - getSize(cur->right) - 1;
			}
			else if (getValue(cur) == 0) {
				break;
			}
			else {
				cur = cur->right;
				ind += getSize(cur->left);
				ind++;
			}
		}

		return cur;
	}

	Node* merge(Node* l, Node* r) {
		if (l == nullptr) return r;
		if (r == nullptr) return l;
		if (l->p > r->p) {
			l->right = merge(l->right, r);
			updateSize(l);
			updateZero(l);
			return l;
		}
		else {
			r->left = merge(l, r->left);
			updateSize(r);
			updateZero(r);
			return r;
		}
	}

	void split(Node* t, int key, Node*& l, Node*& r) {
		if (t == nullptr) {
			l = r = nullptr;
			return;
		}
		if (getSize(t->left) < key) {
			split(t->right, key - getSize(t->left) - 1, t->right, r);
			l = t;
		}
		else {
			split(t->left, key, l, t->left);
			r = t;
		}
		updateSize(t);
		updateZero(t);
	}

	Node* remove(Node* r, int key) {
		Node* t1, * t2, * t3;
		split(r, key, t1, t2);
		split(t2, 1, t2, t3);
		r = merge(t1, t3);
		delete (t2);
		return r;
	}


	Node* build(size_t n) {
		for (int i = 0; i < n; i++) {
			root = merge(new Node(0, true), root);
		}
		return root;
	}

	void insert(int ind) {
		Node* l, * r, * z;
		int i;

		split(root, ind, l, r);
		z = searchNull(r, i);
		if (z != nullptr && z->value == 0) {
			r = remove(r, i);
		}

		root = merge(merge(l, new Node(++num, false)), r);
	}

	void inorder_traverse() {
		inorder_traverse(root);
	}
private:
	void updateZero(Node* t) {
		t->zero = getZero(t->left) || getZero(t->right) || (t->value == 0);
	}
	bool getZero(Node* node) {
		return node == nullptr ? false : node->zero;
	}
	
	size_t getSize(Node* node) {
		return node == nullptr ? 0 : node->size;
	}

	void updateSize(Node* node) {
		node->size = getSize(node->left) + getSize(node->right) + 1;
	}

	int getValue(Node* node) {
		return node == nullptr ? -1 : node->value;
	}

	void inorder_traverse(Node* node) {
		if (node->left != nullptr) {
			inorder_traverse(node->left);
		}
		std::cout << node->value << " ";
		if (node->right != nullptr) {
			inorder_traverse(node->right);
		}
	}

	Node* root = nullptr;
	
};

// 5 4
// 3 3 4 1 3

void compound() {
	int n, m;
	std::cin >> n >> m;

	Treap tree;
	tree.build(m);

	for (int i = 0; i < n; ++i) {
		int j;
		std::cin >> j;
		tree.insert(j-1);
	}

	tree.inorder_traverse();
}