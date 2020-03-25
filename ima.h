#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>
#include <GL/glut.h>
#include <GL/glu.h>	
#include <GL/gl.h>	
#include <unistd.h>     
#include <math.h>

typedef struct noued noued;
// cette structure represente un arret du graphe il contient sa position x
// sa couleur au format rgb
// le nombre d'element
struct noued{
	ulong x;
	GLubyte R , G ,B;
	int n;
	ulong  *adj;
};

typedef struct Graph{
	ulong sizeX , sizeY   ;
    ulong 			n     ;
    noued *         liste ;
}graph;
typedef unsigned long ulong;
typedef struct Listgr Listgr;
struct Listgr{
	noued *data ;
	Listgr * next ;
};
typedef struct List List ;
 struct List {
    Listgr *data;
    List * next;
};
struct Image {
    ulong sizeX;
    ulong sizeY;
    GLubyte *data;
};


typedef struct Image Image;
typedef unsigned short utab [3][3][3];

int ImageLoad_PPM(char *filename, Image *image, graph*);
void imagesave_PPM(char *filename, Image *image);
/*
void floattoint3(float, float, float, int *, int *, int *);
void inttofloat3(int, int, int, float *, float *, float*);
void rgbtohls(float, float, float, float *, float *, float *);
void hlstorgb(float, float, float, float *, float *, float *);
void modifclr(GLubyte *, GLubyte *, int);
void dlr27(Image *), dlr54(Image *), dlr27fs(Image *);
*/

void gris_uniforme (Image *);
/*void untrait (Image *), untraitOK (Image *);
void moserr (Image *), mosprox(Image *);
Image * try2  (Image *);
Image * toclut  (Image *);
*/