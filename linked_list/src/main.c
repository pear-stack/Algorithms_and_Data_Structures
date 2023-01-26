#include <stdio.h>
#include "linkedlist.h"

int main(int argc, char * argv[]){
    nodePtr root = NULL;
    for(int i = 0; i < (argc - 1); i++){
        insertNodeAtLast(&root, atoi(argv[i+1]));
    }
    printf("list struct:\n");
    displayList(root);
    return 0;
}