#include "jmesh.h"

int count = 0;
int mesh_option = 0;
float model_scale = 1;

jmesh * new_jmesh(FILE * fp) {
   jmesh * jm;

   jm = malloc(sizeof(jmesh));

   load_off_mesh(fp, jm);

   return jm;
}

void free_mesh(jmesh *mesh) {

    free(mesh->vertices);
    free(mesh->normals);
    free(mesh->triangles);

    free(mesh);
}

float *get_min_bounds(jmesh *mesh){
    int i;
    float *min_bounds = malloc(sizeof(float) * 3);
    min_bounds[0] = 100000000;
    min_bounds[1] = 100000000;
    min_bounds[2] = 100000000;

    for(i = 0; i < mesh->nvert; i++){
        if(mesh->vertices[i * 3 + 0] < min_bounds[0]){
            min_bounds[0] = mesh->vertices[i * 3 + 0];
        }
        if(mesh->vertices[i * 3 + 1] < min_bounds[1]){
            min_bounds[1] = mesh->vertices[i * 3 + 1];
        }
        if(mesh->vertices[i * 3 + 2] < min_bounds[2]){
            min_bounds[2] = mesh->vertices[i * 3 + 2];
        }
    }

    return min_bounds;
}

float *get_max_bounds(jmesh *mesh){
    int i;
    float *max_bounds = malloc(sizeof(float) * 3);
    max_bounds[0] = -100000000;
    max_bounds[1] = -100000000;
    max_bounds[2] = -100000000;

    for(i = 0; i < mesh->nvert; i++){
        if(mesh->vertices[i * 3 + 0] > max_bounds[0]){
            max_bounds[0] = mesh->vertices[i * 3 + 0];
        }
        if(mesh->vertices[i * 3 + 1] > max_bounds[1]){
            max_bounds[1] = mesh->vertices[i * 3 + 1];
        }
        if(mesh->vertices[i * 3 + 2] > max_bounds[2]){
            max_bounds[2] = mesh->vertices[i * 3 + 2];
        }
    }

    return max_bounds;
}

float *get_centroid(jmesh *mesh){
    int i;
    float *points_total = malloc(sizeof(float) * 3);
    points_total[0] = 0;
    points_total[1] = 0;
    points_total[2] = 0;

    for(i = 0; i < mesh->nvert; i++){
        points_total[0] += mesh->vertices[i * 3 + 0];
        points_total[1] += mesh->vertices[i * 3 + 1];
        points_total[2] += mesh->vertices[i * 3 + 2];
    }

    points_total[0] = points_total[0]/mesh->nvert;
    points_total[1] = points_total[1]/mesh->nvert;
    points_total[2] = points_total[2]/mesh->nvert;

    return points_total;
}

void make_mesh(int option, char *file_name, float scale){
    mesh_option = option;
    model_scale = scale;

    FILE *fp;
    fp = fopen(file_name , "r");
    jmesh *mesh = new_jmesh(fp);

    printf("\nModel Information:\n");
    printf("Number of Vertices: %d\n", mesh->nvert);
    printf("Number of Triangles: %d\n", mesh->ntri);

    //get min bounds
    float *min_bounds;
    min_bounds = get_min_bounds(mesh);
    printf("Minimum Bounds: %f %f %f\n", min_bounds[0], min_bounds[1], min_bounds[2]);
    free(min_bounds);

    float *max_bounds;
    max_bounds = get_max_bounds(mesh);
    printf("Maximum Bounds: %f %f %f\n", max_bounds[0], max_bounds[1], max_bounds[2]);
    free(max_bounds);

    float *centroid;
    centroid = get_centroid(mesh);
    printf("Centroid at: %f %f %f\n", centroid[0], centroid[1], centroid[2]);
    free(centroid);

    mesh_off = mesh;
}

