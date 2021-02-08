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

	//i in left
	void split(Node* t, int i, Node*& l, Node*& r) {
		if (t == nullptr) {
			l = r = nullptr;
			return;
		}
		if (i >= getSize(t->left) + 1) {
			split(t->right, i - getSize(t->left)-1 , t->right, r);
			l = t;
		}
		else {
			split(t->left, i, l, t->left);
			r = t;
		}
		updateSize(t);
	}

	Node* remove(Node* node, int i) {
		Node* left;
		Node* right;
		Node* new_left;
		Node* new_right;
		split(node, i-1, left, right);
		split(right, 1, new_left, new_right);
		node = merge(left, new_right);
		delete (new_left);
		return node;
	}
	void remove(int i) {
		root = remove(root, i);
	}

	void insert(int i, int val) {
		Node* l, * r;

		split(root, i, l, r);
		root = merge(merge(l, new Node(val)), r);
	}

	void inorder_traverse(std::vector<int>& v) {
		inorder_traverse(root, v);
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

	void inorder_traverse(Node* node, std::vector<int>& v) {
		if (node == nullptr) return;
		if (node->left != nullptr) {
			inorder_traverse(node->left, v);
		}
		v.push_back(node->value);
		if (node->right != nullptr) {
			inorder_traverse(node->right, v);
		}
	}

	Node* root = nullptr;
};

void compound() {
	int n, q;
	std::cin >> n >> q;
	Treap tr;
	for (int i = 0; i < n; i++) {
		int tmp;
		std::cin >> tmp;
		tr.insert(i,tmp);
	}
	for (int i = 0; i < q; i++) {
		std::string s;
		std::cin >> s;
		if (s == "del") {
			int pos;
			std::cin >> pos;
			tr.remove(pos);
		}
		else if (s == "add") {
			int pos, val;
			std::cin >> pos >> val;
			tr.insert(pos, val);
		}
		std::vector<int> ans;
		tr.inorder_traverse(ans);
		std::cout << ans.size() << std::endl;
		for (int i = 0; i < ans.size(); i++) {
			std::cout << ans[i] << " ";
		}
	}
	std::vector<int> ans;
	tr.inorder_traverse(ans);
	std::cout << ans.size() << std::endl;
	for (int i = 0; i < ans.size(); i++) {
		std::cout << ans[i] << " ";
	}
}