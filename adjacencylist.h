
#include"structs.h"

GraphAdjLst graphAdjLstNew(int nrVertices, int nrEdges);

GraphAdjLst graphAdjLstRead(FILE* fin, int nrVertices, int nrEdges);

void graphAdjLstFree(GraphAdjLst* graph);

