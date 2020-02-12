#include <stdio.h>

typedef struct Mesh{
    int nvert;
    int ntri;
    float *vertices;
    float *normals;
    int *triangles;
} jmesh;

/* return value: number of vertices upon success, -1 upon failure*/
int load_off_mesh(FILE *fp, jmesh *mesh);

