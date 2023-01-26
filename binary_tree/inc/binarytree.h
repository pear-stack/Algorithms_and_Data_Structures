#ifndef BINARYTREE_H
#   define BINARYTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node tree_node_t;
typedef tree_node_t * p_tree_node_t;

void insertNodeBinTree(p_tree_node_t *, int);
void displayPost(p_tree_node_t);
void displayPre(p_tree_node_t);
void displayIn(p_tree_node_t);

#endif
