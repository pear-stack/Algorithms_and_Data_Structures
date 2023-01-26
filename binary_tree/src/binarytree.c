#include <binarytree.h>

struct tree_node
{
    int value;
    struct tree_node *fChild;
    struct tree_node *sChild;
};

void displayPost(p_tree_node_t root){
    if(root != NULL){
        displayPost(root->fChild);
        displayPost(root->sChild);
        printf("%d ", root->value);
    }
}

void displayPre(p_tree_node_t root){
    if(root != NULL){
        printf("%d ", root->value);
        displayPre(root->fChild);
        displayPre(root->sChild);
    }
}

void displayIn(p_tree_node_t root){
    if(root != NULL){
        displayIn(root->fChild);
        printf("%d ", root->value);
        displayIn(root->sChild);
    }
}

int isEmpty(p_tree_node_t node){
    if(node == NULL)
        return 0;
    else
        return 1;
}

void insertNodeBinTree(p_tree_node_t *head, int value){
    if(isEmpty(*head)){
        if ((*head)->value > value)
        {
            insertNodeBinTree(&(*head)->fChild, value);
        }else if ((*head)->value < value){
            insertNodeBinTree(&(*head)->sChild, value);
        }else{
            fprintf(stderr, "Value \"%d\" Duplication!\n",value);
            return;
        }
    }else{
        p_tree_node_t newNode = NULL;
        newNode = (p_tree_node_t)malloc(sizeof(p_tree_node_t));
        newNode->fChild = NULL;
        newNode->sChild = NULL;
        newNode->value = value;
        *head = newNode;  
    }  
}