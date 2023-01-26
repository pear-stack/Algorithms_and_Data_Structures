#include <stdio.h>
#include "binarytree.h"

int main(int argc, char * argv[]){
    p_tree_node_t root = NULL;
    for(int i = 0; i < (argc - 1); i++){
        insertNodeBinTree(&root, atoi(argv[i+1]));
    }
    printf("PostOrder:\n");
    displayPost(root);
    printf("\nPreOrder:\n");
    displayPre(root);
    printf("\nInOrder:\n");
    displayIn(root);
    return 0;
}