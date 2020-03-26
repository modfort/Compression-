
#ifndef LISTE_H
#include "liste.h"
#endif

graph* Image_To_Graph(Image *);
int Graph_To_Image(graph *,Image *);
int Graph_To_Image2(graph *,Image *);
int Graph_To_Image3(graph *,Image *);
float same_color(GLubyte *,GLubyte *);
void print_Gr(graph *);
int  recherche_connex(graph *, vectUl , ulong,int);
vectUl  compos_connex(graph * );
void print(vectUl);
vectUl Delete_Four(graph*gr, vectUl visite);
void free_GR(graph*);