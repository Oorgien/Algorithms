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
		T max_element = std::numeric_limits<T>::min();
		T min_element = std::numeric_limits<T>::max();
		int height = 0;
		Node *left = NULL;
		Node *right = NULL;
		Node *parent = NULL;
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
	int height(Node* node);
	T max_element(Node* node);
	T min_element(Node* node);
	Node* balance_tree(Node* node);
	Node* insert(T key, Node* node);
	Node* SingleLeftRotate(Node* a);
	Node* SingleRightRotate(Node* a);
	Node* DoubleLeftRotate(Node* a);
	Node* DoubleRightRotate(Node* a);
	Node* del(T key, Node* node);
	Node* exists(T key, Node* node);
	void more(Node* node, T key, T& val);
	void less(Node* node, T key, T& val);
	Node* next(Node* node);
	Node* prev(Node* node);
	Node* go_to_left(Node* node);
	Node* go_to_right(Node* node);
	void inorder_traverse(Node* node);
	Node *root; //root - указатель
};

template <class T>
tree<T>::tree() {
	root = NULL;
}

template <class T>
void tree<T>::inorder_traverse(Node* node) {
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
int  tree<T>::height(Node* node) {
	return node == NULL ? -1 : node->height;
}

template <class T>
T tree<T>::max_element(Node* node) {
	if (node == NULL) {
		return std::numeric_limits<T>::min();
	}
	else if (node->right == NULL && node->left == NULL) {
		return node->value;
	}
	else {
		return node->max_element;
	}
}

template <class T>
T tree<T>::min_element(Node* node) {
	if (node == NULL) {
		return std::numeric_limits<T>::max();
	}
	if (node->right == NULL && node->left == NULL) {
		return node->value;
	}
	else {
		return node->min_element;
	}
}

template <class T>
typename tree<T>::Node* tree<T>::SingleLeftRotate(Node* a) {
	Node* b = a->right;
	Node* c = b->left;
	b->left = a;
	a->right = c;

	a->height = std::max(height(c), height(a->left)) + 1;
	b->height = std::max(height(b->right), height(a)) + 1;

	a->max_element = std::max(a->value,
		std::max(max_element(c), max_element(a->left)));
	a->min_element = std::min(a->value,
		std::min(min_element(c), min_element(a->left)));

	b->max_element = std::max(b->value,
		std::max(max_element(b->right), max_element(a)));
	b->min_element = std::min(b->value,
		std::min(min_element(b->right), min_element(a)));
	return b;
}

template <class T>
typename tree<T>::Node* tree<T>::SingleRightRotate(Node* a) {
	Node* b = a->left;
	Node* c = b->right;
	b->right = a;
	a->left = c;
	
	a->height = std::max(height(c), height(a->right)) + 1;
	b->height = std::max(height(b->left), height(a)) + 1;

	a->max_element = std::max(a->value,
		std::max(max_element(c), max_element(a->right)));
	a->min_element = std::min(a->value,
		std::min(min_element(c), min_element(a->right)));

	b->max_element = std::max(b->value,
		std::max(max_element(b->left), max_element(a)));
	b->min_element = std::min(b->value,
		std::min(min_element(b->left), min_element(a)));
	return b;
}

template <class T>
typename tree<T>::Node* tree<T>::DoubleRightRotate(Node* a) {
	a->left = SingleLeftRotate(a->left);
	return SingleRightRotate(a);
}

template <class T>
typename tree<T>::Node* tree<T>::DoubleLeftRotate(Node* a) {
	a->right = SingleRightRotate(a->right);
	return SingleLeftRotate(a);
}

template <class T>
void tree<T>::insert(T key) {
	if (root == NULL) {
		root = new Node;
		root->value = key;
		root->height = 0;
	}
	else {
		root = insert(key, root);
	}
}


template <class T>
typename tree<T>::Node* tree<T>::balance_tree(Node* node) {
	if (height(node->left) - height(node->right) == 2) {
		if (height(node->left->right) <= height(node->left->left)) {
			node = SingleRightRotate(node);
		}
		else {
			node = DoubleRightRotate(node);
		}

		if (height(node->right->left) <= height(node->right->right)) {
			node = SingleLeftRotate(node);
		}
		else {
			node = DoubleLeftRotate(node);
		}
	}
	return node;
}

template <class T>
typename tree<T>::Node* tree<T>::insert(T key, Node* node) {
	if (node == NULL) {
		node = new Node;
		node->value = key;
		node->left = NULL;
		node->right = NULL;
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
	}
	node->height = std::max(height(node->left), height(node->right)) + 1;
	node->max_element = std::max(node->value,
		std::max(max_element(node->left), max_element(node->right)));
	node->min_element = std::min(node->value,
		std::min(min_element(node->left), min_element(node->right)));
	return node;
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
typename tree<T>::Node* tree<T>::exists(T key, Node* node) {
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
void tree<T>::less(Node* node, T key, T& val) {
	if (node != NULL) {
		if (node->value < key) val = std::max(val, node->value);
		if (min_element(node->right) < key) {
			less(node->right, key, val);
		}
		else less(node->left, key, val);
	}
}

template <class T>
T tree<T>::less(T key) {
	T val = std::numeric_limits<T>::min();
	less(root, key, val);
	return val;
}

template <class T>
void tree<T>::more(Node* node, T key, T& val) {
	if (node != NULL) {
		if (node->value > key) val = std::min(val, node->value);
		if (max_element(node->left) > key) {
			more(node->left, key, val);
		}
		else more(node->right, key, val);
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

	node = balance_tree(node);
	node->height = std::max(height(node->left), height(node->right)) + 1;
	node->max_element = std::max(node->value,
		std::max(max_element(node->left), max_element(node->right)));
	node->min_element = std::min(node->value ,
		std::min(min_element(node->left), min_element(node->right)));
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
		if (std::cin.eof()) {
			break;
		}

		if (s == "insert") {
			tr.insert(n);
		}
		else if (s == "exists") {
			std::cout << "";
			if (tr.exists(n) == NULL) {
				std::cout << "false" << std::endl;
			}
			else if (tr.exists(n) != NULL) {
				std::cout << "true" << std::endl;
			}
		}
		else if (s == "next") {
			int res = tr.more(n);
			if (res != std::numeric_limits<int>::max()) {
				std::cout << res << std::endl;
			}
			else if (res == std::numeric_limits<int>::max()) {
				std::cout << "none" << std::endl;
			}
		}
		else if (s == "prev") {
			int res = tr.less(n);
			if (res != std::numeric_limits<int>::min()) {
				std::cout << res << std::endl;
			}
			else if (res == std::numeric_limits<int>::min()) {
				std::cout << "none" << std::endl;
			}
		}
		else if (s == "delete") {
			tr.del(n);
		}
		//tr.inorder_traverse();
		cnt++;
		/*
		insert 14
		insert 8
		insert 3
		insert 10
		insert 19
		insert 17
		insert 25
		insert 1
		insert 9 
		insert 16
		insert 23
		insert 4
		insert 11
		insert 18
		insert 27

		*/
	}
}


