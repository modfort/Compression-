#include "graph.h"
#define LIM 8.
float same_color(GLubyte *data,GLubyte *data1)
{		
	return sqrt(pow(data[0] - data1[0],2)+pow(data[1] - data1[1],2) + pow(data[2] - data1[2],2));
}

graph*  Image_To_Graph(  Image *im)
{	graph * GR = malloc(sizeof(graph));
    GR->liste = malloc(sizeof(noued)*im->sizeX *im->sizeY);
    assert(GR);
    assert(GR->liste);
    GR->sizeX = im->sizeX;
    GR->sizeY = im->sizeY;
	ulong size = GR->sizeX * GR->sizeY ;
	GR->n=size;
	assert(GR->n > 0 );
	/*
	GR.liste = malloc(sizeof(noued) * im->sizeX * im->sizeY );
	*/
	printf("je suis la \n");

	printf("size : %ld\n",GR->n);
	printf("et maintenant la\n");
	ulong j;
	
	for (ulong i = 0; i < GR->n ; i++)
	{		j = i*3;
			GR->liste[i].adj = malloc(sizeof(ulong) * 4 );
			assert(GR->liste[i].adj);
			if(i < im->sizeX)
					{				
						GR->liste[i].n 	 		 = 0;
						GR->liste[i].x = i			;
						GR->liste[i].R = im->data [j];
						GR->liste[i].G = im->data [j+1];
						GR->liste[i].B = im->data [j+2];
						if(same_color(im->data + j, im->data + j + im->sizeX * 3)<LIM)
						{	//printf("%ld , %ld",i/3 + im->sizeX);
							GR->liste[i].adj[GR->liste[i].n++] = i + im->sizeX;
						}
						if(i%im->sizeX-1>0 && same_color(im->data+j , im->data+j-3)<LIM)
						{	
							GR->liste[i].adj[GR->liste[i].n++] = i - 1;
							
						}
						if((i+1)/im->sizeY == i/im->sizeY && same_color(im->data + j, im->data + j +  3)<LIM)
							GR->liste[i].adj[GR->liste[i].n++] = i + 1;
					}
			else if(i + im->sizeX < size)
				{
						GR->liste[i].x = i 			;
						GR->liste[i].R = im->data [j]	;
						GR->liste[i].G = im->data [j+1];
						GR->liste[i].B = im->data [j+2];
						if(same_color(im->data+j,im->data + j + im->sizeX * 3 )<LIM)
						{
							GR->liste[i].adj[GR->liste[i].n++] = i +im->sizeX;
						}
						if(same_color(im->data+j,im->data + j - im->sizeX * 3 ) <LIM)
						{
							GR->liste[i].adj[GR->liste[i].n++] = i -im->sizeX;

						}
						if(i%im->sizeX-1>0 && same_color(im->data+j , im->data+j-3)<LIM)
						{	
							GR->liste[i].adj[GR->liste[i].n++] = i - 1;
							
						}
						if((i+1)/im->sizeY == i/im->sizeY && same_color(im->data + j, im->data + j +  3)<LIM)
							GR->liste[i].adj[GR->liste[i].n++] = i + 1;
				}
			else
			{
						GR->liste[i].x = i 			;
						GR->liste[i].R = im->data [j]	;
						GR->liste[i].G = im->data [j+1]; 	
						GR->liste[i].B = im->data [j+2];	
						if(same_color(im->data+j,im->data + j - im->sizeX * 3 ) <LIM)
						{
							GR->liste[i].adj[GR->liste[i].n++] = i - im->sizeX*3;
						}
						if(i%im->sizeX-1>0 && same_color(im->data+j , im->data+j-3)<LIM)
						{	
							GR->liste[i].adj[GR->liste[i].n++] = i - 1;
							
						}
						if((i+1)/im->sizeY == i/im->sizeY && same_color(im->data + j, im->data + j +  3)<LIM)
							GR->liste[i].adj[GR->liste[i].n++] = i + 1;

			}	
					
		
	}
	printf("sortie\n");
	return GR;
}

