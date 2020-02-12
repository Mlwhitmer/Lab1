#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glut.h>
#include "offreader.h"

int load_off_mesh(FILE *fp, jmesh *mesh){

    char buffer[1024];
    int i;
    float f;
    int triangle_count = 0;
    int colors;

    if (fp == NULL){
        printf("Error opening file\n");
        return -1;  //return -1 upon failure
    }


    else {
        fscanf(fp, " %1023s", buffer);
        if(strcmp(buffer, "OFF" ) != 0){    //not an OFF file
            fclose (fp);
            return -1;  //return -1 upon failure
        }

        fscanf(fp, " %1023s", buffer); //Get the number of vertices
        sscanf(buffer, "%d", &i); //convert string to int
        mesh->nvert = i;

        float *vertices = malloc(sizeof(float) * mesh->nvert * 3); //multiply by 3 for x, y, z coordinates

        fscanf(fp, " %1023s", buffer); //Get the number of faces
        sscanf(buffer, "%d", &i); //convert string to int
        int faces_count = i;
        int *triangles = malloc(sizeof(int) * (faces_count * 3) * 3); //multiply faces_count by 3 for worst case scenario then by 3 for 3 triangle vertices

        fscanf(fp, " %1023s", buffer);
        sscanf(buffer, "%d", &i); //convert string to int
        colors = i;

        int v;
        for(v = 0; v < mesh->nvert; v++){ //Get vertices from OFF file
            fscanf(fp, " %1023s", buffer);
            f = (float)atof(buffer);    //convert string to float
            vertices[v * 3 + 0] = f; //x //Width = 3

            fscanf(fp, " %1023s", buffer);
            f = (float)atof(buffer);    //convert string to float
            vertices[v * 3 + 1] = f; //y

            fscanf(fp, " %1023s", buffer);
            f = (float)atof(buffer);    //convert string to float
            vertices[v * 3 + 2] = f; //z
        }

        mesh->vertices = vertices;  //Load in vertices

        //Find Triangles Now//

        for(v = 0; v < faces_count; v++){ //Get vertices from OFF file
            fscanf(fp, " %1023s", buffer); //Get the number of vertices for the face
            sscanf(buffer, "%d", &i);

            if(i == 4){ //We must tessellate to convert square to triangles
                fscanf(fp, " %1023s", buffer);
                sscanf(buffer, "%d", &i);
                int A = i;

                fscanf(fp, " %1023s", buffer);
                sscanf(buffer, "%d", &i);
                int B = i;

                fscanf(fp, " %1023s", buffer);
                sscanf(buffer, "%d", &i);
                int C = i;

                fscanf(fp, " %1023s", buffer);
                sscanf(buffer, "%d", &i);
                int D = i;

                triangles[triangle_count * 3 + 0] = A;
                triangles[triangle_count * 3 + 1] = B;
                triangles[triangle_count * 3 + 2] = C;
                triangle_count++;

                triangles[triangle_count * 3 + 0] = C;
                triangles[triangle_count * 3 + 1] = D;
                triangles[triangle_count * 3 + 2] = A;
                triangle_count++;
            }
            else if(i == 5){ //We must tessellate to convert pentagon to triangles
                fscanf(fp, " %1023s", buffer);
                sscanf(buffer, "%d", &i);
                int A = i;

                fscanf(fp, " %1023s", buffer);
                sscanf(buffer, "%d", &i);
                int B = i;

                fscanf(fp, " %1023s", buffer);
                sscanf(buffer, "%d", &i);
                int C = i;

                fscanf(fp, " %1023s", buffer);
                sscanf(buffer, "%d", &i);
                int D = i;

                fscanf(fp, " %1023s", buffer);
                sscanf(buffer, "%d", &i);
                int E = i;

                triangles[triangle_count * 3 + 0] = A;
                triangles[triangle_count * 3 + 1] = B;
                triangles[triangle_count * 3 + 2] = C;
                triangle_count++;

                triangles[triangle_count * 3 + 0] = C;
                triangles[triangle_count * 3 + 1] = D;
                triangles[triangle_count * 3 + 2] = E;
                triangle_count++;

                triangles[triangle_count * 3 + 0] = C;
                triangles[triangle_count * 3 + 1] = E;
                triangles[triangle_count * 3 + 2] = A;
                triangle_count++;
            }
            else{
                fscanf(fp, " %1023s", buffer);
                sscanf(buffer, "%d", &i);
                int A = i;

                fscanf(fp, " %1023s", buffer);
                sscanf(buffer, "%d", &i);
                int B = i;

                fscanf(fp, " %1023s", buffer);
                sscanf(buffer, "%d", &i);
                int C = i;

                triangles[triangle_count * 3 + 0] = A;
                triangles[triangle_count * 3 + 1] = B;
                triangles[triangle_count * 3 + 2] = C;
                triangle_count++;
            }

            if(colors != 0) {
                fscanf(fp, " %1023s", buffer);  //Don't worry about colors right now
                fscanf(fp, " %1023s", buffer);
                fscanf(fp, " %1023s", buffer);
            }
        }

        mesh->ntri = triangle_count;  //Load in vertices

        mesh->triangles = malloc(sizeof(int) * mesh->ntri * 3);  //Now we can obtain the right size for the malloc memory
        for(v = 0; v < mesh->ntri; v++){
            mesh->triangles[v * 3 + 0] = triangles[v * 3 + 0];
            mesh->triangles[v * 3 + 1] = triangles[v * 3 + 1];
            mesh->triangles[v * 3 + 2] = triangles[v * 3 + 2];
        }
        free(triangles); //Free unused memory

        //Find Normals Now//

        float *normals = malloc(sizeof(float) * mesh->ntri * 3); //One normal per triangle surface

        for(v = 0; v < mesh->ntri; v++){
            int Point1 = mesh->triangles[v * 3 + 0];
            int Point2 = mesh->triangles[v * 3 + 1];
            int Point3 = mesh->triangles[v * 3 + 2];

            float Point1_x = vertices[Point1 * 3 + 0];
            float Point1_y = vertices[Point1 * 3 + 1];
            float Point1_z = vertices[Point1 * 3 + 2];

            float Point2_x = vertices[Point2 * 3 + 0];
            float Point2_y = vertices[Point2 * 3 + 1];
            float Point2_z = vertices[Point2 * 3 + 2];

            float Point3_x = vertices[Point3 * 3 + 0];
            float Point3_y = vertices[Point3 * 3 + 1];
            float Point3_z = vertices[Point3 * 3 + 2];

            float *vector1 = malloc(sizeof(float) * 3);
            float *vector2 = malloc(sizeof(float) * 3);

            vector1[0] = Point3_x - Point1_x;   //x
            vector1[1] = Point3_y - Point1_y;   //y
            vector1[2] = Point3_z - Point1_z;   //z

            vector2[0] = Point2_x - Point1_x;   //x
            vector2[1] = Point2_y - Point1_y;   //y
            vector2[2] = Point2_z - Point1_z;   //z

            //Cross Product
            normals[v * 3 + 0] = (vector1[1] * vector2[2]) - (vector1[2] * vector2[1]);
            normals[v * 3 + 1] = (vector1[2] * vector2[0]) - (vector1[0] * vector2[2]);
            normals[v * 3 + 2] = (vector1[0] * vector2[1]) - (vector1[1] * vector2[0]);

            free(vector1);
            free(vector2);
        }

        mesh->normals = normals;

        fclose (fp);
    }



    return 0;
}