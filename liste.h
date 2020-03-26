#ifndef IMA_H
#include "ima.h"
#endif


Listgr* init_Lgr( noued* data);
int find_Lgr(Listgr*tete, noued* data);
Listgr* add_Lgr(Listgr *tete, noued* data);
void free_Lgr(Listgr *tete);
List* init_L(Listgr *data);
List* add_L(List *tete, Listgr *data);
void free_L(List *tete);