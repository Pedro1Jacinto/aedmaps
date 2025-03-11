#ifndef _GRAPH_ADJLST_H
#define _GRAPH_ADJLST_H
#include <stdio.h>


typedef struct _edge EdgeGraphAdjLst;
typedef struct _vertex VertexGraphAdjLst;
typedef struct _GraphAdjLst GraphAdjLst;

/*--------------------------------------------------------------------------------------------
struct _vertex

struct of vertex containing a list of his edges, his degree, state, settlement, parent and cost 
of parent edge (used in dijkstra algorithm to store the path between vertices). 


---------------------------------------------------------------------------------------------*/

struct _vertex {
	EdgeGraphAdjLst* edges;
	int degree; 
	int state; 
    char settlement[30];
	int parent;
	double parentcost;
};

/*--------------------------------------------------------------------------------------------
struct _edge

struct of an edge contains the index of the connected vertex, its weight and pointer to the next
edge

---------------------------------------------------------------------------------------------*/

struct _edge {
	EdgeGraphAdjLst* next;
	double weight; 
	int vertexIdx; 
};

/*--------------------------------------------------------------------------------------------
struct _GraphAdjLst

struct graph adjacency list has the total number of vertices and edges, an array of vertices
and an array of lists

---------------------------------------------------------------------------------------------*/

struct _GraphAdjLst{
	int nrVertices;
	int nrEdges;
	VertexGraphAdjLst* vertices; 
	EdgeGraphAdjLst* edges; 
};


#endif