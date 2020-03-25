
#ifndef LISTE_H
#include "liste.h"
#endif

int Image_To_Graph(graph* ,Image *im);
int Graph_To_Image(graph *,Image *im);
int Graph_To_Image2(graph *,Image *im);
int Graph_To_Image3(graph *,Image *im);
float same_color(GLubyte *data,GLubyte *data1);
void print_Gr(graph *GR);
int  recherche_connex(graph *gr, noued data, Listgr*visite,Listgr *courant);
int  compos_connex(graph *gr,List *res );
void free_GR(graph*);