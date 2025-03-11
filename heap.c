#include "structs.h"
#include "adjacencylist.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

 /*--------------------------------------------------------------------------------------------
Function: newMinHeapNode

Arguments: vertex ID and cost

Description: creates a new Node 

Returns: nothing
---------------------------------------------------------------------------------------------*/

MinHeapNode* newMinHeapNode(int vID, double cost)
{
    MinHeapNode* minHeapNode =( MinHeapNode*) malloc(sizeof( MinHeapNode));
    if (minHeapNode==NULL)exit(0);
    minHeapNode->vID = vID;
    minHeapNode->cost = cost;
    return minHeapNode;
}

/*--------------------------------------------------------------------------------------------
Function: createMinHeap

Arguments: number of vertices

Description: creates minHeap

Returns: created minHeap
---------------------------------------------------------------------------------------------*/
 
MinHeap* createMinHeap(int totalVertices)
{
    MinHeap* minHeap = (MinHeap*) malloc(sizeof(MinHeap));
    if (minHeap==NULL)exit(0);
    minHeap->pos = (int *)malloc(totalVertices * sizeof(int));
    if (minHeap->pos==NULL)exit(0);
    minHeap->size = 0;
    minHeap->totalVertices = totalVertices;
    minHeap->Nodes =(MinHeapNode**) malloc(totalVertices *sizeof(MinHeapNode*));
    if (minHeap->Nodes==NULL)exit(0);
    return minHeap;
}

/*--------------------------------------------------------------------------------------------
Function: freeNode

Arguments: Node

Description: frees a Node

Returns: nothing
---------------------------------------------------------------------------------------------*/

void freeNode (MinHeapNode* Node){
    free(Node);
}

/*--------------------------------------------------------------------------------------------
Function: freeHeap

Arguments: pointer to minHeap

Description: frees the minHeap

Returns: nothing
---------------------------------------------------------------------------------------------*/

void freeHeap(MinHeap* minHeap){
    int i;
    for(i=0; i < minHeap->size ; i++){
        free(minHeap->Nodes[i]);
    }
    free(minHeap->Nodes);
    free(minHeap->pos);
    free(minHeap);
    return;
}

 /*--------------------------------------------------------------------------------------------
Function: swapMinHeapNode

Arguments: two nodes

Description: swaps two nodes of min heap

Returns: nothing
---------------------------------------------------------------------------------------------*/

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b)
{
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
 /*--------------------------------------------------------------------------------------------
Function: minHeapify

Arguments: pointer to minHeap and index of a node

Description: heapifies at the index given and updates the position of the nodes if they are swapped

Returns: nothing
---------------------------------------------------------------------------------------------*/

void minHeapify(MinHeap* minHeap,int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size && minHeap->Nodes[left]->cost < minHeap->Nodes[smallest]->cost )
      smallest = left;
 
    if (right < minHeap->size && minHeap->Nodes[right]->cost < minHeap->Nodes[smallest]->cost )
      smallest = right;
 
    if (smallest != idx)
    {
        MinHeapNode *smallestNode = minHeap->Nodes[smallest];
        MinHeapNode *idxNode = minHeap->Nodes[idx];
 
        minHeap->pos[smallestNode->vID] = idx;
        minHeap->pos[idxNode->vID] = smallest;
 
        swapMinHeapNode(&minHeap->Nodes[smallest], &minHeap->Nodes[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 
/*--------------------------------------------------------------------------------------------
Function: isEmpty

Arguments: pointer to minHeap

Description: it checks if minHeap is empty

Returns: 
---------------------------------------------------------------------------------------------*/

int isEmpty(MinHeap* minHeap)
{
    return minHeap->size == 0;
}

/*--------------------------------------------------------------------------------------------
Function: extractMin

Arguments: pointer to minHeap

Description: extracts minimum node from minHeap

Returns: minimum node from minHeap
---------------------------------------------------------------------------------------------*/
 
MinHeapNode* extractMin(MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 
    MinHeapNode* root = minHeap->Nodes[0];
 
    MinHeapNode* lastNode = minHeap->Nodes[minHeap->size - 1];
    minHeap->Nodes[0] = lastNode;
 
    minHeap->pos[root->vID] = minHeap->size-1;
    minHeap->pos[lastNode->vID] = 0;
 
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}

/*--------------------------------------------------------------------------------------------
Function: decreaseKey

Arguments: pointer to minHeap, a vertex and cost

Description: decreases cost value of the given vertex, using the position of minHeap to get current
index of node in minHeap

Returns: nothing
---------------------------------------------------------------------------------------------*/
 
void decreaseKey(MinHeap* minHeap, int vID, double cost)
{
    int i = minHeap->pos[vID];
 
    minHeap->Nodes[i]->cost = cost;
 
    while (i && minHeap->Nodes[i]->cost < minHeap->Nodes[(i - 1) / 2]->cost)
    {
        minHeap->pos[minHeap->Nodes[i]->vID] = (i-1)/2;
        minHeap->pos[minHeap->Nodes[(i-1)/2]->vID] = i;
        swapMinHeapNode(&minHeap->Nodes[i], &minHeap->Nodes[(i - 1) / 2]);
 
        i = (i - 1) / 2;
    }
}
 
 /*--------------------------------------------------------------------------------------------
Function: isInMinHeap

Arguments: pointer to minHeap and vertex index

Description: checks if a given vertex is in min heap 

Returns: true if its is in min heap, false if it is not
---------------------------------------------------------------------------------------------*/

bool isInMinHeap(MinHeap *minHeap, int vID)
{
   if (minHeap->pos[vID] < minHeap->size) return true;

   return false;
}
 

