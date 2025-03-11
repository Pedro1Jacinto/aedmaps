#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adjacencylist.h"
#include "structs.h"
#include "modos.h"

/*--------------------------------------------------------------------------------------------
Function: ReadOption

Arguments: argv

Description: Validates option given in argv

Returns: 1 if option is valid, 0 if its not
---------------------------------------------------------------------------------------------*/
int ReadOption(char *argv[]){
    if((strcmp(argv[1],"-oo")==0))return 1;
    if((strcmp(argv[1],"-oa")==0))return 1;
    if((strcmp(argv[1],"-aa")==0))return 1;
    if((strcmp(argv[1],"-ao")==0))return 1;
    else return 0;

}

/*--------------------------------------------------------------------------------------------
Function: ReadProblem

Arguments: argv, graph adjacency list, file containing problems and outputfile

Description: reads problems in the problem file and sends each problem to its solving function, 
if option is type -ox (x being a or o) the function only reads the first problem in the problem 
file

Returns: nothing
----------------------------------------------------------------------------------------------*/

void ReadProblem(char* argv[], GraphAdjLst g, FILE* problems, FILE* fpOut){
    int vertice1, vertice2, etapa;
    double k;
    char modo[2];
    char desvio;
    
    while(fscanf(problems,"%s %d %d ", modo, &vertice1, &vertice2)!= EOF){

        if (strcmp(modo,"B1")==0){
          if (fscanf(problems, "%c %lf", &desvio, &k)==0) exit(0); 
        }
        if (strcmp(modo,"C1")==0||strcmp(modo,"D1")==0){
          if (fscanf(problems, "%d", &etapa)==0)exit(0);
        }
        
        if(strcmp(modo,"A1")==0)ModoA1(vertice1, vertice2, g, fpOut);
        if(strcmp(modo,"B1")==0)ModoB1(vertice1,vertice2, desvio, k, g, fpOut);
        if(strcmp(modo,"C1")==0)ModoC1(vertice1,vertice2, etapa, g,fpOut);
        if(strcmp(modo,"D1")==0)ModoD1(vertice1,vertice2, etapa, g,fpOut);

        if(argv[1][1] == 'o') break;
    }
}

/*--------------------------------------------------------------------------------------------
Function: main

Arguments: argc and argv

Description: main function

Returns: 0
---------------------------------------------------------------------------------------------*/


int main(int argc, char *argv[]){
  FILE* maps, *fpout, *problems;
  GraphAdjLst mainGraph;

  char ext[]= ".routes";
  char* outFilename = malloc(strlen(argv[3]) - strlen(".maps") + strlen(ext) + 1);
  if(outFilename==NULL)exit(0);
  snprintf(outFilename, strlen(argv[3]) + 1 - strlen(".maps"), "%s", argv[3]);
  strcat(outFilename, ext);
    
  if(ReadOption(argv)!=1)exit (0);

  maps = fopen(argv[3], "r");
  if(maps == NULL) exit (0);

  fpout=fopen(outFilename,"w");
  if(fpout == NULL)exit (0);
  fprintf(fpout,"%s %s %s\n\n",argv[1], argv[2], argv[3]);

  problems = fopen(argv[2], "r");
  if(problems == NULL) exit (0);

  while(fscanf(maps,"%d %d",&mainGraph.nrVertices, &mainGraph.nrEdges)!=EOF){
  mainGraph = graphAdjLstRead(maps, mainGraph.nrVertices, mainGraph.nrEdges);
  ReadProblem(argv, mainGraph, problems, fpout);
  rewind(problems);
  graphAdjLstFree(&mainGraph);
  if(argv[1][2] == 'o') break;
  }
  
  free(outFilename); 
  fclose(maps);
  fclose(problems);
  fclose(fpout);
    
  return 0;
}