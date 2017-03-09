#include <stdio.h>
#include <malloc/malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "rdjpeg.h"

#define R_BIN 4
#define G_BIN 4
#define B_BIN 4

#define TAILLE_MAX 5000

int main(int argc, char *argv[]){ //creation d'un histogramme de couleurs pour une image au format svm

	char* url = argv[1];
    FILE* fichier = fopen("test/histoColor.svm","w+");
    double hist[R_BIN*G_BIN*B_BIN];
    int ir, ig, ib;
    int i,j,k,n,nx,ny,nb;
    CIMAGE cim;
    for (k = 0; k < R_BIN*G_BIN*B_BIN; k++)
        hist[k] = 0;
    read_cimage(url,&cim);
    for (j = 0; j < cim.ny; j++) {
        for (i = 0; i < cim.nx; i++) {
            ir = (cim.r[i][j] * R_BIN) / 256;
            ig = (cim.g[i][j] * G_BIN) / 256;
            ib = (cim.b[i][j] * B_BIN) / 256;
            hist[ir + ig * R_BIN + ib * R_BIN * G_BIN] += 1;
        }
    }
    for (k = 0; k < R_BIN*G_BIN*B_BIN; k++){
        hist[k] = hist[k]/(cim.nx * cim.ny);
    }
    fprintf(fichier,"0");
    for (k = 0; k < R_BIN*G_BIN*B_BIN; k++){
        if (hist[k] != 0)
            fprintf(fichier," %d:%f",(k+1),hist[k]);
    }
    fprintf(fichier,"\n");
    free_cimage(url,&cim);

    exit(0);
}