void print_Gr(graph *GR)
{	ulong cpt;
	//printf("je suis rentre\n");
	for (ulong i = 0; i < GR->n; ++i)
	{	
	//	printf("element  %ld :%ld: ",i,GR.liste[i].x );
	//	printf("%d %d %d\n mes succeseur sont :",GR.liste[i].R,GR.liste[i].B,GR.liste[i].G);
		if(GR->liste[i].n>0)
				cpt++;

	/*	for (int j = 0; j < GR.liste[i].n; ++j)
		{
			printf("%ld,",GR.liste[i].adj[j]);
		}
		printf("\n");*/
	}
	printf("la moyenne est de %f= %ld /%ld",(float)cpt/GR->n,cpt,GR->n);
}
void free_GR(graph *GR){
	if(GR)
	{	printf("liberation de la memoire\n");
		for (ulong i = 0; i < GR->n; ++i)
		{	
			free(GR->liste[i].adj);
		}
		free(GR->liste);
		printf("fin de liberation\n");
	}
	else
	{
		fprintf(stderr, "%s\n", "erreur de variable");
	}
}
// cette fonction transforme un graph en image
int Graph_To_Image(graph* gr,Image *im)
{	

	/*im->data = malloc((size_t)gr.n*3 * sizeof(GLubyte));
	if(!im->data)
	{	
		fprintf(stderr, "%s\n","erreur d'allocation memoire" );
		exit(0);
	}*/
	//print_Gr(gr);
	for (ulong i = 0; i < gr->n; ++i)
	{
		im->data[i*3]   =gr->liste[i].R;
		im->data[i*3+1] =gr->liste[i].G;
		im->data[i*3+2] =gr->liste[i].B;
	}
	printf("fini\n");
	
	return 1;
}

int Graph_To_Image2(graph *gr,Image *im)
{
	/*im->data = malloc((size_t)gr.n*3 * sizeof(GLubyte));
	if(!im->data)
	{	
		fprintf(stderr, "%s\n","erreur d'allocation memoire" );
		exit(0);
	}*/
	//print_Gr(gr);
	for (ulong i = 0; i < gr->n; ++i)
	{	if(gr->liste[i].n>0)
		{
			im->data[i*3]   =gr->liste[i].R;
			im->data[i*3+1] =gr->liste[i].G;
			im->data[i*3+2] =gr->liste[i].B;
		}
		else
		{
			im->data[i*3]  = 100;
			im->data[i*3+1]= 0;
			im->data[i*3+2]= 100;
		}
	}

	printf("fini\n");
	return 1;
}
int Graph_To_Image3(graph* gr,Image *im)
{
/*	im->data = malloc((size_t)gr.n*3 * sizeof(GLubyte));
	if(!im->data)
	{	
		fprintf(stderr, "%s\n","erreur d'allocation memoire" );
		exit(0);
	}*/
	//print_Gr(gr);
	for (ulong i = 0; i < gr->n; ++i)
	{	
		if(gr->liste[i].n==4)
		{
			im->data[i*3]   =gr->liste[i].R;
			im->data[i*3+1] =gr->liste[i].G;
			im->data[i*3+2] =gr->liste[i].B;
		}
		else
		{
			im->data[i*3]  = 0;
			im->data[i*3+1]= 0;
			im->data[i*3+2]= 0;
		}
	}

	printf("fini\n");
	return 1;
}
// cette fonction boucle sur tous les elements d'une liste d'element
// elle prend un graph et le le transforme en une liste de liste de graph
//  res est le retour de la fonction lorsqu'il s'agit de pointeur je prefere
//les passes en parametres
// elle contiendra la liste des graph convexes
// on sauvegardmae a chaque
vectUl  compos_connex(graph *gr)
{
    vectUl visite;
    visite.n = gr->n;
    visite.data = malloc(sizeof(int)*gr->n);
    assert(visite.data);
    memset(visite.data,0,gr->n*4);
   // visite.data = {0};
    ulong cpt = 1;
    for (ulong i = 0; i < gr->n ; ++i) {
        if(visite.data[i]==0)
        {
            visite.data[i]=cpt;
            for (int j = 0; j <gr->liste[i].n ; ++j) {
                recherche_connex(gr,visite,gr->liste[i].adj[j],cpt);
            }
            cpt++;
        }

    }
    printf("%ld\n",cpt);
    return  visite;
}
//cette fonction
int  recherche_connex(graph *gr, vectUl visite,ulong index,int cpt)
{
    if(visite.data[index]==0)
    {
        visite.data[index] = cpt;
        for(int i = 0;i<gr->liste[index].n;i++)
            recherche_connex(gr,visite,gr->liste[index].adj[i],cpt);
    }


    return 1;
}
/*
 * cette fonction va me permetre d'obenir un graph sans les voisin a 4 coleurs
 * */
vectUl Delete_Four(graph*gr, vectUl visite)
{   printf("cette fonction est elle bien teste;\n");
    ulong cpt = 0;
    vectUl tmp;
    for (ulong i = 0; i <gr->n ; ++i) {
        if(gr->liste[i].n<4)
            cpt++;
    }
    printf("%ld\n",cpt);
    tmp.n=cpt;
    tmp.data = malloc(sizeof(int)*cpt);
    assert(tmp.data);
    printf("on a gagne %f =%ld / %ld ",(float)cpt/gr->n,cpt,gr->n);
    cpt=0;
    for (ulong i = 0; i <gr->n ; ++i) {
        if(gr->liste[i].n<4)
         {   tmp.data[cpt] = visite.data[i];
             cpt++;
         }
    }
    return tmp;
}

void print(vectUl tab)
{
    for (ulong i = 0; i < tab.n; ++i) {
        printf("%d :",tab.data[i]);
    }
}