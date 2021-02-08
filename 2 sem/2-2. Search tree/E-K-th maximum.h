#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

class Treap {
public:
	int num = 0;
	struct Node {
		Node(int data = 0) {
			value = data;
			size = 1;
			left = right = nullptr;
			p = rand() * rand();
		}
		int value;
		size_t size;
		int p;
		Node* right, * left;
	};


	Node* merge(Node* l, Node* r) {
		if (l == nullptr) return r;
		if (r == nullptr) return l;
		if (l->p > r->p) {
			l->right = merge(l->right, r);
			updateSize(l);
			return l;
		}
		else {
			r->left = merge(l, r->left);
			updateSize(r);
			return r;
		}
	}

	void split(Node* t, int key, Node*& l, Node*& r) {
		if (t == nullptr) {
			l = r = nullptr;
			return;
		}
		if (key >= getValue(t)) {
			split(t->right, key, t->right, r);
			l = t;
		}
		else {
			split(t->left, key, l, t->left);
			r = t;
		}
		updateSize(t);
	}

	Node* remove(Node* node, int key) {
		Node* left;
		Node* right;
		Node* new_left;
		Node* new_right;
		split(node, key, left, right);
		split(left, key-1, new_left, new_right);
		node = merge(new_left, right);
		delete (new_right);
		return node;
	}
	void remove(int key) {
		root = remove(root, key);
	}
	
	void insert(int key) {
		Node* l, * r;

		split(root, key, l, r);
		root = merge(merge(l, new Node(key)), r);
	}

	Node* k_th_max(Node* node, int k) {
		if (getSize(node->left) == k) {
			return node;
		}
		if (getSize(node->left) < k) {
			return k_th_max(node->right, k - getSize(node->left)-1);
		}
		else {
			return k_th_max(node->left, k);
		}
	}

	int k_th_max(int k) {
		return getValue(k_th_max(root, getSize(root) - k));
	}

	void inorder_traverse() {
		inorder_traverse(root);
	}

	Node*& get_root() {
		return root;
	}
private:
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

void compound() {
	int q;
	std::string s;
	std::cin >> q;
	Treap tr;
	for (int i = 0; i < q; i++) {
		std::cin >> s;
		if (s == "+1") {
			int key, met = 0;
			std::cin >> key;
			tr.insert(key);
		}
		else if (s == "0") {
			int k;
			std::cin >> k;
			std::cout << tr.k_th_max(k) << std::endl;
		}
		else if (s == "-1") {
			int key;
			std::cin >> key;
			tr.remove(key);
		}
	}
}