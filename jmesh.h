#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include "offreader.h"


typedef struct Object{
    float x;
    float y;
    float z;
    float radius;
    float movement_speed;
} object;

jmesh *mesh_off;
object *sun;
object *planet_1;
object *planet_2;

/* return value: pointer to jmesh upon success, NULL upon failure*/
jmesh *new_jmesh(FILE *fp);
void free_mesh(jmesh *mesh);
float *get_min_bounds(jmesh *mesh);
float *get_max_bounds(jmesh *mesh);
float *get_centroid(jmesh *mesh);
void make_mesh(int option, char *file_name, float scale);
void display(void);
void draw();
void init_solar_system();



