#include <stdlib.h>
#include <stdio.h>

#define NV 5

typedef struct aresta {
    int dest;
    int custo;
    struct aresta *prox;
} *LAdj, *GrafoL [NV];

typedef int GrafoM [NV][NV];

void printGraphM(GrafoM g, int n) {
    // V^2
    int i,j;
    for (i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf("%d ",g[i][j]);
        }
        printf("\n");
    }
    //printGraphM_sol(g, n);    
}



void printGraphL(GrafoL g, int n) {
    // V + A
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

void fromMat (GrafoM in, GrafoL out){
    // V^2
     int i,j;
     LAdj aux; 
     for (i=0; i<NV; i++){
         out[i] = NULL;
         for(j=NV-1; j>=0; j--){
            if (in[i][j] != 0){
               aux = malloc(sizeof(struct aresta));
               aux->dest = j;
               aux->custo = 1;
               aux->prox = out[i];
               out[i] = aux;      
            }
         }
     }
}


void inverte (GrafoL in, GrafoL out){
    // V + A
    int o;
    LAdj d, aux;

    for (o=0;o<NV;o++) out[o] = NULL;

    for (o=0;o<NV;o++){

        d = in[o];

        while (d != NULL){
            aux = malloc(sizeof(struct aresta));
            aux->dest = o;
            aux->custo = 1;
            aux->prox = out[d->dest];
            out[d->dest] = aux;
            d = d->prox;
        }

    }
}

int inDegree (GrafoL g){
    // V + A
    int ind[NV];
    int o,max=0;
    LAdj d;
    for (o=0; o<NV; o++) ind[o] = 0;
    for (o=0;o<NV;o++){
        d = g[o];
        while(d){
            ind[d->dest]++;
            d = d->prox;
        }
    }
    for (o=0; o<NV; o++){
        if (ind[o]>max) max = ind[o];
    }
    return max;
}

int colorOk (GrafoL g, int cor[]){
    // pior caso  V + A
    // melhor caso  1
    LAdj d;
    int i;
    for (i=0; i < NV; i++){
        d = g[i];
        while (d){
            if (cor[i] == cor[d->dest]) return 0;
            d = d->prox;
        }
    }
    return 1;
}

int existe (GrafoL h,int o,int d) {
    struct aresta *p;
    for (p=h[o];p;p=p->prox) {
        if (p->dest == d) return 1;  
    }
    return 0;
}

int homomorfOK (GrafoL g, GrafoL h, int f[]) {
    int i,r=1;
    struct aresta *p;
    for (i=0;r && i<9;i++) {
        for (p=g[i];r && p;p=p->prox) {
            r = existe(h,f[i],f[p->dest]);
        }
    }
    return r;
}


// 2. Travessias

int DF (GrafoL g, int or,
int v[],
int p[],
int l[]){
int i;
for (i=0; i<NV; i++) {
v[i]=0;
p[i] = -1;
l[i] = -1;
}
p[or] = -1; l[or] = 0;
return DFRec (g,or,v,p,l);
}

int DFRec (GrafoL g, int or,
int v[],
int p[],
int l[]){
int i; LAdj a;
i=1;
v[or]=-1;
for (a=g[or];
a!=NULL;
a=a->prox)
if (!v[a->dest]){
p[a->dest] = or;
l[a->dest] = 1+l[or];
i+=DFRec(g,a->dest,v,p,l);
}
v[or]=1;
return i;

int BF (GrafoL g, int or,
int v[],
int p[],
int l[]){
int i, x; LAdj a;
int q[NV], front, end;
for (i=0; i<NV; i++) {
v[i]=0;
p[i] = -1;
l[i] = -1;
}
front = end = 0;
q[end++] = or; //enqueue
v[or] = 1; p[or]=-1;l[or]=0;
i=1;
while (front != end){
x = q[front++]; //dequeue
for (a=g[x]; a!=NULL; a=a->prox)
if (!v[a->dest]){
i++;
v[a->dest]=1;
p[a->dest]=x;
l[a->dest]=1+l[x];
q[end++]=a->dest; //enqueue
}
}
return i;
}


int maisLonga(GrafoL g, int v, int p[]){
    int vis[NV], pai[NV], dist[NV];
    BF(g,v,vis,pai,dist);
    int i,m,r;
    m = v;
    for(i=0;i<NV;i++){
        if (dist[i] > dist[m]) m = i;
    }
    r = dist[m];
    i = 0;

    while(pai[m] != -1){
        p[i--] = m;
        m = pai[m];
    }
    p[i] = m;
    return r;
}

int componentes (GrafoL g, int c[]){
    int  v[NV], p[NV], l[NV], orig;
    DF(g,0,c,p,l);
    comp = 1;
    do {
        //encontrar um 0 em c[]
        for(orig=0; orig<NV && c[orig] != 0; orig++);
        if (orig < NV){
            DF(g, orig, v, p, l);
            comp++;
            for(i=0; i<NV; i++) if (v[i]) c[i] = comp;
        }
    } while(orig < NV);
    return comp;
}
