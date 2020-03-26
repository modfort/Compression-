
#ifndef LISTE_H
#include "liste.h"
#endif

int Image_To_Graph(graph* ,Image *);
int Graph_To_Image(graph *,Image *);
int Graph_To_Image2(graph *,Image *);
int Graph_To_Image3(graph *,Image *);
float same_color(GLubyte *,GLubyte *);
void print_Gr(graph *);
int  recherche_connex(graph *, noued , Listgr*,Listgr *);
List*  compos_connex(graph * );
void free_GR(graph*);