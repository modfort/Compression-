#ifndef IMA_H
#include "ima.h"
#endif


void init_Lgr(Listgr*tete, noued* data);
int find_Lgr(Listgr*tete,noued* data);
void add_Lgr(Listgr *tete,noued* data);
void free_Lgr(Listgr *tete);
void init_L(List*tete,Listgr *data);
void add_L(List *tete,Listgr *data);
void free_L(List *tete);