#include <stdbool.h>

/*--------------------------------------------------------------------------------------------
struct MinHeapNode

structure to represent a min heap node

---------------------------------------------------------------------------------------------*/

typedef struct MinHeapNode
{
    int  vID;
    double cost;
}MinHeapNode;


/*--------------------------------------------------------------------------------------------
struct MinHeap

structure to represent a min heap
---------------------------------------------------------------------------------------------*/

typedef struct MinHeap
{
    int size;    
    int totalVertices; 
    int *pos;   
    MinHeapNode **Nodes;
}MinHeap;


MinHeapNode* newMinHeapNode(int vID, double cost);

MinHeap* createMinHeap(int totalVertices);

void freeHeap(MinHeap* minHeap);

void freeNode (MinHeapNode* Node);

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b);

void minHeapify(MinHeap* minHeap,int idx);

int isEmpty(MinHeap* minHeap);

MinHeapNode* extractMin(MinHeap* minHeap);

void decreaseKey(MinHeap* minHeap, int vID, double cost);

bool isInMinHeap(MinHeap *minHeap, int vID);

