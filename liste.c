#ifndef LISTE_H
#include "liste.h"
#endif
// pour les liste de noued
Listgr* init_Lgr( noued* data)
{
    Listgr* tete  = malloc(sizeof(Listgr));
    assert(tete);
    tete->data = data;
    tete->next = NULL;
    return tete;
}

int find_Lgr(Listgr*tete,noued *data)
{
    if(!tete)
    {
        return -1;
    }
    while(tete)
    {
        if(tete->data->x == data->x)
            return 1;
        tete = tete->next;
    }
    return 0;
}

void add_Lgr(Listgr *tete,noued *data)
{   if(!tete)
    {
        fprintf(stderr,"%s\n","erreur d'allocation");
        return;
    }
    Listgr *tmp = tete;
    while(tmp->next)
    {
        tmp = tmp->next;
    }
    Listgr * suiv;
    suiv = malloc(sizeof(Listgr));
    assert(suiv);
    suiv->data = data;
    tmp->next = suiv;
}
void free_Lgr(Listgr *tete)
{
    if(!tete)
        return ;
    free_Lgr(tete->next);
    free(tete);
}


// pour les liste de liste de graph


List* init_L(Listgr *data)
{
    List*tete = malloc(sizeof(List));
    assert(tete);
    tete->next = NULL;
    tete->data = data;
    return tete;
}

void add_L(List *tete,Listgr *data)
{   if(!tete)
    {
        fprintf(stderr,"%s\n","erreur d'allocation");
        return;
    }

    List* tmp = tete;
    while(tmp->next)
    {
        tmp = tmp->next;
    }
    List * suiv;
    suiv = malloc(sizeof(List));
    suiv->data = data;
    tmp->next = suiv;
}

void free_L(List *tete)
{
    if(!tete)
        return ;
    free_L(tete->next);
    free_Lgr(tete->data);
    free_L(tete);
}
