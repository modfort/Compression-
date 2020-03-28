#ifndef GRAPH_H
#include "graph.h"
#endif

vectUl  compos_connex(graph *);
int  recherche_connex(graph *gr, vectUl *visite,ulong index,int cpt);
vectUl Delete_Four(graph*gr, vectUl visite);
void Compress(graph*gr,vectUl tab , Image *im ) ;
Image* UNcompress1( );
void print(vectUl tab);
