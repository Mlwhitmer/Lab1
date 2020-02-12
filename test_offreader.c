
#include <stdio.h>
#include <stdlib.h>
#include "offreader.h"

int
main(void)
{
  jmesh * mesh;

  mesh = new_jmesh(stdin);
  if (mesh == NULL)
     fprintf(stderr,"load_off_mesh failed\n");
 
  free_jmesh(mesh);
  return 0;
}
