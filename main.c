#ifndef GRAPH_H
#include "graph.h"
#endif

Image *image;//ceci est notre image de base
graph *GR;// ceci est notre graphe avec son million de noued
vectUl res;// ceci est notres liste de graph convexe.
char s[100] ;//copie pour recharger l'image
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

int Init(char *sa) {

  image = malloc(sizeof(Image));
  assert(image);

  if (image == NULL) {
    fprintf(stderr, "Out of memory\n");
    return(-1);
  }

  if (ImageLoad_PPM(s, image)==-1)
	return(-1);
  printf("tailles %d %d\n",(int) image->sizeX, (int) image->sizeY);
    GR=Image_To_Graph( image );
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

      // Graph_To_Image( GR, image);

          Graph_To_Image(GR,image);
          printf("reussi\n");
          res= compos_connex(GR);
         res= Delete_Four(GR,res);
        //    print(res);
          break;

      case 2:

     Graph_To_Image2(GR,image);
     
     printf("reussi\n");
   
    break;
  case 3:

     Graph_To_Image3(GR,image);
     printf("reussi\n");
     
    break;
      case 4:
          Init("de");
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
  strcpy(s,argv[1]);
  glutInit(&argc, argv); 
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(640,480);  
  glutInitWindowPosition(100, 100);  
  glutCreateWindow("VPUP8");  

  Init(argv[1]);

  glutCreateMenu(menuFunc);
  glutAddMenuEntry("Quit", 0);
    glutAddMenuEntry("image", 1);
    glutAddMenuEntry("image2", 2);
   glutAddMenuEntry("image3", 3);
    glutAddMenuEntry("reload", 4);
  glutAttachMenu(GLUT_LEFT_BUTTON);
  glutDisplayFunc(Display);  
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(Keyboard);
  
  glutMouseFunc(Mouse);

  glutMainLoop();  

  return 1;
}