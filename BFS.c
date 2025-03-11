#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "BFS.h"

/*--------------------------------------------------------------------------------------------
Function: bfsC0

Arguments: graph, start vertex and number of steps

Description: runs breadth first search algorithm to see if the start vertex has neighbors at k 
steps

Returns: returns number of steps equal to k if the vertex has neighbor at k steps, if it doesnt
have neighbours at k steps it returns the max number of steps taken from the start vertex

---------------------------------------------------------------------------------------------*/

int bfsC0(GraphAdjLst* graph, int startVertex,int k) {
  queue* q = createQueue();
  int Maxsteps = 0;
  EdgeGraphAdjLst* aux;
  enqueue(q, startVertex);
  cleanStates(graph);
  
  while (q->front != NULL) {
    if (graph->vertices[q->front->item].state == 0) {
      graph->vertices[q->front->item].state = 1;
      if(q->front->steps > Maxsteps){
        Maxsteps=q->front->steps;
      }
      if(Maxsteps == k){
        break;
      }
      aux = graph->vertices[q->front->item].edges;
      while(aux!=NULL){
        enqueue(q, aux->vertexIdx);
        aux = aux->next;
      }    
    }
    dequeue(q);
  }
  clearQueue(q);
  return Maxsteps;
}

/*--------------------------------------------------------------------------------------------
Function: bfsD0

Arguments: graph, start vertex and number of steps

Description: uses breadth first search algorithm to count how many neighbours start vertex has 
at k steps utilizing a queue

Returns: 0 if the start vertex has no neighbours at k steps or the number of neighbours start 
vertex has at k steps 

---------------------------------------------------------------------------------------------*/

int bfsD0(GraphAdjLst* graph, int startVertex,int k) {
  queue* q = createQueue();
  int verticesk = 0;
  EdgeGraphAdjLst* aux;
  enqueue(q, startVertex);
  cleanStates(graph);
  
  while (q->front != NULL) {
    if (graph->vertices[q->front->item].state == 0) {
      graph->vertices[q->front->item].state = 1;
      
      if(q->front->steps == k){
        verticesk++;
      }
      aux = graph->vertices[q->front->item].edges;
      while(aux!=NULL){
        enqueue(q, aux->vertexIdx);
        aux = aux->next;
      }    
    }
    dequeue(q);
  }
  clearQueue(q);
  return verticesk;
}

/*--------------------------------------------------------------------------------------------
Function: createQueue

Arguments: nothing

Description: creates queue

Returns: queue
---------------------------------------------------------------------------------------------*/

queue* createQueue() {
  queue* q = malloc(sizeof(queue));
  q->front = NULL;
  q->rear = NULL;
  return q;
}

/*--------------------------------------------------------------------------------------------
Function: enqueue

Arguments: queue and value to add to queue

Description: adds an element to the queue

Returns: nothing

---------------------------------------------------------------------------------------------*/

void enqueue(queue* q, int value) {

  if (q->front == NULL){
    q->front=(Item*)malloc(sizeof(Item));
    q->front->item = value;
    q->front->steps = 0;
    q->front->next = NULL;
    q->rear = q->front;
  }else{
    q->rear->next=(Item*)malloc(sizeof(Item));
    q->rear = q->rear->next;
    q->rear->item = value;
    q->rear->steps = q->front->steps+1;
    q->rear->next = NULL;
  }

}

/*--------------------------------------------------------------------------------------------
Function: dequeue

Arguments: queue

Description: removes the front element of the queue

Returns: nothing
---------------------------------------------------------------------------------------------*/

void dequeue(queue* q){
  Item* aux;
  aux = q->front->next;
  free(q->front);
  q->front = aux;
}

/*--------------------------------------------------------------------------------------------
Function: clearQueue

Arguments: queue

Description: while queue is not empty frees all elemements of queue

Returns: nothing
---------------------------------------------------------------------------------------------*/

void clearQueue(queue* q){
  Item* aux;
  while(q->front!=NULL){
    aux = q->front->next;
    free(q->front);
    q->front = aux;
  }
}

/*--------------------------------------------------------------------------------------------
Function: cleanStates

Arguments: graph

Description: cleans state of the vertices

Returns: nothing
---------------------------------------------------------------------------------------------*/

void cleanStates(GraphAdjLst* graph){
  int i=0;
  for(i=0; i<graph->nrVertices;i++){
    graph->vertices[i].state=0;
  }
}