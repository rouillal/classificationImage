#include "rdjpeg.h"

void read_cimage(char *name, CIMAGE *cim)
{
  /*-----------------------------*/
  /* lecture d'une image couleur */
  /*-----------------------------*/
  int i,j,nx,ny,nc;
  unsigned char **r,**g,**b;
  char *command,head[4];
  FILE *fp;
  /*-------------------------------------------------*/
  /* commande conversion vers le format PPM          */
  /* djpeg envoie le résultat sur la sortie standard */  
  /*-------------------------------------------------*/  
  if (strstr(name,"http://") == name) {
    asprintf(&command,"wget -O - \"%s\" -o /dev/null | djpeg ",name);
  } else {
    asprintf(&command,"djpeg \"%s\"",name);
  }
  /*-----------------------------------*/
  /* lecture d'une image au format PPM */
  /*-----------------------------------*/
  if ((fp = popen(command,"r")) == NULL) {
    fprintf(stderr,"Can't open PBM file from \"%s\" command, exiting",command);
    exit(1);
  }
  free(command);
  fscanf(fp,"%s\n%d %d\n%d\n",head,&nx,&ny,&nc);
  (*cim).nx = nx;
  (*cim).ny = ny;
  (*cim).r = r = (unsigned char **) malloc(nx*sizeof(unsigned char *));
  (*cim).g = g = (unsigned char **) malloc(nx*sizeof(unsigned char *));
  (*cim).b = b = (unsigned char **) malloc(nx*sizeof(unsigned char *));
  r[0] = (unsigned char *) malloc(nx*ny*sizeof(unsigned char));
  g[0] = (unsigned char *) malloc(nx*ny*sizeof(unsigned char));
  b[0] = (unsigned char *) malloc(nx*ny*sizeof(unsigned char));
  for (i = 1; i < nx; i++) {
    r[i] = r[i-1]+ny;
    g[i] = g[i-1]+ny;
    b[i] = b[i-1]+ny;
  }
  if (!strcmp(head,"P6")) { /* image couleur */
    for (j = 0; j < ny; j++) {
      for (i = 0; i < nx; i++) {
        r[i][j] = (unsigned char) getc(fp);
        g[i][j] = (unsigned char) getc(fp);
        b[i][j] = (unsigned char) getc(fp);
      }
    }
  } else if (!strcmp(head,"P5")) { /* image noir et blanc */
    for (j = 0; j < ny; j++) {
      for (i = 0; i < nx; i++) {
        r[i][j] = g[i][j] = b[i][j] = (unsigned char) getc(fp);
      }
    }
  } else { /* format non supporté */
    exit(1);
  }
  pclose(fp);
}

void free_cimage(char *name, CIMAGE *cim)
{
  free(*(cim->r));
  free(*(cim->g));
  free(*(cim->b));
  free(cim->r);
  free(cim->g);
  free(cim->b);
}
