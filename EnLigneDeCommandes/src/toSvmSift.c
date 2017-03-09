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

int main(int argc, char *argv[]){

    FILE* fichier = fopen("../test/histoSift.svm","a+"); //fichier à générer
    FILE* map = fopen ("../test/res1nn.txt", "r"); //fichier mapping
    
    char line[TAILLE_MAX] = "";
    int cpt = 0;
    int tab[TAILLE_MAX][2];
    
    int ok = 0;
    int j = 0;
    int temp1 = 0;
    int temp2 = 0;
    
    while (fgets(line, TAILLE_MAX, map) != NULL){
        ok = 0;
        for (int i = 0; i<j; i++){
            if (tab[i][0] == atoi(line)){
                tab[i][1] = tab[i][1]+1;
                ok = 1;
            }
        }
        if (!ok) {
            tab[j][0] = atoi(line);
            tab[j][1] = 1;
            j++;
        }
        cpt++;
    }
    for(int k = 0; k<j-1; k++){ //tri par odre croissant
        for(int i=0; i<j-1; i++){
            if(tab[i][0]>tab[i+1][0]){
                temp1=tab[i][0];
                temp2=tab[i][1];
                tab[i][0]=tab[i+1][0];
                tab[i][1]=tab[i+1][1];
                tab[i+1][0]=temp1;
                tab[i+1][1]=temp2;
                temp1=0;
                temp2=0;
            }
        }
    }

    fprintf(fichier,"0");
    for (int i = 0; i<j; i++){
        fprintf(fichier," %d:%f",tab[i][0],((float)tab[i][1])/((float)cpt));
    }
    fprintf(fichier,"\n");
    fclose(map);
    fclose(fichier);

    exit(0);
}
