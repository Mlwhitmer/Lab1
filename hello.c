/* hello.c */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glut.h>
#include "utils.h"
#include "jmesh.h"

int main(int argc, char **argv) {
    char c;
    int option = 0;
    init_solar_system();

    graphics_state gs;

    gs.height = 512;
    gs.width = 512;

    if(argc == 1) {
        printf("Please enter a numeric option\n");
        printf("View Solar System Model: 1\n");
        printf("View Square Model: 2\n");
        printf("View Mushroom Model: 3\n");
        printf("View Bunny Model: 4\n");
        printf("View Beethoven Model: 5\n");
        printf("View specified model at entered location: 6\n");
        c = getchar();
        option = c - '0';

        if (option == 1) {
            make_mesh(1, "./off/square.off", 1);
        } else if (option == 2) {
            make_mesh(2, "./off/mushroom.off", 1);
        } else if (option == 3) {
            make_mesh(3, "./off/bunny.off", 1);
        } else if (option == 4) {
            make_mesh(4, "./off/beethoven.off", 1);
        } else if (option == 5) {
            printf("Please enter the OFF file location:\n");
            char str[1000];
            scanf("%s", str);
            make_mesh(5, str, 1);
        }
    }
    else if(argc == 2){
        float f;
        f = (float)atof(argv[1]);
        make_mesh(2, "./off/square.off", f);
    }
    else if(argc == 3){
        float f;
        f = (float)atof(argv[1]);
        make_mesh(2, argv[2], f);
    }



    print_howto();

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(gs.width,gs.height);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(keys);
    glutMouseFunc(mouse_handler);
    glutMotionFunc(trackMotion);

    init(&gs);

    glutMainLoop();

    return 0;
}
