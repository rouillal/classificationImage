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

void imageToSvm (char* url,FILE* fichier){ //creation d'un histogramme de couleurs pour une image
    
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
}

void imageToFileSvm (char* url){ //creation d'un histogramme de couleurs pour une image
    FILE* fichier = fopen("../histoColor.svm","a+");
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
}

void createFileColorSvm (char* file){ //creation du fichier color.svm pour les images de val et train
    
    FILE *fileUrl = fopen (file, "r");
    FILE* fichier = fopen("../train/color.svm","a+"); //FILE* fichier = fopen("val/svm/color.svm","a+");
    
    char urlImg[TAILLE_MAX] = "";
        
    if (fileUrl != NULL ){
        while (fgets(urlImg, TAILLE_MAX, fileUrl) != NULL){
            char *url = strtok(urlImg,"\n");
            imageToSvm(url,fichier);
        }
        fclose(fileUrl);
    }else
        exit(EXIT_FAILURE);
        
    fclose(fichier);
}

void createFileColorConcept (char* ann, char* dest){ //fusion du fichier de vecteurs histogrammes et d'un fichier d'annotation pour création des fichiers.out avec SvmPredict

    FILE* fichier = fopen(dest,"a+");
    FILE* fileTrain = fopen ("../train/classificationSift/histo.svm", "r");
    FILE* fileAnn = fopen (ann, "r"); //fichier d'annotation
    
    char classe[TAILLE_MAX] = "";
    char histo[TAILLE_MAX] = "";
    
    if (fileAnn != NULL){
        while (fgets(classe, TAILLE_MAX, fileAnn) != NULL && fgets(histo, TAILLE_MAX, fileTrain) != NULL){
            char *token = strtok(classe," ");
            token = strtok(NULL, " ,\n");
            for(int i = 0 ; histo[i] ; i++)
                histo[i] = histo[i+1];
            strcat(token,histo);
            fprintf(fichier,"%s",token);
        }
        fclose(fileAnn);
        fclose(fileTrain);
    }else
        exit(EXIT_FAILURE);
    
    fclose(fichier);
}

void createFileColorTop (char *fileout, char *concept){ //conversion des fichiers .out en .top pour TrecEval
    FILE* fichier = fopen("../val/classificationSift/all_top.top","a+"); //fichier à générer
    FILE* list = fopen ("../val/list.txt", "r"); //fichier des id des images
    FILE* out = fopen (fileout, "r"); //fichier color_concept.out
    
    int cpt = 0;
    char imageId[TAILLE_MAX] = "";
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
    
    while (fgets(imageId, TAILLE_MAX, list) != NULL && fgets(imageScore, TAILLE_MAX, out) != NULL){
        char *id = strtok(imageId,".");
        char *score = strtok(imageScore," ");
        for(int i=0; i<cpt; i++)
            score = strtok(NULL, " ,\n");
        fprintf(fichier,"%s Q0 %s 0 %s R\n",concept,id,score);
    }
    fclose(list);
    fclose(out);
    fclose(fichier);
}

void createFileSampleSift (char *fileout){ //création du fichiers de samples SIFT
    FILE* fichier = fopen("../val/newSift/2010_001256.sift","a+"); //fichier à générer
    FILE* sift = fopen (fileout, "r"); //fichier sift
    
    char line[TAILLE_MAX] = "";
    
    for (int i = 0; i<3; i++)
        fgets(line, TAILLE_MAX, sift); //supprime les 3 premières lignes
    
    while (fgets(line, TAILLE_MAX, sift) != NULL){
        char *caract = strtok(line,";");
        caract = strtok(NULL, ",\n");
        char *new = malloc(strlen(caract)*sizeof(char)+1);
        int j = 0;
        for (int i = 1 ; caract[i] ; i++){
            if(caract[i] != ';')
                new[j++] = caract[i];
        }
//        for (int i=0; i<74; i++)
//            fgets(line, TAILLE_MAX, sift); //supprime 74 lignes
        fprintf(fichier,"%s\n",new);
    }
    fclose(sift);
    //fclose(fichier);
}

void createFileSiftSvm (char *filemapping){ //creation du fichier histogramme a partir des fichiers de mapping
    FILE* fichier = fopen("../val/classificationSift/histo.svm","a+"); //fichier à générer
    FILE* map = fopen (filemapping, "r"); //fichier mapping
    
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
}

void createFileFusion (int valeur){ //creation du fichier de fusion des scores de classification globaux
    char dest[50] = "../val/fusion/all_topFusion";
    char buff[10];
    sprintf(buff, "%d", valeur);
    strcat(dest,buff);
    strcat(dest,".top");
    
    FILE* fichier = fopen(dest,"a+"); //fichier à générer
    FILE* topColor = fopen ("../val/top/all_top.top", "r"); //fichier all_top.top à partir des histogrammes de couleurs
    FILE* topSift = fopen ("../val/classificationSift/all_top.top", "r"); //fichier all_top.top à partir des histogrammes sift
    
    char lineColor[TAILLE_MAX] = "";
    char lineSift[TAILLE_MAX] = "";
    char* image;
    float scoreColor,scoreSift,scoreFusion,f;
    
    f = ((float)valeur)/10.0;
    printf("%f\n",f);
    
    while (fgets(lineColor, TAILLE_MAX, topColor) != NULL && fgets(lineSift, TAILLE_MAX, topSift) != NULL){
        char *line1 = strtok(lineColor," ");
        for(int i=0; i<2; i++)
            image = strtok(NULL, " ,\n");
        for(int i=0; i<2; i++)
            scoreColor = atof(strtok(NULL, " ,\n"));
        char *line2 = strtok(lineSift," ");
        for(int i=0; i<4; i++)
            scoreSift = atof(strtok(NULL, " ,\n"));
        scoreFusion = f*scoreColor + (1-f)*scoreSift;
        
        fprintf(fichier,"%s Q0 %s 0 %f R\n",line1,image,scoreFusion);
    }
    
    fclose(topColor);
    fclose(topSift);
    fclose(fichier);
}

int main(int argc, char *argv[]){
    
    //createFileColorSvm(argv[1]); //creation du fichier color.svm pour les images de val et train
    imageToFileSvm(argv[1]);
    //createFileColorConcept(argv[1],argv[2]); //création des fichiers.out avec SvmPredict
    //createFileColorTop(argv[1],argv[2]); //conversion des fichiers .out en .top pour TrecEval
    //createFileSampleSift(argv[1]); //création du fichier d'échantillons sift
    //createFileSiftSvm(argv[1]); //creation du fichier histogramme a partir des fichiers de mapping
//    for (int i=1; i<10; i++)
//        createFileFusion(i); //creation du fichier de fusion des scores de classification globaux
    
    exit(0);
}
