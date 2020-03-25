#ifndef GRAPH_H
#include "graph.h"
#endif

Image *image;//ceci est notre image de base
graph *GR;// ceci est notre graphe avec son million de noued
List * res;// ceci est notres liste de graph convexe
#define ESCAPE 27

void Keyboard(unsigned char key, int x, int y)  {
  switch(key){
  case ESCAPE :
    exit(0);                   
    break;
  default:
    fprintf(stderr, "Unused key\n");
  }
}

void Mouse(int button, int state, int x, int y) {

  switch(button){
  case GLUT_LEFT_BUTTON:
    break;
  case GLUT_MIDDLE_BUTTON:
    break;
  case GLUT_RIGHT_BUTTON:
    break;    
  }
  glutPostRedisplay();
}

int Init(char *s) {

  image = malloc(sizeof(Image));
  GR = malloc(sizeof(graph)  );
  if (image == NULL) {
    fprintf(stderr, "Out of memory\n");
    return(-1);
  }
  if(GR == NULL)
  {
    fprintf(stderr, "%s\n","Out of memory graph\n " );
    exit(0);
  }
  if(GR->n<=0)
  {
    fprintf(stderr, "%s\n","erreur  d'allocation tableau" );
    exit(0);
  }
  if (ImageLoad_PPM(s, image, GR)==-1) 
	return(-1);
  printf("tailles %d %d\n",(int) image->sizeX, (int) image->sizeY);

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glutReshapeWindow(image->sizeX, image->sizeY);
  
  return (0);
}

int ReInit() {

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glutReshapeWindow(image->sizeX, image->sizeY);
  
  return (0);
}

void Display(void) {
  
 // GLint w, h;

  glClear(GL_COLOR_BUFFER_BIT);

  //w = glutGet(GLUT_WINDOW_WIDTH);
 // h = glutGet(GLUT_WINDOW_HEIGHT);
  glDrawPixels(image->sizeX, image->sizeY, GL_RGB, GL_UNSIGNED_BYTE, 
	       image->data);

  glFlush();
}

void Reshape(int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble)h);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void menuFunc(int item) {


  switch(item){
  case 0:
    free(image);
    free_GR(GR);
    exit(0);
    break;
  case 1:
  case 2:
     Image_To_Graph( GR, image );
     print_Gr(GR);
     Graph_To_Image3(GR,image);
     
     printf("reussi\n");
   
    break;
  case 3:
    
     Image_To_Graph(GR, image );
     print_Gr(GR);
     Graph_To_Image2(GR,image);
     
     printf("reussi\n");
     
    break;

  case 6:
     
     // Graph_To_Image( GR, image);
   Image_To_Graph(GR, image );
     print_Gr(GR);
     Graph_To_Image(GR,image);
          printf("reussi\n");
          compos_connex(GR,res);

    break;

  default:
    break;
  }
}

int main(int argc, char **argv) {  

  if (argc<2) {
    fprintf(stderr, "Usage : palette nom_de_fichier\n");
    exit(0);
  }

  glutInit(&argc, argv); 
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(640,480);  
  glutInitWindowPosition(100, 100);  
  glutCreateWindow("VPUP8");  

  Init(argv[1]);

  glutCreateMenu(menuFunc);
  glutAddMenuEntry("Quit", 0);
  glutAddMenuEntry("image3", 2);
  glutAddMenuEntry("image2", 3);
  glutAddMenuEntry("image", 6);
  glutAttachMenu(GLUT_LEFT_BUTTON);
  glutDisplayFunc(Display);  
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(Keyboard);
  
  glutMouseFunc(Mouse);

  glutMainLoop();  

  return 1;
}