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

int main(int argc, char *argv[]){ //scores de classification par concepts

    char *fileout = argv[1];
	char *concept = argv[2];
    char *dest = argv[3];
	FILE* fichier = fopen(dest,"a+"); //fichier à générer
    FILE* out = fopen (fileout, "r"); //fichier color_concept.out
    
    int cpt = 0;
    char imageScore[TAILLE_MAX] = "";
    fgets(imageScore, TAILLE_MAX, out);
    int ok = 0;
    char *classe = strtok(imageScore," ");
    classe = strtok(NULL, " ,\n");
    
    while( classe != NULL && ok == 0){
        if (atoi(classe) == 1){
            ok = 1;
        }
        cpt++;
        classe = strtok(NULL, " ,\n");
    }
    
    while (fgets(imageScore, TAILLE_MAX, out) != NULL){
        char *score = strtok(imageScore," ");
        for(int i=0; i<cpt; i++)
            score = strtok(NULL, " ,\n");
        fprintf(fichier,"%s %s\n",score,concept);
    }
    fclose(out);
    fclose(fichier);

    exit(0);
}