void display(void){

    glClearColor(1.0, 0.5, 0.0, 0.0);
    glClearDepth( 1.0 );
    glClear(GL_COLOR_BUFFER_BIT);

    float centerX;
    float centerY;
    float centerZ;

    float *centroid;
    centroid = get_centroid(mesh_off);
    centerX = centroid[0];
    centerY = centroid[1];
    centerZ = centroid[2];
    free(centroid);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Set rendering to wire

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(mesh_option == 1) {
        gluLookAt( centerX, centerY, centerZ, // Look at center of object
                   1.0, 0, 1.0,
                   0.0, 1.0, 0.0 );

        //Sun
        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        draw();
        glPopMatrix();

        //Planet 1
        glPushMatrix();
        glScalef(0.09, 0.09, 0.09);
        glRotatef(count * 0.1, 0, 1, 0);
        glTranslated(4, 0, 4);
        draw();
        glPopMatrix();

        //Planet 2
        glPushMatrix();
        glScalef(0.10, 0.1, 0.1);
        glRotatef(count * 0.018, 0, 1, 0);
        glTranslated(7, 0, 7);
        draw();
        glPopMatrix();

        //Planet 3
        glPushMatrix();
        glScalef(0.2, 0.2, 0.2);
        glRotatef(count * 0.01, 0, 1, 0);
        glTranslated(5, 0, 5);
        draw();
        glPopMatrix();
    }
    else if(mesh_option == 2) {
        gluLookAt( centerX-.1, centerY+.4, centerZ, // Look at center of object
                   0.0, 0, 10.0,
                   0.0, 1.0, 0.0 );
        glPushMatrix();
        glScalef(model_scale, model_scale, model_scale);
        draw();
        glPopMatrix();
    }
    else if(mesh_option == 3) {
        gluLookAt( centerX, centerY, centerZ, // Look at center of object
                   0.0, 0, 1.0,
                   0.0, 1.0, 0.0 );
        draw(); //Draw mushroom
    }
    else if(mesh_option == 4) {
        gluLookAt( centerX-.1, centerY+.4, centerZ, // Look at center of object
                   0.0, 0, 10.0, //Stand far away from the bunny
                   0.0, 1.0, 0.0 );
        glPushMatrix();
        glScalef(5, 5, 5); //Scale bunny up for better viewing
        draw(); //Draw bunny
        glPopMatrix();
    }
    else if(mesh_option == 5) {
        gluLookAt( centerX, centerY+.4, centerZ, // Look at center of object
                   0.0, 0, 10.0, //Stand far away from Beethoven
                   0.0, 1.0, 0.0 );
        glPushMatrix();
        glScalef(.1, .1, .1); //Scale down beethoven up for better viewing
        draw(); //Draw beethoven
        glPopMatrix();
    }
    else if(mesh_option == 6) {
        gluLookAt( centerX, centerY, centerZ, // Look at center of object
                   0.0, 0, 10.0,
                   0.0, 1.0, 0.0 );
        draw();
    }

    glutSwapBuffers();
    glutPostRedisplay();

    count++;

    return;
}

void draw(){
    glBegin(GL_TRIANGLES);
    int i;

    for(i = 0; i < mesh_off->ntri; i++) {
        int Point1 = mesh_off->triangles[i * 3 + 0];
        int Point2 = mesh_off->triangles[i * 3 + 1];
        int Point3 = mesh_off->triangles[i * 3 + 2];

        float Point1_x = mesh_off->vertices[Point1 * 3 + 0];
        float Point1_y = mesh_off->vertices[Point1 * 3 + 1];
        float Point1_z = mesh_off->vertices[Point1 * 3 + 2];

        float Point2_x = mesh_off->vertices[Point2 * 3 + 0];
        float Point2_y = mesh_off->vertices[Point2 * 3 + 1];
        float Point2_z = mesh_off->vertices[Point2 * 3 + 2];

        float Point3_x = mesh_off->vertices[Point3 * 3 + 0];
        float Point3_y = mesh_off->vertices[Point3 * 3 + 1];
        float Point3_z = mesh_off->vertices[Point3 * 3 + 2];

        glVertex3f(Point1_x, Point1_y, Point1_z);
        glVertex3f(Point2_x, Point2_y, Point2_z);
        glVertex3f(Point3_x, Point3_y, Point3_z);
    }

    glEnd();
}

void init_solar_system(){

    sun = malloc(sizeof(object));
    sun->x = 0;
    sun->y = 0;
    sun->z = 0;
    sun->radius = 0;
    sun->movement_speed = 0;

    planet_1 = malloc(sizeof(object));
    planet_1->x = 0;
    planet_1->y = 0;
    planet_1->z = 8;
    planet_1->radius = 8;
    planet_1->movement_speed = 0.1;

    planet_2 = malloc(sizeof(object));
    planet_2->x = 0;
    planet_2->y = 0;
    planet_2->z = 5;
    planet_2->radius = 5.5;
    planet_2->movement_speed = .001;
}