#include <linkedlist.h>

typedef struct node
{
    int value;
    struct node *nextNode;
}node_;

int isEmpty(nodePtr node){
    if(node == NULL)
        return 1;
    else
        return 0;
};

void insertNodeAtFirst(nodePtr* head, int value){
    nodePtr new_node = (nodePtr)malloc(sizeof(node_));
    new_node->value = value;
    new_node->nextNode = *head;
    *head = new_node;
};

void insertNodeAtLast(nodePtr* head, int value){
    nodePtr new_node = (nodePtr)malloc(sizeof(node_));
    new_node->value = value;
    new_node->nextNode = NULL;
    if(isEmpty(*head))
        *head = new_node;
    else{
        nodePtr currentNode = *head;
        while(currentNode->nextNode != NULL){
            currentNode = currentNode->nextNode;
        }
        currentNode->nextNode = new_node;
    }
};

void insertNodeAt(nodePtr *head, int position, int value){
    nodePtr newNode = (nodePtr)malloc(sizeof(node_));
    newNode->value = value;
    nodePtr currentNode = *head;
    nodePtr previousNode = NULL;
    int currentPosition = 0;
    while(!isEmpty(currentNode)){
        if(currentPosition < position){
            previousNode = currentNode;
            currentNode = currentNode->nextNode;
            currentPosition++;
        }else if(currentPosition == position){
            if(position == 0){
                newNode->nextNode = *head;
                *head = newNode;
                return;
            }else{
                previousNode->nextNode = newNode;
                newNode->nextNode = currentNode;
                return;
            }
        }else
            break;
    }
    printf("position out of list range\n");
};

void deleteNodeFrom(nodePtr *head, int position){
    nodePtr currentNode = *head;
    int currentPosition = 0;
    nodePtr previousNode = NULL;
    nodePtr tmpNode = NULL;
    while(currentNode != NULL){
        if(currentPosition < position){
            previousNode = currentNode;
            currentNode = currentNode->nextNode;
            currentPosition++;
        }else if(currentPosition == position){
            if(position == 0){
                tmpNode = currentNode->nextNode;
                free(*head);
                *head = tmpNode;
                return;
            }else{
                tmpNode = currentNode->nextNode;
                free(currentNode);
                currentNode = tmpNode;
                previousNode->nextNode = currentNode;
                return;
            }
        }else
            break;
    }
    printf("position out of list range\n");
};

void updateNodeValue(nodePtr head, int position, int newValue){
    nodePtr currentNode = head;
    int currentPosition = 0;
    while(currentNode != NULL){
        if(currentPosition < position){
            currentNode = currentNode->nextNode;
            currentPosition++;
        }else if(currentPosition == position){
            currentNode->value = newValue;
            return;
        }else
            break;
    }
    printf("position out of list range\n");
};

nodePtr findValue(nodePtr head, int value){
    nodePtr currentNode = head;
    int position = 0;
    while(currentNode != NULL){
        if(currentNode->value != value){
            currentNode = currentNode->nextNode;
            position++;
        }else{
            printf("value %d found at %d\n", value, position);
            return currentNode;
        }
    }
    printf("value %d not found\n", value);
    return NULL;
};

void displayList(nodePtr head){
    if(isEmpty(head))
        printf("List is empty\n");
    else{
        nodePtr currentNode = head;
        while (currentNode != NULL)
        {
            printf("-> %d ", currentNode->value);
            currentNode = currentNode->nextNode;
        }
        printf("\n");
    }
};
