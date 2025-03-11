

typedef struct parentB1
{
    int parent;
    double weight;
}parentB1;



double dijkstra(GraphAdjLst* graph, int beg, int dest, int v1, int v2);

parentB1* dijkstraB1(GraphAdjLst* graph, int beg, int dest, double* pathCost);