/* il s agit de prendre une image et de la modifier */
#ifndef IMA_H
#include "ima.h"
#endif
#include <limits.h>
void gris_uniforme(Image * i) {
  int j, size;
  GLubyte * im, val ;
  val = 128 ;
  size = 3 * i->sizeY * i->sizeX ;
  im = i->data;
  for (j = 0; j < size; j ++) 
	*im++ = val;
  
}

