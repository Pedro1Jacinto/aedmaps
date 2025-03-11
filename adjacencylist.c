
#include "structs.h"
#include "adjacencylist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*--------------------------------------------------------------------------------------------
Function: graphAdjLstNew

Arguments: number of vertices and number of edges

Description: allocates memory for the new graph 

Returns: graph
---------------------------------------------------------------------------------------------*/


GraphAdjLst graphAdjLstNew(int nrVertices, int nrEdges) {

	GraphAdjLst g;
	g.nrVertices = nrVertices;
	g.nrEdges = nrEdges;
	g.vertices = (VertexGraphAdjLst*)calloc(nrVertices, sizeof(VertexGraphAdjLst));
	g.edges = (EdgeGraphAdjLst*)malloc(nrEdges * sizeof(EdgeGraphAdjLst) * 2);

	return g;
}


/*--------------------------------------------------------------------------------------------
Function: GraphAdjLstRead

Arguments: input file(maps), number of vertices and number of edges

Description: reads from maps file and writes on graph 

Returns: graph
---------------------------------------------------------------------------------------------*/

GraphAdjLst graphAdjLstRead(FILE* fin, int nrVertices, int nrEdges) {

	GraphAdjLst g = graphAdjLstNew(nrVertices, nrEdges);

	VertexGraphAdjLst* vertex = g.vertices;
	EdgeGraphAdjLst* nextEdge = g.edges;

	int a, b, i;
	double w;
    char set[26];

	for(i=0; i < 26; i++) set[i] = '\0';
	

    while(nrVertices > 0 && fscanf(fin,"%d %s", &a, set) == 2){
        VertexGraphAdjLst* va = &vertex[a-1];
        strcpy(va->settlement, set);
		va->parent = -1;
		va->parentcost = -1;
        nrVertices--;
    }


	while (nrEdges > 0 && fscanf(fin, "%d %d %lf", &a, &b, &w) == 3) {

		VertexGraphAdjLst* va = &vertex[a - 1];
		VertexGraphAdjLst* vb = &vertex[b - 1];

		EdgeGraphAdjLst* e = nextEdge++;
		e->next = va->edges;
		e->vertexIdx = b - 1;
		e->weight = w;

		va->edges = e;
		va->degree++;

		e = nextEdge++;
		e->next = vb->edges;
		e->vertexIdx = a - 1;
		e->weight = w;

		vb->edges = e;
		vb->degree++;

		nrEdges--;
	}

	return g;
}


/*--------------------------------------------------------------------------------------------
Function: graphAdjLstFree

Arguments: pointer to graph adjacency list

Description: frees array of vertices and array of edges

Returns: nothing
---------------------------------------------------------------------------------------------*/


void graphAdjLstFree(GraphAdjLst* graph) {

	free(graph->vertices); 
	free(graph->edges); 
}

