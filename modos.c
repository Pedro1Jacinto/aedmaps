#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adjacencylist.h"
#include "Dijkstra.h"
#include "structs.h"
#include "BFS.h"

/*--------------------------------------------------------------------------------------------
Function: ModoA0

Arguments: vertex, graph and outputfile

Description: writes on the outputfile the degree of the vertex sent to this function

Returns: nothing
---------------------------------------------------------------------------------------------*/

void ModoA0(int vertice1, GraphAdjLst g, FILE* fpOut){
    int i;
    
    if((vertice1 >=1) && (vertice1<=g.nrVertices)){
        i = g.vertices[vertice1-1].degree;
    }
    else {
        i = -1;
    }

    fprintf(fpOut,"%d %d A0 %d %d\n\n", g.nrVertices, g.nrEdges, vertice1, i);
}

/*--------------------------------------------------------------------------------------------
Function: ModoB0

Arguments: two vertices, graph and outputfile

Description: sees if  there is a direct path between vertice2 and vertice1, writing the cost of 
that path in the outputfile, if they are not directly connected it writes -1 in the outputfile 

Returns: nothing
---------------------------------------------------------------------------------------------*/

void ModoB0(int vertice1, int vertice2, GraphAdjLst g, FILE* fpOut){
double preco;
EdgeGraphAdjLst* aux;
aux = g.vertices[vertice1-1].edges;

    if((vertice1 >=1) && (vertice1<=g.nrVertices) && (vertice2 >=1) && (vertice2<=g.nrVertices)){
        while(g.vertices[vertice1-1].edges!=NULL){
            if(g.vertices[vertice1-1].edges->vertexIdx+1 == vertice2){
                preco = g.vertices[vertice1-1].edges->weight;
                break;
            }
            g.vertices[vertice1-1].edges= g.vertices[vertice1-1].edges->next;
            preco=-1;
        }
        
    }else preco = -1;

    g.vertices[vertice1-1].edges = aux;
    if(preco == -1)fprintf(fpOut,"%d %d B0 %d %d %d\n\n",g.nrVertices, g.nrEdges, vertice1, vertice2, (int)preco);
    else fprintf(fpOut,"%d %d B0 %d %d %.2lf\n\n",g.nrVertices, g.nrEdges, vertice1, vertice2, preco);
     
}

/*--------------------------------------------------------------------------------------------
Function: modoC0

Arguments: one vertex, number of steps, graph and outputfile

Description: if the vertex is part of the graph sends it to bfsC0 who returns number of steps(i)
equal to k if there are vertices at k steps from vertice1, writing 1 in the outputfile. If the 
number of steps returned by bfsC0 are not equal to k it means that that arent any vertices at k 
steps from vertice1, writing 0 in the outputfile. If it doesnt belong in the graph writes -1

Returns: nothing
---------------------------------------------------------------------------------------------*/

void ModoC0(int vertice1, int k, GraphAdjLst g, FILE* fpOut){
    int i=0;
    if((vertice1 >=1) && (vertice1<=g.nrVertices)){
        if(k<0){
            fprintf(fpOut,"%d %d C0 %d %d %d\n\n", g.nrVertices, g.nrEdges, vertice1, k, 0);
            return;
        }
        if(k==0){
            fprintf(fpOut,"%d %d C0 %d %d %d\n\n", g.nrVertices, g.nrEdges, vertice1, k, 1);
            return;
        }
        i = bfsC0(&g,vertice1-1,k);
        if (i==k){
            fprintf(fpOut,"%d %d C0 %d %d %d\n\n", g.nrVertices, g.nrEdges, vertice1, k, 1);
            return;
        }else{
            fprintf(fpOut,"%d %d C0 %d %d %d\n\n", g.nrVertices, g.nrEdges, vertice1, k, 0);
            return;
        }
    }else{
        fprintf(fpOut,"%d %d C0 %d %d %d\n\n", g.nrVertices, g.nrEdges, vertice1, k, -1);
        return;
    }
}

/*--------------------------------------------------------------------------------------------
Function: modosD0

Arguments: one vertex, number of steps, graph and outputfile

Description: if the vertex is part of the graph, sends it to bfsD0 who returns the number of vertices
at k steps or 0 if there is none, it writes on outputfile the number of vertices at k steps or zero
if there are none. If the vertex doesnt belong in the graph it writes -1 in the outputfile

Returns: nothing
---------------------------------------------------------------------------------------------*/

