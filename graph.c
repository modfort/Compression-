#include "graph.h"
#define LIM 15.0 // dois toujours etre inferieur a 15
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

	ulong j;
	
	for (int i = 0; i < GR->n ; i++)
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
						{
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

	return GR;
}

void print_Gr(graph *GR)
{	ulong cpt;

	for (int i = 0; i < GR->n; ++i)
	{	
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
		for (int i = 0; i < GR->n; ++i)
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
	return 1;
}
