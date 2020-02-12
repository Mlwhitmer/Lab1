/* utils.c */
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glut.h>
#include "utils.h"

static graphics_state * current_gs;

void print_howto(void){
  printf("\nCommands\n");
  printf("q:       Exit Program\n");
  printf("s:       Save Display to .ppm\n");
}

void set_gs(graphics_state * gs){
  current_gs = gs;
}

void init(graphics_state * gs){
  current_gs = gs;
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
}

void 
reshape(int w, int h){

}

void 
mouse_handler(int button, int button_state, int x, int y){
  
}

void 
trackMotion(int x, int y) {

}

void keys(unsigned char c, int x, int y) {
  switch (c){
    case 'q':
      exit(0);
      break;
    case 's':
      read_to_ppm();
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

void read_to_ppm(){
  printf("\nSaving image.ppm to current directory...\n");

  int dimx = glutGet(GLUT_WINDOW_WIDTH);
  int dimy = glutGet(GLUT_WINDOW_HEIGHT);
  size_t imsize = 3*dimx*dimy;
  char *pixels = (char*) malloc(imsize*sizeof(char));
  char *pixels_t = (char*) malloc(imsize*sizeof(char));

  glReadPixels(0, 0, dimx, dimy, GL_RGB, GL_UNSIGNED_BYTE, pixels);

  int i, k = 0;
  for(i = imsize-3; i >= 0; i-=3){
    pixels_t[k + 0] = pixels[i + 0];
    pixels_t[k + 1] = pixels[i + 1];
    pixels_t[k + 2] = pixels[i + 2];
    k+=3;
  }

  FILE *fp = fopen("image.ppm", "wb");
  fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);
  fwrite(pixels_t, sizeof(char), imsize, fp);
  fclose(fp);

  free(pixels);
  free(pixels_t);
  printf("image.ppm saved!\n\n");


  return;
}
