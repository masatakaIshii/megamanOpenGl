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
#include "Block.h"

// Megaman header



// Objet Camera
Camera *cam = new Camera();
float cameraTranslationX = cam->posx;
float cameraTranslationZ = cam->posz;
float cameraDirectionX = cam->dirx;
float cameraDirectionY = cam->diry;
float cameraDirectionZ = cam->dirz;
float teta = 0;
float lastX = 0;
float lastZ = 0;
bool firstIteration = true;


// Objet Scène
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
        if(cam->locked)
        {

        }
        else
        {
            cam->deltaForward = 1;
        }
        break;
    case 's':
        if(cam->locked)
        {

        }
        else
        {
            cam->deltaForward = -1;
        }
        break;
    case 'd':
        if(cam->locked)
        {
            if (megaman->shoot)
            {
                megaman->angleCanonY -= 1.5;
                megaman->translateCanonX += 1.5 * 0.01;
                megaman->translateCanonZ -= 1.5 * 0.02;
                //std::cout << angleCanonY << std::endl;
                megaman->angleBassinY -= 0.25;
                cam->dirz += 0.01;
            }
        }
        else
        {
            cam->deltaStrafe = -1;
        }
        break;
    case 'q':
        if(cam->locked)
        {
            if (megaman->shoot && megaman->angleCanonY < 62)
            {
                megaman->angleCanonY += 1.5;
                megaman->translateCanonX -= 1.5 * 0.01;
                megaman->translateCanonZ += 1.5 * 0.02;
                //std::cout << angleCanonY << std::endl;
                megaman->angleBassinY += 0.25;
                cam->dirz -= 0.01;
            }
        }
        else
        {
            cam->deltaStrafe = 1;
        }
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
    if(!cam->locked)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
        // Relacher la camera
            if (state == GLUT_UP)
            {
                cam->releaseCam();
            }
        // Mise à jour origine du clic
            else
            {
                cam->grabCam(x, y);
            }
        }
    }
}

/** GESTION DEPLACEMENT CAMERA **/
void computePos(int inutile)
{
/*
    std::cout << "pos x : " << cam->posx << std::endl;
    std::cout << "pos z : " << cam->posz << std::endl;
/*
    std::cout << "dir x : " << cam->dirx << std::endl;
    std::cout << "dir z : " << cam->dirz << std::endl;
*/
    if (megaman->walk)
    {
        if(megaman->etapeDeplacement == 0)
        {
            if(lastX != megaman->moveZ){
                cameraTranslationX += VITESSE_WALK/2;
                lastX = megaman->moveZ;
            }
        }
        else if(megaman->etapeDeplacement == 1)
        {
            if(firstIteration)
            {
                firstIteration = false;
                cameraTranslationZ += VITESSE_WALK*13;
            }
            cameraTranslationX = -13;
            cameraDirectionX = 0.02478;
            cameraDirectionZ = -1.0f;
            if(lastZ != megaman->moveX){
                cameraTranslationZ -= VITESSE_WALK/2;
                lastZ = megaman->moveX;
            }
        }
        else if(megaman->etapeDeplacement == 2)
        {
            if(!firstIteration)
            {
                firstIteration = true;
                cameraTranslationX = -19.0;
            }
             cameraTranslationZ = -24.03;
             cameraDirectionX = 0.98;
             cameraDirectionZ = 0.033;
            if(lastX != megaman->moveZ){
                cameraTranslationX += VITESSE_WALK/2;
                lastX = megaman->moveZ;
            }
        }
        else if(megaman->etapeDeplacement == 3)
        {
            if(firstIteration)
            {
                firstIteration = false;
                cameraTranslationZ = -30.2832;
            }
            cameraTranslationX = 22.2796;
            cameraDirectionZ = 0.996766;
            cameraDirectionX = -0.0083804;
            if(lastZ != megaman->moveX){
                cameraTranslationZ += VITESSE_WALK/2;
                lastZ = megaman->moveX;
            }
        }
        else if(megaman->etapeDeplacement == 4)
        {
            if(!firstIteration)
            {
                firstIteration = true;
                cameraTranslationX = 28.082;
            }
            cameraTranslationZ = 24.1436;
            cameraDirectionZ = -0.0157387;
            cameraDirectionX = -0.996265;
            if(lastX != megaman->moveZ){
                cameraTranslationX -= VITESSE_WALK/2;
                lastX = megaman->moveZ;
            }
        }
    }

    if (megaman->walk && cam->locked)
    {
        cam->posx = cameraTranslationX;
        cam->posz = cameraTranslationZ;
        cam->dirx = cameraDirectionX;
        cam->diry = cameraDirectionY;
        cam->dirz = cameraDirectionZ;
	}
    cam->updatePos();
    megaman->Update();
    glutTimerFunc(10, computePos, 0);
}

/** AFFICHAGE **/
void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // Définition de la caméra
    gluLookAt(  cam->posx, cam->posy, cam->posz,
                cam->posx+cam->dirx, cam->posy+cam->diry,  cam->posz+cam->dirz,
                0.0f, 1.0f,  0.0f
                );

    GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };   // Color (0.2, 0.2, 0.2)
	GLfloat lightColor0[] = { 1.0f, 1.0f, 1.0f, 1.0f };    // Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = { -4.0f, 50.0f, -4.0f, 1.0f };      // Positioned at (4, 0, 8)
	//GLfloat lightPos0[] = { 24.0f, 30.0f, 24.0f, 1.0f };
	GLfloat mat_ambient_color[] = { 0.6, 0.6, 0.2, 1.0 };


	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, mat_ambient_color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);        // lumière diffuse
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);         // position
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    int sizeBullet = megaman->keepPuissance.size();
    int sizeCible = sizeof(m->cibleTabX);
    for (int i = 0; i < sizeBullet; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            if(megaman->translateBulletX[i] > m->cibleTabX[j] - 2 && megaman->translateBulletX[i] < m->cibleTabX[j] + 2)
            {
                //std::cout << megaman->translateBulletX[i] << " and " << m->cibleTabX[j] << std::endl;
                std::cout << megaman->translateBulletZ[i] << " and " << m->cibleTabZ[j] << std::endl;
                if(megaman->translateBulletZ[i] > m->cibleTabZ[j] - 2 && megaman->translateBulletZ[i] < m->cibleTabZ[j] + 2)
                {
                    std::cout << "yesss" << std::endl;
                }
            }
        }
    }

    m->DrawGround();
    m->DrawAllCible();
    m->DrawAllBatiment();
    m->DrawSkybox(cam);
    glPushMatrix();
    glTranslatef(-48,2,24);
    glRotatef(90,0,1,0);
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
    glutInitWindowSize(800,600);
    glutCreateWindow("Megaman");

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
    glEnable(GL_NORMALIZE);
    glutMainLoop();

    return (1);
}
