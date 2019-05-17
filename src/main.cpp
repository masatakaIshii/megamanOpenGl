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

// Megaman header
using namespace std;
void drawMegaman();
void updateMegaman(int value);

// Objet Camera
Camera *cam = new Camera();
float teta = 0;

// Actions
bool canon = false;
bool shoot = false;
bool bullet = false;
bool shootBullet = false;
bool fire = false;
bool walk = false;
bool rightLeg = false;
int walkEtape = 1;
time_t seconds;
float puissance = 0;
list<float> keepPuissance;

// Transformations
float angleArmX = 0;
float angleForearmY = 0;
float translateArmZ = 0;
float translateArmY = 0;
float translateBulletX[10];
float translateBulletZ[10];
float angleForelegX = 0;
float angleLegX = 0;
float translateForelegZ = -0.2;
float angleForelegX_2 = 0;
float angleLegX_2 = 0;
float translateForelegZ_2 = -0.2;


// Objet Scène
Map *m = new Map();



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
    case 'e': // Unlock Camera
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
		if (fire)
		{
			fire = false;
		}
		else
		{
			fire = true;
		}
		break;
	// Tir
	case 'c':
		if (canon)
		{
			canon = false;
		}
		else
		{
			canon = true;
		}
		break;
		// take boom
	case 't':
		canon = true;
		shoot = true;
		break;
        // remove boom
	case 'r':
		canon = false;
		shoot = false;
		break;
        // Boom headshot
	case 'b':
		seconds = time(NULL);
		puissance += PUISSANCE_BULLET;
		bullet = true;
		break;

		// Mouvement
	case 'w':
		if (walk)
		{
			walk = false;
		}
		else
		{
			walk = true;
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
        // Mise à jour origine du clic
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
    updateMegaman(inutile);
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

    m->DrawGround();
    m->DrawSkybox(cam);
    drawMegaman();
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
    glutCreateWindow("Implémentation :: Textures");

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

void updateMegaman(int value) {
	if (shoot)
	{
		if (angleForearmY > -80) {
			angleForearmY -= VITESSE;
		}

		if (angleArmX > -90) {
			angleArmX -= VITESSE;
		}

		if (translateArmY < 1.5) {
			translateArmY += (1.5 * VITESSE) / 90;
		}

		if (translateArmZ < 1.3) {
			translateArmZ += (1.3 * VITESSE) / 90;
		}
	}
	else
	{
		if (angleForearmY < 0) {
			angleForearmY += VITESSE;
		}

		if (angleArmX < 0) {
			angleArmX += VITESSE;
		}

		if (translateArmY > 0) {
			translateArmY -= (1.5 * VITESSE) / 90;
		}

		if (translateArmZ > 0) {
			translateArmZ -= (1.3 * VITESSE) / 90;
		}
	}

	if (walk)
	{
		// Les lignes en commentaires peuvent servir à forcer le bon replacement des jambes si celles-ci se décalent avec le temps
		if (rightLeg) {
			if (walkEtape == 1) {
				if (angleForelegX < 30) {
					angleForelegX += VITESSE;
					angleLegX -= (20 * VITESSE) / 30;
					translateForelegZ += (0.40 * VITESSE) / 30;
				}
				else {
					/*angleForelegX = 30;
					angleLegX = -20;
					translateForelegZ = 0.35;*/
					walkEtape = 2;
				}
			}
			else if (walkEtape == 2) {
				if (angleForelegX > -25) {
					angleForelegX -= VITESSE;
				}
				else {
					//angleForelegX = -25;
					walkEtape = 3;
				}
			}
			else if (walkEtape == 3) {
				if (angleForelegX < 0) {
					angleForelegX += VITESSE;
					angleLegX += (20 * VITESSE) / 25;
					translateForelegZ -= (0.40 * VITESSE) / 25;
				}
				else {
					/*angleForelegX = 0;
					angleLegX = 0;
					translateForelegZ = -0.2;*/
					rightLeg = false;
					walkEtape = 1;
				}
			}
		}
		else {
			if (walkEtape == 1) {
				if (angleForelegX_2 < 30) {
					angleForelegX_2 += VITESSE;
					angleLegX_2 -= (20 * VITESSE) / 30;
					translateForelegZ_2 += (0.40 * VITESSE) / 30;
				}
				else {
					walkEtape = 2;
				}
			}
			else if (walkEtape == 2) {
				if (angleForelegX_2 > -25) {
					angleForelegX_2 -= VITESSE;
				}
				else {
					walkEtape = 3;
				}
			}
			else if (walkEtape == 3) {
				if (angleForelegX_2 < 0) {
					angleForelegX_2 += VITESSE;
					angleLegX_2 += (20 * VITESSE) / 25;
					translateForelegZ_2 -= (0.40 * VITESSE) / 25;
				}
				else {
					rightLeg = true;
					walkEtape = 1;
				}
			}
		}
	}

	if (shootBullet)
	{
		for (int i = 0; i < keepPuissance.size(); i++)
		{
			if (translateBulletX[i] < 40) {
				translateBulletX[i] += 0.2;
				translateBulletZ[i] += 0.2;
			}
			else {
				keepPuissance.pop_front();
			}
		}
	}
	glutPostRedisplay();
}

void drawMegaman(){
Object megaman(TETE, GL_CERCLE, 0.5, 18.0, 18.0);
	megaman.AddObject(CORPS, GL_TRAPEZE3D, 1.5, 0.8, -0.5, 0.3f);
	megaman.Addcolor(BLUE, 0, 0, 1);
	megaman.Addcolor(WHITE, 1, 1, 1);
	megaman.Addcolor(RED, 1, 0, 0);
	if (fire)
	{
		megaman.SetDefaultColor(RED);
	}
	else
	{
		megaman.SetDefaultColor(BLUE);
	}

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	megaman.Show(CORPS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, -0.25);
	megaman.Show(TETE);
	glPopMatrix();

	megaman.AddObject(BRAS, GL_POLYGON, 0.15, 3, 30);
	megaman.AddObject(AVANT_BRAS, GL_POLYGON, 0.15, 2, 30);
	megaman.AddObject(CANON, GL_POLYGON, 0.3, 1.5, 30);

	glPushMatrix();

	glPushMatrix();
	glTranslatef(-1.2, 1.5, -0.25);
	glRotatef(90, 1, 0, 0);
	glRotatef(-25, 0, 1, 0);
	megaman.Show(BRAS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.1, -0.2, -0.25);
	glRotatef(90, 0, 1, 0);
	glRotatef(35, 1, 0, 0);
	megaman.Show(AVANT_BRAS);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, translateArmY, translateArmZ);
	glRotatef(angleArmX, 1, 0, 0);

	glPushMatrix();
	glTranslatef(1.2, 1.5, -0.25);
	glRotatef(90, 1, 0, 0);
	glRotatef(25, 0, 1, 0);
	megaman.Show(BRAS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, -0.2, -0.25);
	glRotatef(90, 0, 1, 0);
	glRotatef(145, 1, 0, 0);
	glRotatef(angleForearmY, 1, 0, 0);
	if (canon)
	{
		megaman.Show(CANON);
	}
	else
	{
		megaman.Show(AVANT_BRAS);
	}
	glPopMatrix();

	glPopMatrix();

	megaman.AddObject(JAMBE, GL_POLYGON, 0.2, 2, 30);
	megaman.AddObject(AVANT_JAMBE, GL_POLYGON, 0.2, 2, 30);
	glPushMatrix();
	glTranslatef(-0.6, -1.5, -0.2);
	glRotatef(90, 1, 0, 0);
	glRotatef(angleLegX_2, 1, 0, 0);
	megaman.Show(JAMBE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.6, -2.5, translateForelegZ_2);
	glRotatef(90, 1, 0, 0);
	glRotatef(angleForelegX_2, 1, 0, 0);
	megaman.Show(AVANT_JAMBE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.6, -1.5, -0.2);
	glRotatef(90, 1, 0, 0);
	glRotatef(angleLegX, 1, 0, 0);
	megaman.Show(JAMBE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.6, -2.5, translateForelegZ);
	glRotatef(90, 1, 0, 0);
	glRotatef(angleForelegX, 1, 0, 0);
	megaman.Show(AVANT_JAMBE);
	glPopMatrix();


	if (bullet && shoot && canon) {
		size_t now;
		now = time(NULL);
		if (now >= seconds + TIME_SHOOT)
		{
			cout << puissance << endl;

			if (puissance > PUISSANCE_MAX_BULLET) {
				puissance = PUISSANCE_MAX_BULLET;
			}
			shootBullet = true;
			translateBulletX[keepPuissance.size()] = 2.8;
			translateBulletZ[keepPuissance.size()] = 2.8;
			keepPuissance.push_back(puissance);
			puissance = 0;
			bullet = false;
		}
	}

	shootBullet = !keepPuissance.empty();

	if (shootBullet) {
		int count = 0;
		for (list<float>::iterator i = keepPuissance.begin(); i != keepPuissance.end(); i++)
		{
			megaman.AddObject(BULLET + count, GL_CERCLE, *i, 18.0, 18.0);
			glPushMatrix();
			glTranslatef(translateBulletX[count], 1.2, translateBulletZ[count]);
			megaman.Show(BULLET + count);
			glPopMatrix();
			count++;
		}
	}
}