void ModoD0(int vertice1, int k, GraphAdjLst g, FILE* fpOut){
    int i=0;
    if((vertice1 >=1) && (vertice1<=g.nrVertices)){
        if(k<0){
            fprintf(fpOut,"%d %d D0 %d %d %d\n\n", g.nrVertices, g.nrEdges, vertice1, k, 0);
            return;
        }
        if(k==0){
            fprintf(fpOut,"%d %d D0 %d %d %d\n\n", g.nrVertices, g.nrEdges, vertice1, k, 1);
            return;
        }
        i = bfsD0(&g,vertice1-1,k);
        if (i!=0){
            fprintf(fpOut,"%d %d D0 %d %d %d\n\n", g.nrVertices, g.nrEdges, vertice1, k, i);
            return;
        }else{
            fprintf(fpOut,"%d %d D0 %d %d %d\n\n", g.nrVertices, g.nrEdges, vertice1, k, 0);
            return;
        }
    }else{
        fprintf(fpOut,"%d %d D0 %d %d %d\n\n", g.nrVertices, g.nrEdges, vertice1, k, -1);
        return;
    }
}


/*---------------------------------------Segunda Parte---------------------------------------------*/



void ModoA1(int vertice1, int vertice2, GraphAdjLst g, FILE* fpOut){
    int i, steps=0;
    double resultado;

    if( (0 >= vertice1) || (vertice1 > g.nrVertices) || (0 >= vertice2) || (vertice2 > g.nrVertices) ){
        fprintf(fpOut,"%d %d A1 %d %d -1",g.nrVertices, g.nrEdges, vertice1, vertice2);
        fprintf(fpOut,"\n\n");
        return;
    }

    if( vertice1 == vertice2 ){
        fprintf(fpOut,"%d %d A1 %d %d 0 0.00",g.nrVertices, g.nrEdges, vertice1, vertice2);
        fprintf(fpOut,"\n\n");
        return;
    }


    resultado = dijkstra(&g, vertice2-1, vertice1, -1, -1);

    if (resultado == -1){
        fprintf(fpOut,"%d %d A1 %d %d -1",g.nrVertices, g.nrEdges, vertice1, vertice2);
        fprintf(fpOut,"\n\n");
        return;
    }
    

    for(i=vertice1; i!= vertice2; i=g.vertices[i-1].parent) steps++;

    fprintf(fpOut,"%d %d A1 %d %d %d %.2lf", g.nrVertices, g.nrEdges, vertice1, vertice2, steps, resultado);
    for(i=vertice1; i!= vertice2; i=g.vertices[i-1].parent){
        fprintf(fpOut,"\n%d %d %.2lf", i, g.vertices[i-1].parent, g.vertices[i-1].parentcost);
    }
    fprintf(fpOut,"\n\n");
    return;
}



