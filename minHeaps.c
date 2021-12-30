
#include <stdlib.h>

#include "minheap.h"



void initHeap (Heap *h, int size) {
    h->values = calloc(size,sizeof(Elem));
    h->size = size;
    h->used = 0;
   // initHeap_sol (h, size);
}



void bubbleUp (Elem h[], int i) {
    if (i != 0){
    if (h[PARENT(i)] > h[i]) {
        swap(h,i,PARENT(i));
        i = PARENT(i);
        bubbleUp(h,i);   
    }
    }
}



int  insertHeap (Heap *h, Elem x) {
        if (h->used == h->size){
           h->size = 2 * h->size;
           h->values = realloc(h->values,sizeof(Elem) * h->size);
        }
        h->values[h->used] = x;
        h->used++;
        bubbleUp(h->values,h->used-1);
        
    return 1;
    
   // return insertHeap_sol (h, x);
}

int isEmpty (Heap *h){
    if (h->used == 0) return 1;
    return 0;
}

void bubbleDown (Elem h[], int N) {
     int i=0,min;
     while (LEFT(i) < N){ 
         min = LEFT(i);
     if (RIGHT(i) < N && h[RIGHT(i)] < h[min]) min = RIGHT(i);
     if (h[min] >= h[i]) break;
       swap(h,i,min);
       i = min;
     }
     
}



int  extractMin (Heap *h, Elem *x) {
    if (h->used == 0);
    else {
    *x = h->values[0];
    h->values[0] = h->values[h->used-1];
    h->used--;
    bubbleDown_sol(h->values,h->used);
    return 1;
    }
    return 0;
    //return extractMin_sol (h, x);
}



int minHeapOK (Heap h) {
    if (h.used == 0) return 0;
    else if (h.values[PARENT(h.used-1)] < h.values[h.used-1]) {
        h.used--;
        minHeapOK(h); 
        return 1;
    }
    return 0;
}


int main()
{

    Heap h;
    int i, x;

    initHeap(&h, 1);
    
    insertHeap(&h, 30);
    insertHeap(&h, 60);
    insertHeap(&h, 40);
    insertHeap(&h, 10);
    insertHeap(&h, 100);
    insertHeap(&h, 20);
    insertHeap(&h, 90);
    insertHeap(&h, 50);
    insertHeap(&h, 80);
    insertHeap(&h, 70);
    
    printf("%d\n",minHeapOK(h));
  
    printf("Heap construída (capacidade %d):\n", h.size);
    for (i = 0; i < h.used; i++)
        printf("%d\n", h.values[i]);

    printf("Extracção de elementos:\n");
    while (extractMin(&h, &x)) 
        printf("%d\n", x);
    
}
