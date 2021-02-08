#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

struct Node {
    int value = 0;
    Node *left = NULL;
    Node *right = NULL;
};

void inorder_traverse(Node *node) {
    if (node->left != NULL) {
        inorder_traverse(node->left);
    }
    std::cout << node->value << " ";
    if (node->right != NULL) {
        inorder_traverse(node->right);
    }
}

void compound() {
    Node *head = new Node;
    head->value = 8;

    Node *left_1 = new Node;
    left_1->value = 3;

    Node *right_1 = new Node;
    right_1->value = 10;

    head->left = left_1;
    head->right = right_1;

    Node *left_2 = new Node;
    left_2->value = 1;
    left_1->left = left_2;

    Node* right_2 = new Node;
    right_2->value = 6;
    left_1->right = right_2;

    Node* right_3 = new Node;
    right_3->value = 14;
    right_1->right = right_3;
    inorder_traverse(head);
}