void ModoB1(int vertice1, int vertice2, char desvio, double k, GraphAdjLst g, FILE* fpOut){
double preco1, minpreco = -1, pathCost = 0, resultado=0;
int i,j, steps=0, interest=0;
parentB1 *pathStart = NULL , *pathEnd = NULL, *minpathStart = NULL, *minpathEnd = NULL;

    if( (0 >= vertice1) || (vertice1 > g.nrVertices) || (0 >= vertice2) || (vertice2 > g.nrVertices) ){
        if(k < 0){
            fprintf(fpOut,"%d %d B1 %d %d %c %d -1",g.nrVertices, g.nrEdges, vertice1, vertice2, desvio, (int)k);
        }else{
            fprintf(fpOut,"%d %d B1 %d %d %c %.2lf -1",g.nrVertices, g.nrEdges, vertice1, vertice2, desvio, k);
        }
        fprintf(fpOut,"\n\n");
        return;
    }

    preco1 = dijkstra(&g, vertice2-1 , vertice1, -1, -1);

    if(preco1 == -1){
        if(k < 0){
            fprintf(fpOut,"%d %d B1 %d %d %c %d -1",g.nrVertices, g.nrEdges, vertice1, vertice2, desvio, (int)k);
        }else{
            fprintf(fpOut,"%d %d B1 %d %d %c %.2lf -1",g.nrVertices, g.nrEdges, vertice1, vertice2, desvio, k);
        }
        fprintf(fpOut,"\n\n");
        return;
    }

    for(i=vertice1; i!= vertice2; i=g.vertices[i-1].parent, steps++){
        for (j=0; g.vertices[i-1].settlement[j] != '\0'; j++){
            if(g.vertices[i-1].settlement[j] == desvio) interest=1 ;
        }
    }

    if (interest == 1){
        if(k < 0){
            fprintf(fpOut,"%d %d B1 %d %d %c %d %d %.2lf",g.nrVertices, g.nrEdges, vertice1, vertice2, desvio, (int)k, steps, preco1);
        }else{
            fprintf(fpOut,"%d %d B1 %d %d %c %.2lf %d %.2lf",g.nrVertices, g.nrEdges, vertice1, vertice2, desvio, k, steps, preco1);
        }
        for(i=vertice1; i!= vertice2; i=g.vertices[i-1].parent){
            fprintf(fpOut,"\n%d %d %.2lf", i, g.vertices[i-1].parent, g.vertices[i-1].parentcost);
        }
        fprintf(fpOut,"\n\n");
        return;
    }
    
    for (i=0; i < g.nrVertices ; i++){
        for (j=0; g.vertices[i].settlement[j] != '\0'; j++){
            if(g.vertices[i].settlement[j] == desvio){
                pathCost = 0;
                pathStart = dijkstraB1(&g, i, vertice1, &pathCost);
                pathEnd = dijkstraB1(&g, vertice2-1, i+1, &pathCost);
                if((minpreco == -1 || pathCost < minpreco) && pathStart != NULL && pathStart != NULL){
                    interest = i+1;
                    if( minpathStart != NULL && minpathEnd != NULL){
                        free(minpathStart);
                        free(minpathEnd);
                    }
                    minpreco = pathCost;
                    minpathStart = pathStart;
                    minpathEnd = pathEnd; 
                }else{
                    free(pathStart);
                    free(pathEnd);
                }
            }
        }
    }

    if(minpreco == -1){
        if(k < 0){
            fprintf(fpOut,"%d %d B1 %d %d %c %d -1",g.nrVertices, g.nrEdges, vertice1, vertice2, desvio, (int)k);
        }else{
            fprintf(fpOut,"%d %d B1 %d %d %c %.2lf -1",g.nrVertices, g.nrEdges, vertice1, vertice2, desvio, k);
        }
        fprintf(fpOut,"\n\n");
        return;
    }
        
    resultado = (minpreco-preco1) / preco1 ;

    if(resultado > k && k >= 0){
        free(minpathStart);
        free(minpathEnd);
        fprintf(fpOut,"%d %d B1 %d %d %c %.2lf -1", g.nrVertices, g.nrEdges, vertice1, vertice2, desvio, k);
        fprintf(fpOut,"\n\n");
        return;
    }

    if(minpathStart == NULL || minpathEnd == NULL){
        if(k < 0){
            fprintf(fpOut,"%d %d B1 %d %d %c %d -1",g.nrVertices, g.nrEdges, vertice1, vertice2, desvio,(int) k);
        }else{
            fprintf(fpOut,"%d %d B1 %d %d %c %.2lf -1",g.nrVertices, g.nrEdges, vertice1, vertice2, desvio, k);
        }
        fprintf(fpOut,"\n\n");
        return;
    }

    steps = 0;
    for(i=vertice1; i!= interest; i=minpathStart[i-1].parent)steps++;
    for(i=interest; i!= vertice2; i=minpathEnd[i-1].parent)steps++;
    
    if(k < 0){
        fprintf(fpOut,"%d %d B1 %d %d %c %d %d %.2lf",g.nrVertices, g.nrEdges, vertice1, vertice2, desvio,(int) k, steps, minpreco);
    }else{
        fprintf(fpOut,"%d %d B1 %d %d %c %.2lf %d %.2lf",g.nrVertices, g.nrEdges, vertice1, vertice2, desvio, k, steps, minpreco);
    }

    for(i=vertice1; i!= interest; i=minpathStart[i-1].parent){
        fprintf(fpOut,"\n%d %d %.2lf", i, minpathStart[i-1].parent, minpathStart[i-1].weight);
    }
    for(i=interest; i!= vertice2; i=minpathEnd[i-1].parent){
        fprintf(fpOut,"\n%d %d %.2lf", i, minpathEnd[i-1].parent, minpathEnd[i-1].weight);
    }

    fprintf(fpOut,"\n\n");
    free(minpathStart);
    free(minpathEnd);
    return;
}




