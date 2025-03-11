#include "structs.h"
#include "adjacencylist.h"
#include "heap.h"
#include "Dijkstra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*--------------------------------------------------------------------------------------------
Function: dijkstra

Arguments: pointer to graph, beginning vertex, destination vertex and two vertices 

Description: utilizes the dijkstra algorithm to find the shortest path between two vertices.
v1 and v2 will be used by C1 and D1 when we cant pass in a certain vertex or we cant go through an
edge

Returns: cost of path if it exists or returns -1 if there is no path between them

---------------------------------------------------------------------------------------------*/

double dijkstra(GraphAdjLst* graph, int beg, int dest, int v1, int v2)
{   
    int V, i;
    V = graph->nrVertices;

    double cost[V];    
    MinHeap* minHeap = createMinHeap(V);

    for (i = 0; i < V; ++i)
    {   
        cost[i] = INT_MAX;
        minHeap->Nodes[i] = newMinHeapNode(i,cost[i]);
        minHeap->pos[i] = i;
    }
 
    cost[beg] = 0;
    decreaseKey(minHeap, beg, cost[beg]);
 
    minHeap->size = V;
 
    while (!isEmpty(minHeap))
    {
        MinHeapNode* minHeapNode = extractMin(minHeap);
       
        int vExt = minHeapNode->vID;
        freeNode(minHeapNode);


        if((vExt+1 == dest) && (cost[dest-1] != INT_MAX)){
            freeHeap(minHeap);
            return cost[dest-1];
        } 


        EdgeGraphAdjLst* vEdge = graph->vertices[vExt].edges;
        while (vEdge != NULL)
        {
            int vID = vEdge->vertexIdx;

            if((v1 != -1) && (v2 == -1) && (vID+1 == v1)){
                vEdge = vEdge->next;
                if(vEdge==NULL)break;
                vID = vEdge->vertexIdx;
            } 

            if((v1 != -1) && (v2 != -1) && (((vExt+1 == v2) && (vID+1 == v1))||((vExt+1 == v1) && (vID+1 == v2)))){
                vEdge = vEdge->next;
                if(vEdge==NULL)break;
                vID = vEdge->vertexIdx;
            }
            

            if (isInMinHeap(minHeap, vID) && cost[vExt] != INT_MAX && vEdge->weight + cost[vExt] < cost[vID])
            {
                cost[vID] = cost[vExt] + vEdge->weight;
 
                decreaseKey(minHeap, vID, cost[vID]);
                if(v1 == -1 ){
                graph->vertices[vID].parent = vExt+1;          
                graph->vertices[vID].parentcost = vEdge->weight;
                }
                
            }
            vEdge = vEdge->next;
        }
    }
    freeHeap(minHeap);
    return -1;
}

/*--------------------------------------------------------------------------------------------
Function: dijkstraB1

Arguments: pointer to graph, beginning vertex, destination vertex and addres of pathCost 

Description: finds the shortest path between the two given vertices and saves its cost in
pathCost

Returns: path between the two vertices if exists or NULL if it doesnt

---------------------------------------------------------------------------------------------*/

parentB1* dijkstraB1(GraphAdjLst* graph, int beg, int dest, double* pathCost)
{   
    int V = graph->nrVertices;

    double cost[V]; 

    parentB1 *path = malloc(V*sizeof(parentB1));   

    MinHeap* minHeap = createMinHeap(V);

    for (int i = 0; i < V; i++)
    {   
        path[i].parent = -1;
        path[i].weight = -1;
        cost[i] = INT_MAX;
        minHeap->Nodes[i] = newMinHeapNode(i,cost[i]);
        minHeap->pos[i] = i;
    }
 
    cost[beg] = 0;
    decreaseKey(minHeap, beg, cost[beg]);
 
    minHeap->size = V;
 
    while (!isEmpty(minHeap))
    {

        MinHeapNode* minHeapNode = extractMin(minHeap);
       
        int vExt = minHeapNode->vID;
        freeNode(minHeapNode);


        if((vExt+1 == dest) && (cost[dest-1] != INT_MAX)){
            *pathCost += cost[dest-1];
            freeHeap(minHeap);
            return path;
        } 

        EdgeGraphAdjLst* vEdge = graph->vertices[vExt].edges;
        while (vEdge != NULL)
        {
            int vID = vEdge->vertexIdx;

            
            if (isInMinHeap(minHeap, vID) && cost[vExt] != INT_MAX && vEdge->weight + cost[vExt] < cost[vID])
            {
                cost[vID] = cost[vExt] + vEdge->weight;
 
                decreaseKey(minHeap, vID, cost[vID]);
                
                path[vID].parent = vExt+1;
                path[vID].weight = vEdge->weight;
                
            }
            vEdge = vEdge->next;
        }
    }
    freeHeap(minHeap);
    free(path);
    return NULL;
}











