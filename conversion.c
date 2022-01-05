


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
    int i,j;
    struct edge *new, *head;
    for(i=0; i<n; i++){
        head = NULL;
        for(j=n-1; j>=0; j--){
            if(gm[i][j] != NE){
                new = malloc(sizeof(struct edge));
                new -> weight = gm[i][j];
                new -> dest = j;
                new -> next = head; 
                head = new;
            }
            gl[i] = new;
        }
    }
    //graphMtoL_sol(gl, gm, n);
}



int inDegree (GraphL g, int j, int n) {
    struct edge * v;
    int i, count=0;
    for (i=0; i<n; i++){
        v = g[i];
        while(v){
        if (v->dest == j) {
            count++;
        }
        v = v -> next;
        }
    }
    return count;
}



int outDegree (GraphL g, int j) {
    struct edge * v;
    v = g[j];
    int count = 0;
    while (v){
        if (v->dest != 0) count++;
        v = v->next;
    }
    return count;
    //return outDegree_sol(g, j);
}


int capacidadeL (GraphL g, int v, int n) {
    struct edge * f;
    int count = 0;
    f = g[v];
    for(i=0; i<n; i++){
      for(f=g[i]; p; p = p->next){
       if(i==v) {
           count -= f->weight;
       }
       else if (v == f->dest) count += f->weight;
   }
}
  return count;
}


int maxCap (GraphL g, int n) {
    int i, max, aux, aux2 = 0;
    max = capacidadeL(g,0,n);
    for (i=1; i<n; i++){
        aux = capacidade(g,i,n);
        if (aux > max) {
            max = aux;
            aux2 = i;
        }
    }
    return aux2;
}