void ModoC1(int vertice1, int vertice2, int k, GraphAdjLst g, FILE* fpOut){
    double preco1, preco2, resultado;
    int i, steps=0, vproibido=-1;
    
    if( (0 >= vertice1) || (vertice1 > g.nrVertices) || (0 >= vertice2) || (vertice2 > g.nrVertices) ){
        fprintf(fpOut,"%d %d C1 %d %d %d -1",g.nrVertices, g.nrEdges, vertice1, vertice2, k);
        fprintf(fpOut,"\n\n");
        return;
    }

    if( vertice1 == vertice2 ){
        fprintf(fpOut,"%d %d C1 %d %d %d 0 0.00 -1",g.nrVertices, g.nrEdges, vertice1, vertice2, k);
        fprintf(fpOut,"\n\n");
        return;
    }

    preco1 = dijkstra(&g, vertice2-1, vertice1, -1, -1);

    if(preco1 == -1){
        fprintf(fpOut,"%d %d C1 %d %d %d -1",g.nrVertices, g.nrEdges, vertice1, vertice2, k);
        fprintf(fpOut,"\n\n");
        return;
    }

    for(i=vertice1; i!= vertice2; i=g.vertices[i-1].parent, steps++){
        if(steps == k-1){
        vproibido = i;
        }
    }

    if(vproibido == -1 || vertice1 == vproibido || vertice2 == vproibido){
        fprintf(fpOut,"%d %d C1 %d %d %d %d %.2lf -1",g.nrVertices, g.nrEdges, vertice1, vertice2, k, steps, preco1);
        for(i=vertice1; i!= vertice2; i=g.vertices[i-1].parent){
            fprintf(fpOut,"\n%d %d %.2lf", i, g.vertices[i-1].parent, g.vertices[i-1].parentcost);
        }
        fprintf(fpOut,"\n\n");
        return;
    }
    
    preco2 = dijkstra(&g, vertice2-1, vertice1, vproibido, -1);

    if(preco2 == -1){
        fprintf(fpOut,"%d %d C1 %d %d %d %d %.2lf -1",g.nrVertices, g.nrEdges, vertice1, vertice2, k, steps, preco1);
        for(i=vertice1; i!= vertice2; i=g.vertices[i-1].parent){
            fprintf(fpOut,"\n%d %d %.2lf", i, g.vertices[i-1].parent, g.vertices[i-1].parentcost);
        }
        fprintf(fpOut,"\n\n");
        return;
    }

    resultado = preco2 - preco1;

    fprintf(fpOut,"%d %d C1 %d %d %d %d %.2lf %.2lf", g.nrVertices, g.nrEdges, vertice1, vertice2, k, steps, preco1, resultado);
    for(i=vertice1; i!= vertice2; i=g.vertices[i-1].parent){
        fprintf(fpOut,"\n%d %d %.2lf", i, g.vertices[i-1].parent, g.vertices[i-1].parentcost);
    }
    fprintf(fpOut,"\n\n");
    return;
}



void ModoD1(int vertice1, int vertice2, int k, GraphAdjLst g, FILE* fpOut){
    double preco1 = -1, preco2 = -1, resultado;
    int i, steps=0, vproibido1=-1, vproibido2=-1;

    if( (0 >= vertice1) || (vertice1 > g.nrVertices) || (0 >= vertice2) || (vertice2 > g.nrVertices) ){
        fprintf(fpOut,"%d %d D1 %d %d %d -1",g.nrVertices, g.nrEdges, vertice1, vertice2,k);
        fprintf(fpOut,"\n\n");
        return;
    }

    if( vertice1 == vertice2 ){
        fprintf(fpOut,"%d %d D1 %d %d %d 0 0.00 -1",g.nrVertices, g.nrEdges, vertice1, vertice2, k);
        fprintf(fpOut,"\n\n");
        return;
    }


    preco1 = dijkstra(&g, vertice2-1, vertice1, -1, -1);

    if(preco1 == -1){
        fprintf(fpOut,"%d %d D1 %d %d %d -1",g.nrVertices, g.nrEdges, vertice1, vertice2, k);
        fprintf(fpOut,"\n\n");
        return;
    }

        for(i=vertice1; i!= vertice2; i=g.vertices[i-1].parent, steps++){
            if(steps == k-1){
                vproibido1 = i;
                vproibido2 = g.vertices[vproibido1-1].parent;
            } 
        }
    
    
    if(vproibido1 == -1 || vproibido2 == -1 ){
        fprintf(fpOut,"%d %d D1 %d %d %d %d %.2lf -1",g.nrVertices, g.nrEdges, vertice1, vertice2, k, steps, preco1);
        for(i=vertice1; i!= vertice2; i=g.vertices[i-1].parent){
            fprintf(fpOut,"\n%d %d %.2lf", i, g.vertices[i-1].parent, g.vertices[i-1].parentcost);
        }
        fprintf(fpOut,"\n\n");
        return;
    }
    
    preco2 = dijkstra(&g, vertice2-1, vertice1, vproibido1, vproibido2);


    if(preco2 == -1){
        fprintf(fpOut,"%d %d D1 %d %d %d %d %.2lf -1",g.nrVertices, g.nrEdges, vertice1, vertice2, k, steps, preco1);
        for(i=vertice1; i!= vertice2; i=g.vertices[i-1].parent){
            fprintf(fpOut,"\n%d %d %.2lf", i, g.vertices[i-1].parent, g.vertices[i-1].parentcost);
        }
        fprintf(fpOut,"\n\n");
        return;
    }

    resultado = preco2 - preco1;

    fprintf(fpOut,"%d %d D1 %d %d %d %d %.2lf %.2lf", g.nrVertices, g.nrEdges, vertice1, vertice2, k, steps, preco1, resultado);
    for(i=vertice1; i!= vertice2; i=g.vertices[i-1].parent){
        fprintf(fpOut,"\n%d %d %.2lf", i, g.vertices[i-1].parent, g.vertices[i-1].parentcost);
    }
    fprintf(fpOut,"\n\n");
    return;
}

