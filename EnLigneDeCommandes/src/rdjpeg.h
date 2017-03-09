#include <stdio.h>
#include <malloc/malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct {        /* image couleur         */
    int nx;             /* taille horizontale    */
    int ny;             /* taille verticale      */
    unsigned char **r;  /* plan de couleur rouge */
    unsigned char **g;  /* plan de couleur verte */
    unsigned char **b;  /* plan de couleur bleue */
} CIMAGE;

void read_cimage(char *name, CIMAGE *cim);
void free_cimage(char *name, CIMAGE *cim);
