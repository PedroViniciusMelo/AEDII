#include "avl.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

Node * rotate(Node *tree) {
    if (tree->balance_factor > 0) {
        switch (tree->right->balance_factor) {
            case 0:
            case 1:
                return single_left_rotation(tree);

            case -1:
                return double_left_rotation(tree);
        }
    } else {
        switch (tree->left->balance_factor) {
            case 0:
            case -1:
                return single_right_rotation(tree);

            case 1:
                return double_right_rotation(tree);
        }
    }
}

Node * single_left_rotation(Node *tree) {
    Node *p, *u, *t1, *t2, *t3;

    p = tree;
    u = p->right;
    t1 = p->left;
    t2 = u->left;
    t3 = u->right;

    u->left = p;
    p->right = t2;

    if (u->balance_factor == 1) {
        p->balance_factor = 0;
        u->balance_factor = 0;
    } else if (u->balance_factor == 0) {
        p->balance_factor = 1;
        u->balance_factor = -1;
    }

    return u;
}

Node * single_right_rotation(Node *tree) {
    Node *p, *u, *t1, *t2, *t3;

    p = tree;
    u = p->left;
    t1 = u->left;
    t2 = u->right;
    t3 = p->right;

    u->right = p;
    p->left = t2;

    if (u->balance_factor == -1) {
        p->balance_factor = 0;
        u->balance_factor = 0;
    } else if (u->balance_factor == 0) {
        p->balance_factor = -1;
        u->balance_factor = 1;
    }

    return u;
}

Node * double_left_rotation(Node *tree) {
    Node *p, *u, *v, *t1, *t2, *t3, *t4;

    p = tree;
    u = p->right;
    v = u->left;
    t1 = p->left;
    t2 = v->left;
    t3 = v->right;
    t4 = u->right;

    // intermediate rotation
    p->right = v;
    v->right = u;
    u->left = t3;

    // final rotation
    v->left = p;
    p->right = t2;

    if (v->balance_factor == -1) {
        p->balance_factor = 0;
        u->balance_factor = 1;
        v->balance_factor = 0;
    } else if (v->balance_factor == 0) {
        p->balance_factor = 0;
        u->balance_factor = 0;
        v->balance_factor = 0;
    } else if (v->balance_factor == 1) {
        p->balance_factor = -1;
        u->balance_factor = 0;
        v->balance_factor = 0;
    }

    return v;
}

Node * double_right_rotation(Node *tree) {
    Node *p, *u, *v, *t1, *t2, *t3, *t4;

    p = tree;
    u = p->left;
    v = u->right;
    t1 = u->left;
    t2 = v->left;
    t3 = v->right;
    t4 = p->right;

    // intermediate rotation
    p->left = v;
    v->left = u;
    u->right = t2;

    // final rotation
    v->right = p;
    p->left = t3;

    if (v->balance_factor == -1) {
        p->balance_factor = 1;
        u->balance_factor = 0;
        v->balance_factor = 0;
    } else if (v->balance_factor == 0) {
        p->balance_factor = 0;
        u->balance_factor = 0;
        v->balance_factor = 0;
    } else if (v->balance_factor == 1) {
        p->balance_factor = 0;
        u->balance_factor = -1;
        v->balance_factor = 0;
    }

    return v;
}

Node * insert_node(Node *tree, abstract_data data, bool *grew)  {
    if (tree == NULL) {
        Node *node = (Node *) malloc(sizeof(Node));
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        node->balance_factor = 0;

        *grew = true;

        return node;
    } else {
        if (data >= tree->data) {
            tree->right = insert_node(tree->right, data, grew);

            if (*grew) {
                switch (tree->balance_factor) {
                    case 0:
                        tree->balance_factor = 1;
                        *grew = true;
                        break;

                    case -1:
                        tree->balance_factor = 0;
                        *grew = false;
                        break;

                    case 1:
                        *grew = false;
                        return rotate(tree);
                }
            }

        } else {
            tree->left = insert_node(tree->left, data, grew);

            if (*grew) {
                switch (tree->balance_factor) {
                    case 0:
                        tree->balance_factor = -1;
                        *grew = true;
                        break;

                    case -1:
                        *grew = false;
                        return rotate(tree);

                    case 1:
                        tree->balance_factor = 0;
                        *grew = false;
                        break;
                }
            }
        }
        return tree;
    }
}

Node * delete_node(Node *tree, abstract_data data, bool *decreased) {
    if (tree == NULL) {
        *decreased = false;
        return NULL;
    }

    if (data == tree->data) {
        *decreased = true;

        if (tree->left == NULL && tree->right == NULL) {
            free(tree);
            return NULL;
        } else if (tree->left != NULL && tree->right == NULL) {
            Node *left = tree->left;
            free(tree);
            return left;
        } else if (tree->left == NULL && tree->right != NULL) {
            Node *right = tree->right;
            free(tree);
            return right;
        } else if (tree->left != NULL && tree->right != NULL) {
            int max_data = greater(tree->left);
            tree->data = max_data;
            tree->left = delete_node(tree->left, max_data, decreased);

            if (*decreased) {
                switch (tree->balance_factor) {
                    case 0:
                        tree->balance_factor = 1;
                        *decreased = false;
                        break;

                    case -1:
                        tree->balance_factor = 0;
                        *decreased = true;
                        break;

                    case 1:
                        if (tree->right->balance_factor == 0) {
                            *decreased = false;
                        } else {
                            *decreased = true;
                        }

                        return rotate(tree);
                }
            }

            return tree;
        }
    } else {
        if (data >= tree->data) {
            tree->right = delete_node(tree->right, data, decreased);

            if (*decreased) {
                switch (tree->balance_factor) {
                    case 0:
                        tree->balance_factor = -1;
                        *decreased = false;
                        break;

                    case -1:
                        if (tree->left->balance_factor == 0) {
                            *decreased = false;
                        } else {
                            *decreased = true;
                        }

                        return rotate(tree);

                    case 1:
                        tree->balance_factor = 0;
                        *decreased = true;
                        break;
                }
            }

        } else {
            tree->left = delete_node(tree->left, data, decreased);

            if (*decreased) {
                switch (tree->balance_factor) {
                    case 0:
                        tree->balance_factor = 1;
                        *decreased = false;
                        break;

                    case -1:
                        tree->balance_factor = 0;
                        *decreased = true;
                        break;

                    case 1:
                        if (tree->right->balance_factor == 0) {
                            *decreased = false;
                        } else {
                            *decreased = true;
                        }

                        return rotate(tree);
                }
            }

        }
        return tree;
    }
}

int greater(Node *tree) {
    if (tree != NULL) {
        if (tree->right == NULL) {
            return tree->data;
        } else {
            greater(tree->right);
        }
    } else {
        return -1;
    }
}



void print_node(Node *tree) {
    printf("%d [%d]", tree->data, tree->balance_factor);
}

void print_tree(Node *tree) {
    printf("(");
    if(tree != NULL) {
        print_node(tree);
        print_tree(tree->left);
        print_tree(tree->right);
    }
    printf(")");
}