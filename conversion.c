

#include "graphs.h"



int readGraphM(GraphM g) {
    return readGraphM_sol(g);
}



void printGraphM(GraphM g, int n) {
    int i,j;
    for (i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf("%d ",g[i][j]);
        }
        printf("\n");
    }
    //printGraphM_sol(g, n);    
}



void printGraphL(GraphL g, int n) {
    int i;
    struct edge* v;
    for(i=0 ;i<n; i++){
        v = g[i];
        printf("%d ",i);
        while(v) {
        
        printf("--> (%d,%d) ",v->dest , v->weight);
        
        v = v -> next;
        }
        printf("\n");
    }
    //printGraphL_sol(g, n);
}



void graphLtoM(GraphM gm, GraphL gl, int n) {
    int i,j,p;
    struct edge* v;
    for (i=0; i<n; i++){
        v = gl[i];
        for (j=0 ; j<n; j++){
                
                if (v && j == v->dest){ 
                    gm[i][j] = v->weight;
                    v = v->next; 
                }
                else gm[i][j] = 0;
                
            }
            
            }
    //graphLtoM_sol(gm, gl, n);
}



void graphMtoL(GraphL gl, GraphM gm, int n) {


    //graphMtoL_sol(gl, gm, n);
}



int inDegree (GraphL g, int j, int n) {
    return inDegree_sol(g, j, n);
}



int outDegree (GraphL g, int j) {
    return outDegree_sol(g, j);
}


int capacidadeL (GraphL g, int v, int n) {
    return  capacidadeL_sol (g, v, n);
}

int maxCap (GraphL g, int n) {
    return maxCap_sol (g, n);
}
