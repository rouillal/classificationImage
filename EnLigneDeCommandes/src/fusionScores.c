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

int main(int argc, char *argv[]){ //creation du fichier de fusion des scores de classification globaux

    FILE* fichier = fopen("../test/resFinal.txt","a+"); //fichier à générer
    FILE* resColor = fopen ("../test/res2.txt", "r"); //fichier res2 à partir des histogrammes de couleurs
    FILE* resSift = fopen ("../test/res1.txt", "r"); //fichier res1 à partir des histogrammes sift
    
    char lineColor[TAILLE_MAX] = "";
    char lineSift[TAILLE_MAX] = "";
    char* concept;
    float scoreColor,scoreSift,scoreFusion,f;

    while (fgets(lineColor, TAILLE_MAX, resColor) != NULL && fgets(lineSift, TAILLE_MAX, resSift) != NULL){
        scoreColor = atof(strtok(lineColor," "));
        concept = strtok(NULL, " ,\n");
        scoreSift = atof(strtok(lineSift," "));
        scoreFusion = 0.4*scoreColor + 0.6*scoreSift;
        
        fprintf(fichier,"%f %s\n",scoreFusion,concept);
    }
    
    fclose(resColor);
    fclose(resSift);
    fclose(fichier);
    exit(0);
}
