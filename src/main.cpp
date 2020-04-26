#include <GL/freeglut.h>

#include "Entity.h"
#include "Scene.h"


const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

Scene scene(SCREEN_WIDTH, SCREEN_HEIGHT);

void RenderScene()
{
    scene.update();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0,0, SCREEN_WIDTH,0,0,0,0,1,0); //

    scene.draw();
    glutSwapBuffers();
}

void Reshape(int width,int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, width, height);
    glOrtho(0, width, height, 0, 0.1, 10000);

    glMatrixMode(GL_MODELVIEW);
}


void Animate (int value)
{
    glutPostRedisplay();
    glutTimerFunc(16, Animate, ++value);
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        // Escape
        case '\x1B':
            exit(EXIT_SUCCESS);
            break;
    }
}


void Init(int argc, char **argv)
{
    glutInit( &argc, argv );
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
    glutCreateWindow( "Physics" );
    glutDisplayFunc( RenderScene );
    glutReshapeFunc( Reshape );
    glutTimerFunc( 16, Animate, 0);
    glutKeyboardFunc(&keyboard);

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
    glClearColor(0, 0, 0, 1);


    glutMainLoop();
}

int main(int argc, char **argv) {
    Init(argc, argv);
    return 0;
}
