#include "connex.h"
#define VAL 255
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
    printf("je suis arrive a la boucle \n");
    for (ulong i = 0; i < gr->n ; ++i) {
        //  printf("%d \n",i);
        if(visite.data[i]==0)
        {
            visite.data[i]=cpt;
            for (int j = 0; j <gr->liste[i].n ; ++j) {
                recherche_connex(gr,&visite,gr->liste[i].adj[j],cpt);
            }
            cpt++;
        }

    }
    printf("%ld\n",cpt);
    printf("je suis sortie d'ci");
    return  visite;
}
//cette fonction
int  recherche_connex(graph *gr, vectUl *visite,ulong index,int cpt)
{
    if(visite->data[index]==0)
    {
        visite->data[index] = cpt;
        for(int i = 0;i<gr->liste[index].n;i++)
            recherche_connex(gr,visite,gr->liste[index].adj[i],cpt);
    }


    return 1;
}
/*
 * cette fonction va me permetre d'obenir un graph sans les voisin a 4 coleurs
 * */
vectUl Delete_Four(graph*gr, vectUl visite)
{
    printf("cette fonction est elle bien teste;\n");
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
        {   tmp.data[cpt] = gr->liste[i].x;
            cpt++;
        }
    }
    return tmp;

}
/*
 * cette avec cette fonction que je dois generer un fichier compresser
 * */
void Compress(graph*gr,vectUl tab , Image *im ) {

    memset(im->data, VAL, gr->n * 3);
    FILE *fichier = fopen("compress.txt", "w");
    if(fichier==NULL)
    {
        fprintf(stderr,"%s\n","impossible d'ecire dans un fichier ");
        return ;
    }
    fprintf(fichier,"%d %d ",im->sizeX,im->sizeY);
    for (ulong i = 0; i < tab.n; ++i) {
        im->data[tab.data[i] * 3] = gr->liste[tab.data[i]].R;
        im->data[tab.data[i] * 3 + 1] = gr->liste[tab.data[i]].G;
        im->data[tab.data[i] * 3 + 2] = gr->liste[tab.data[i]].B;
        fprintf(fichier,"%d %d %d %d ",tab.data[i],gr->liste[tab.data[i]].R,gr->liste[tab.data[i]].G,gr->liste[tab.data[i]].B);
    }
    fclose(fichier);
}
Image* UNcompress1(graph*gr,vectUl tab )
{
    uint j;
    FILE*fichier = fopen("compress.txt", "r");
    GLubyte R , G , B;
    uint pos;
    if(fichier==NULL)
    {
        fprintf(stderr,"%s\n","fichier non trouve\n");
        return (Image*)NULL;
    }
    Image*img=malloc(sizeof(Image));
    if (fscanf(fichier, "%lu %lu", &img->sizeX, &img->sizeY) != 2) {
        fprintf(stderr,"%s", "Invalid image size (error loading '%s')\n");
        exit(1);
    }
    uint size = img->sizeY*img->sizeX*3;
    img->data = malloc ((size_t) size * sizeof (GLubyte));
    memset(img->data,VAL,size);

    while(fichier!=NULL)
    {
        fscanf(fichier,"%d %hhd %hhd %hhd",&pos,&R,&G,&B);
        img->data[pos*3]=R;
        img->data[pos*3+1]=G;
        img->data[pos*3+2]=B;
    }
    fclose(fichier);
    for(ulong i = 0 ; i < size;i++)
    {
        j = i * 3;
       if(img->data[j]!=VAL)
      {  if(i < img->sizeX)
        {
            printf("je teste la %d\n",img->data[j+img->sizeX*3]);
            if(img->data[j+img->sizeX*3] == VAL)
            {
                //printf("%ld , %ld",i/3 + im->sizeX*3);
                img->data[j+img->sizeX*3]   = img->data[j] ;
                img->data[j+img->sizeX*3+1] = img->data[j+1] ;
                img->data[j+img->sizeX*3+2] =img->data[j+2];
            }
            if(i%img->sizeX-1>0 && img->data[j-3] == VAL)
            {printf("%ld , %ld",i/3 + img->sizeX*3);
                img->data[j-3] = img->data[j];
                img->data[j-2] = img->data[j+1];
                img->data[j-1] = img->data[j+2];

            }
            if((i+1)/img->sizeY == i/img->sizeY && img->data[j+3] == VAL)
            {

                img->data[j+3] = img->data[j];
                img->data[j+2] = img->data[j];
                img->data[j+1] = img->data[j];


            }
        }
        else if(i + img->sizeX < size)
        {

            if(img->data[j+img->sizeX*3] == VAL)
            {	//printf("%ld , %ld",i/3 + im->sizeX*3);
                img->data[j+img->sizeX*3] = img->data[j];
                img->data[j+img->sizeX*3+1] = img->data[j+1];
                img->data[j+img->sizeX*3+2] = img->data[j+2];
            }
            if(img->data[j-img->sizeX*3] == VAL)
            {   img->data[j-img->sizeX*3] = img->data[j];
                img->data[j-img->sizeX*3+1] = img->data[j+1];
                img->data[j-img->sizeX*3+2] = img->data[j+2];
            }
            if(i%img->sizeX*3-1L>0 && img->data[j-3] == VAL)
            {printf("je suis dans uncompress");
                img->data[j-3] = img->data[j];
                img->data[j-2] = img->data[j+1];
                img->data[j-1] = img->data[j+2];

            }
            if((i+1)/img->sizeY == i/img->sizeY && img->data[j+3] == VAL)
            {
                printf("je suis dans uncompress");
                img->data[j+5] =img->data[j];
                img->data[j+4] = img->data[j];
                img->data[j+3] = img->data[j];


            }
        }
        else
        {

            if(img->data[j-img->sizeX*3] == VAL)
            {  printf("je suis dans uncompress");
                img->data[j-img->sizeX*3] = img->data[j];
                img->data[j-img->sizeX*3+1] = img->data[j+1];
                img->data[j-img->sizeX*3+2] = img->data[j+2];
            }
            if(i%img->sizeX-1>0 && img->data[j-3] == VAL)
            {
                printf("je suis dans uncompress");
                img->data[j-3] = img->data[j];
                img->data[j-2] =img->data[j];
                img->data[j-1] = img->data[j];

            }
            if((i+1)/img->sizeY == i/img->sizeY && img->data[j+3] == VAL)
            {   printf("je suis dans uncompress");
                img->data[j+3] = img->data[j];
                img->data[j+4] =img->data[j+1];
                img->data[j+5] = img->data[j+2];


            }

        }
}
    }
    return img;

}

//void complete_im
void print(vectUl tab)
{
    for (uint i = 0; i < tab.n; ++i) {
        printf("%d :",tab.data[i]);
        if(i%10)
            printf("\n");
    }
}