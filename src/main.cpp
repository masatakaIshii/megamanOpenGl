#include<windows.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <iostream>
#include <iterator>
#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"
#include "SOIL.h"
#include "object.hpp"
#include "definitions.hpp"
#include "vector.hpp"
#include "Camera.h"
#include "Map.h"
#include "Megaman.h"

// Megaman header



// Objet Camera
Camera *cam = new Camera();
float teta = 0;




// Objet Sc�ne
Map *m = new Map();

Megaman *megaman = new Megaman();

/** GESTION FENETRE **/
void reshapeWindow(int w, int h)
{
    if (h == 0)
        h = 1;

    float ratio =  w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 348.0f);
    glMatrixMode(GL_MODELVIEW);
}

/** FONCTIONS DE GESTION CLAVIER **/
void KeyboardDown(unsigned char key, int xx, int yy)
{
    switch(key)
    {
    case 'p': // Unlock Camera
        cam->locked = (cam->locked)?0:1;
        break;
    case 'z':
        cam->deltaForward = 1;
        break;
    case 's':
        cam->deltaForward = -1;
        break;
    case 'd':
        cam->deltaStrafe = -1;
        break;
    case 'q':
        cam->deltaStrafe = 1;
        break;
		// Modes megaman
	case 'f':
		if (megaman->fire)
		{
			megaman->fire = false;
		}
		else
		{
			megaman->fire = true;
		}
		break;
	// Tir
	case 'c':
		if (megaman->canon)
		{
			megaman->canon = false;
		}
		else
		{
			megaman->canon = true;
		}
		break;
		// take boom
	case 't':
		megaman->canon = true;
		megaman->shoot = true;
		break;
        // remove boom
	case 'r':
		megaman->canon = false;
		megaman->shoot = false;
		break;
        // Boom headshot
	case 'b':
		megaman->seconds = time(NULL);
		megaman->puissance += PUISSANCE_BULLET;
		megaman->bullet = true;
		break;

		// Mouvement
	case 'w':
		if (megaman->walk)
		{
			megaman->walk = false;
		}
		else
		{
			megaman->walk = true;
		}
		break;

    case SPACEBAR:
		if (!megaman->jump && megaman->onFloor){
			megaman->jump = true;
			megaman->onFloor = false;
		}
		break;

    case 'a':
		if (megaman->shoot && megaman->angleCanonY < 62)
		{
			megaman->angleCanonY += 1.5;
			megaman->translateCanonX -= 1.5 * 0.01;
			megaman->translateCanonZ += 1.5 * 0.02;
			//std::cout << angleCanonY << std::endl;
			megaman->angleBassinY += 0.25;
		}
		break;

	case 'e':
		if (megaman->shoot)
		{
			megaman->angleCanonY -= 1.5;
			megaman->translateCanonX += 1.5 * 0.01;
			megaman->translateCanonZ -= 1.5 * 0.02;
			//std::cout << angleCanonY << std::endl;
			megaman->angleBassinY -= 0.25;
		}
		break;
    }
}
void KeyboardUp(unsigned char key, int xx, int yy)
{
    switch(key)
    {
    case 'z':
    case 's':
        cam->deltaForward = 0;
        break;
    case 'q':
    case 'd':
        cam->deltaStrafe = 0;
        break;
    }
}
void SpecialDown(int key, int xx, int yy)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        cam->deltaForward = 1;
        break;
    case GLUT_KEY_DOWN:
        cam->deltaForward = -1;
        break;
    case GLUT_KEY_RIGHT:
        cam->deltaStrafe = -1;
        break;
    case GLUT_KEY_LEFT:
        cam->deltaStrafe = 1;
        break;
    }
}
void SpecialUp(int key, int xx, int yy)
{
    switch(key)
    {
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
        cam->deltaForward = 0;
        break;
    case GLUT_KEY_RIGHT:
    case GLUT_KEY_LEFT:
        cam->deltaStrafe = 0;
        break;
    }
}

/** FONCTIONS DE GESTION SOURIS (ORIENTATION CAMERA) **/
void mouseMove(int x, int y)
{
    // Rentres uniquement lors du clic
    cam->orienterCam(x, y);
}
void mouseButton(int button, int state, int x, int y)
{
    // Gestion camera en fonction du clic souris
    if (button == GLUT_LEFT_BUTTON)
    {
        // Relacher la camera
        if (state == GLUT_UP)
        {
            cam->releaseCam();
        }
        // Mise � jour origine du clic
        else
        {
            cam->grabCam(x, y);
        }
    }
}

/** GESTION DEPLACEMENT CAMERA **/
void computePos(int inutile)
{
    cam->updatePos();
    megaman->Update();
    glutTimerFunc(10, computePos, 0);
}

/** AFFICHAGE **/
void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // D�finition de la cam�ra
    gluLookAt(  cam->posx, cam->posy, cam->posz,
                cam->posx+cam->dirx, cam->posy+cam->diry,  cam->posz+cam->dirz,
                0.0f, 1.0f,  0.0f
                );

    m->DrawGround();
    m->DrawSkybox(cam);
    glPushMatrix();
    glTranslatef(0,1,0);
    glScalef(0.5, 0.5, 0.5);
    megaman->Draw();
    glPopMatrix();
    glutSwapBuffers();
}

void LoadTextures()
{
    m->LoadTextures();
}

int main(int argc, char **argv)
{
    /** CREATION FENETRE **/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("Impl�mentation :: Textures");

    /** FONCTIONS GLUT **/
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshapeWindow);
    glutIdleFunc(renderScene);
    glutTimerFunc(10, computePos, 0);

    /** GESTION CLAVIER **/
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(KeyboardDown);
    glutKeyboardUpFunc(KeyboardUp);
    glutSpecialFunc(SpecialDown);
    glutSpecialUpFunc(SpecialUp);

    /** GESTION SOURIS **/
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    /** INIT TEXTURES **/
    LoadTextures();

    /** INIT GL STATES **/
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glutMainLoop();

    return (1);
}
