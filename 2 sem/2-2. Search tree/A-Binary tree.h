#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <limits>

template <typename T>
class tree {
public:
	struct Node {

		T value = 0;
		Node *left = NULL;
		Node *right = NULL;
	};

	tree();
	void insert(T key); //добавить в дерево ключ x. Если ключ x есть в дереве, то ничего делать не надо;
	void del(T key); //удалить из дерева ключ x. Если ключа x в дереве нет, то ничего делать не надо;
	Node* exists(T key); //если ключ x есть в дереве выведите «true», если нет «false»;
	T more(T key); // выведите минимальный элемент в дереве, строго больший x, или «none» если такого нет;
	T less(T key); // выведите максимальный элемент в дереве, строго меньший x, или «none» если такого нет.
	Node* next(T key);
	Node* prev(T key);
	void inorder_traverse();

private:
	void insert(T key, Node *node);
	Node* del(T key, Node* node);
	Node* exists(T key, Node *node);
	void more(Node *node, T key, T& val);
	void less(Node *node, T key, T& val);
	Node* next(Node* node);
	Node* prev(Node* node);
	Node* go_to_left(Node* node);
	Node* go_to_right(Node* node);
	void inorder_traverse(Node *node);
	Node *root; //root - указатель
};

template <class T>
tree<T>::tree() {
	root = NULL;
}

template <class T>
void tree<T>::inorder_traverse(Node *node) {
	if (node->left != NULL) {
		inorder_traverse(node->left);
	}
	std::cout << node->value << " ";
	if (node->right != NULL) {
		inorder_traverse(node->right);
	}
}

template <class T>
void tree<T>::inorder_traverse() {
	inorder_traverse(root);
}

template <class T>
void tree<T>::insert(T key) {
	if (root == NULL) {
		root = new Node;
		root->value = key;
	}
	else {
		insert(key, root);
	}
}

template <class T>
void tree<T>::insert(T key, Node *node) {
	if (key < node->value) {
		if (node->left == NULL) {
			node->left = new Node;
			node->left->value = key;
			node->left->left = NULL;
			node->left->right = NULL;
		}
		else {
			insert(key, node->left);
		}
	}
	else if (key > node->value) {
		if (node->right == NULL) {
			node->right = new Node;
			node->right->value = key;
			node->right->left = NULL;
			node->right->right = NULL;
		}
		else {
			insert(key, node->right);
		}
	}
}

template <class T>
typename tree<T>::Node* tree<T>::exists(T key) { 
	if (root == NULL) {
		return NULL;
	}
	else if (root->value == key) {
		return root;
	}
	else {
		exists(key, root);
	}
}

template <class T>
typename tree<T>::Node* tree<T>::exists(T key, Node *node) {
	if (key == node->value) {
		return node;
	}
	else if (key > node->value) {
		if (node->right != NULL) {
			exists(key, node->right);
		}
		else {
			return NULL;
		}
	}
	else if (key < node->value) {
		if (node->left != NULL) {
			exists(key, node->left);
		}
		else {
			return NULL;
		}
	}
}

template <class T>
typename tree<T>::Node* tree<T>::go_to_left(Node* node) {
	if (node->left != NULL) {
		go_to_left(node->left);
	}
	else {
		return node;
	}
}

template <class T>
typename tree<T>::Node* tree<T>::go_to_right(Node* node) {
	if (node->right != NULL) {
		go_to_right(node->right);
	}
	else {
		return node;
	}
}

template <class T>
typename tree<T>::Node* tree<T>::next(Node* node) {
	if (node != NULL) {
		if (node->right != NULL) {
			Node* right_node = node->right;
			if (node->left != NULL) {
				return go_to_left(right_node);
			}
			else {
				return right_node;
			}
		}
		else {
			return NULL;
		}
	}
}

template <class T>
typename tree<T>::Node* tree<T>::next(T key) {
	Node* node = exists(key);
	if (node != NULL) {
		return next(node);
	}
	else {
		return NULL;
	}
}

template <class T>
typename tree<T>::Node* tree<T>::prev(Node* node) {
	if (node->left != NULL) {
		Node* left_node = node->left;
		if (node->left != NULL) {
			return go_to_right(left_node);
		}
		else {
			return left_node;
		}
	}
	else {
		return NULL;
	}
}

template <class T>
typename tree<T>::Node* tree<T>::prev(T key) {
	Node* node = exists(key);
	if (node != NULL) {
		return prev(node);
	}
	else {
		return NULL;
	}
}

template <class T>
void tree<T>::less(Node *node, T key, T& val) {
	if (node != NULL) {

		less(node->left, key, val);
		if (node->value > val && node->value < key) {
			val = node->value;
		}
		less(node->right, key, val);
	}
}

template <class T>
T tree<T>::less(T key) {
	T val = std::numeric_limits<T>::min();
	less(root, key, val);
	return val;
}

template <class T>
void tree<T>::more(Node *node, T key, T& val) {
	if (node != NULL) {
		more(node->left, key, val);
		if (node->value < val && node->value > key) {
			val = node->value;
		}
		more(node->right, key, val);
	}
}

template <class T>
T tree<T>::more(T key) {
	T val = std::numeric_limits<T>::max();
	more(root, key, val);
	return val;
}

template <class T>
typename tree<T>::Node* tree<T>::del(T key, Node* node) {
	if (node == NULL) return node;
	else if (key < node->value)
	{
		node->left = del(key, node->left);
	}
	else if (key > node->value)
	{
		node->right = del(key, node->right);
	}

	// Node deletion
	else {
		//case 1: Leaf Node
		if (node->left == NULL && node->right == NULL) {
			delete node;
			node = NULL;
			return node;
		}
		//case 2: one child
		else if (node->left == NULL) {
			Node* temp = node;
			node = node->right;
			delete temp;
			return node;
		}
		else if (node->right == NULL) {
			Node* temp = node;
			node = node->left;
			delete temp;
			return node;
		}
		//case 3: 2 child
		else {
			Node* temp = next(node);
			node->value = temp->value;
			node->right = del(temp->value, node->right);
		}
	}
	return node;
}

template <class T>
void tree<T>::del(T key) {
	root = del(key, root);
}



void compound() {
	tree<int> tr;
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::string s;
	int cnt = 0;
	while (std::cin >> s) {
		
		int n;
		std::cin >> n;
		if (std::cin.eof() || cnt == 100) {
			break;
		}

		if (s == "insert") {
			tr.insert(n);
		}
		else if (s == "exists") {
			if (tr.exists(n) == NULL) {
				std::cout << "false" << std::endl;
			}
			else std::cout << "true" << std::endl;
		}
		else if (s == "next") {
			int res = tr.more(n);
			if (res != std::numeric_limits<int>::max()) {
				std::cout << res << std::endl;
			}
			else std::cout << "none" << std::endl;
		}
		else if (s == "prev") {
			int res = tr.less(n);
			if (res != std::numeric_limits<int>::min()) {
				std::cout << res << std::endl;
			}
			else std::cout << "none" << std::endl;
		}
		else if (s == "delete") {
			tr.del(n);
		}
		//tr.inorder_traverse();
		cnt++;
		/*
		insert 15
		insert 8
		insert 34
		insert 3
		insert 12
		insert 10
		insert 28
		insert 42
		insert 19
		insert 21
		delete 15
		*/
	}
}

