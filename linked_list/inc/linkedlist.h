#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node node_;
typedef node_ *nodePtr;

void insertNodeAtFirst(nodePtr*, int);
void insertNodeAtLast(nodePtr*, int);
void insertNodeAt(nodePtr*, int, int);
void deleteNodeFrom(nodePtr*, int);
void updateNodeValue(nodePtr, int, int);
nodePtr findValue(nodePtr, int);
void displayList(nodePtr);

#endif
