#ifndef AVL_H
#define AVL_H

typedef int abstract_data;
#include <stdbool.h>

typedef struct Node {
    abstract_data data;
    int balance_factor;
    struct Node *left, *right;
} Node;

typedef Node *arvore;

void print_tree(Node *tree);
Node * insert_node(Node *tree, abstract_data data, bool *grew);
Node * single_left_rotation(Node *tree);
Node * single_right_rotation(Node *tree);
Node * double_left_rotation(Node *tree);
Node * double_right_rotation(Node *tree);
Node * delete_node(Node *tree, abstract_data data, bool *decreased);
int greater(Node *tree);
#endif