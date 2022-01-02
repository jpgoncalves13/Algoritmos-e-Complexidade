#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "hashing.h"


int hash(char key[], int size) {
    
    int i=0, sum=0;
    while(key[i] != '\0') sum += key[i++];
    
    return (sum % size);
}


void initHT(HT *h, int size) {
    h->size = size;
    h->used = 0;
    h->tbl = calloc(size,sizeof(struct pair));
    int i;
    for (i = 0; i < size; i++){
        strcpy(h->tbl[i].key,EMPTY);
    }
}


int freeHT(HT *h, int k) {
    if (strcmp((h->tbl)[k].key, EMPTY)==0) return 1;
    if (strcmp((h->tbl)[k].key, DELETED)==0) return 1;
    return 0;
}



void writeHT (HT *h, char key[], int value) {
    int i, j=0, value2;
    float load = h->used / h->size;
    
    if (load > 0.8) {
       HT *ht;
       initHT(ht,2*h->size);
       while(j<h->size){
           value2 = hash(h->tbl[j].key,2 * h->size);
           writeHT(ht,h->tbl[j].key,value2);
           j++;
       }
      h = ht;
    }

    i = hash(key, h->size);
    
    while (!freeHT(h, i)) {
        i = (i+1)%(h->size);
        printf("* ");
    }
    
    strcpy((h->tbl)[i].key, key);
    (h->tbl)[i].value = value;
    h->used++;
    
   // return i;
   // return writeHT_sol (h, key, value);
}



int readHT (HT *h, char key[], int* value) {
     int i, ii;
    i = ii = hash(key, h->size);

    while (strcmp((h->tbl)[i].key, key) != 0) {
        if (strcmp((h->tbl)[i].key, EMPTY) == 0) return -1;
        i = (i+1)%(h->size); printf("* ");
        if (i == ii) return -1;
    }

    *value = (h->tbl)[i].value;
    return i;
    //return readHT_sol (h, key, value);
}



int deleteHT (HT *h, char key[]) {
    int j;
    int i = readHT(h,key,&j);
    if (i >= 0){
        strcpy(h->tbl[i].key,DELETED);
        h->used--;
    }
    return i;
    //return deleteHT_sol (h, key);
}


int main(int argc, const char * argv[]) {

    HT h;
    int i, r, v;
    char* characters[] = {"Akamaru", "Sai", "Yamata", "Itachi", "Gaara", 
    "Hinata", "Sasuke", "Naruto", "Sakura", "Kakashi", "Gae"};
    
    initHT(&h, 11);

    // Inserts all except last element in characters
    printf("** INSERTIONS **\n");
    for (i=0; i<10; i++) {
        writeHT(&h, characters[i], strlen(characters[i]));
        printf("%s inserted\n", characters[i]);
    }

    // Looks up all elements in characters
    printf("**  LOOKUPS **\n");
    for (i=0; i<=10; i++) {
        r = readHT(&h, characters[i], &v);
        if (r>=0) printf("(%8s, %d ) at index %d\n", characters[i], v, r);
        else printf("%s not found\n", characters[i]);
    }
    
    //  Deletes elements in even positions of characters
    printf("** REMOVALS **\n");
    for (i=0; i<=10; i+=2) {
        r = deleteHT(&h, characters[i]);
        if (r>=0) printf("%s deleted\n", characters[i]);
        else printf("%s not found\n", characters[i]);
    }

    printf("** DUMP: **\n");
    for (i=0; i<h.size; i++)
        printf("%s, %d\n", (h.tbl)[i].key, (h.tbl)[i].value);
    
    // Inserts elements that have been removed
    printf("** REINSERTIONS **\n");
    for (i=0; i<=10; i+=2) {
        writeHT(&h, characters[i], i);
        printf("%s inserted\n", characters[i]);
    }


    return 0;
}
