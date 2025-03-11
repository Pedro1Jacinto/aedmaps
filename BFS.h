#ifndef _BFS_H
#define _BFS_H
#include "structs.h"

typedef struct _items{
    int item;
    int steps;
    struct _items* next;
}Item;

typedef struct _queue{
    Item* front;
    Item* rear;
}queue;



int bfsC0(GraphAdjLst* graph, int startVertex,int k);

int bfsD0(GraphAdjLst* graph, int startVertex,int k);

void enqueue(queue* q, int value);

queue* createQueue();

void dequeue(queue* q);

void printQueue(queue* q);

void cleanStates(GraphAdjLst* graph);

void clearQueue(queue* q);


#endif