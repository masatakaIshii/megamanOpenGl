#include "Megaman.h"

Megaman::Megaman(){
    this->canon = false;
    this->shoot = false;
    this->bullet = false;
    this->shootBullet = false;
    this->fire = false;
    this->walk = false;
    this->jump = false;
    this->onFloor = true;
    this->rightLeg = false;
    this->walkEtape = 1;
    this->seconds;
    this->puissance = 0;
}

/***** DRAW *****/

/**
* To construct Megaman
*/
void Megaman::Draw(){
    Object megaman(TETE, GL_CERCLE, 0.5, 18.0, 18.0);
    megaman.AddObject(CORPS, GL_TRAPEZE3D, 1.5, 0.8, -0.5, 0.3f);
    const int size = 4;
	float start[size] = { 120, 60, 20, -90 };
	float degres[size] = { 300, -130, 140, -70 };
	float sizex[size] = { 0.02, 0.02, 0.02, 0.04 };
	float sizey[size] = { 0.08, 0.08, 0.08, 0.08 };
	float sizez[size] = { 0.3, 0.3, 0.3, 0.1 };
	float decalage[size] = { -0.5, -0.5, -0.5, -0.5 };
    megaman.AddBigObject(CASQUE, GL_CIRCLE_ARC, sizex, sizey, sizez, decalage, start, degres, size);
    megaman.AddObject(BRAS, GL_POLYGON, 0.15, 3, 30);
	megaman.AddObject(AVANT_BRAS, GL_POLYGON, 0.15, 2, 30);
	megaman.AddObject(CANON, GL_POLYGON, 0.3, 1.5, 30);
	megaman.AddObject(JAMBE, GL_POLYGON, 0.2, 2, 30);
	megaman.AddObject(AVANT_JAMBE, GL_POLYGON, 0.2, 2, 30);
	megaman.AddObject(EYES, GL_CERCLE, 0.1, 18, 18);
	megaman.AddObject(PUPILLE, GL_CERCLE, 0.02, 18, 18);

    Megaman::SetColors(&megaman);

    glPushMatrix();
	glTranslatef(0, jumpY, moveZ);

	glPushMatrix();
	glRotatef(angleBassinY, 0, 1, 0);

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	megaman.Show(CORPS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, -0.25);
	megaman.Show(TETE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 2, -0.3);
	megaman.BigShow(CASQUE, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, 0.23);
	glRotatef(270, 0, 1, 0);
	glRotatef(180, 1, 0, 0);
	megaman.BigShow(CASQUE, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 2, -0.2);
	glRotatef(90, 1, 0, 0);
	megaman.BigShow(CASQUE, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, 0.2);
	//glRotatef(-45, 0, 0, 1);
	glRotatef(270, 0, 1, 0);
	//glRotatef(180, 1, 0, 0);
	megaman.BigShow(CASQUE, 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.2, 2.05, 0.17);
	megaman.Show(EYES);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2, 2.05, 0.17);
	megaman.Show(EYES);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.2, 2.05, 0.28);
	megaman.Show(PUPILLE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2, 2.05, 0.28);
	megaman.Show(PUPILLE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.2, 1.8, 0.21);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0.5, 0, 0);
	glEnd();
	glPopMatrix();

	Megaman::SetArms(&megaman);

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
    glPopMatrix();
	Megaman::SetLegs(&megaman);
	glPopMatrix();
	AddCibles();
}

void Megaman::AddCibles(){
    Object cibles(0, GL_CERCLE, 0.5, 18.0, 18.0);
	cibles.Addcolor(WHITE, 1, 1, 1);
	cibles.SetDefaultColor(WHITE);
	float posCibles[5][3] = { {5,1.3,4},{-4,1.3,7},{-5,1.3,11},{6,1.3,3},{2,1.3,16} };
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glTranslatef(posCibles[i][0], posCibles[i][1], posCibles[i][2]);
		cibles.Show(0);
		glPopMatrix();
	}
}

void Megaman::SetColors(Object *megaman){

	megaman->Addcolor(BLUE, 0, 0, 1);
	megaman->Addcolor(BLUE_LIGHT, 0.43, 0.65, 1);
	megaman->Addcolor(WHITE, 1, 1, 1);
    megaman->Addcolor(BEIGE, 0.95, 0.92, 0.8);
	megaman->Addcolor(RED, 1, 0, 0);
	megaman->Addcolor(RED_LIGHT, 0.97, 0.87, 0.24);

	megaman->SetColor(TETE, BEIGE);
	megaman->SetColor(EYES, WHITE);
	if (fire)
	{
		megaman->SetDefaultColor(RED);
		megaman->SetColor(BRAS, RED_LIGHT);
		megaman->SetColor(JAMBE, RED_LIGHT);
	}
	else
	{
		megaman->SetDefaultColor(BLUE);
		megaman->SetColor(BRAS, BLUE_LIGHT);
		megaman->SetColor(JAMBE, BLUE_LIGHT);
	}
}

void Megaman::SetArms(Object *megaman){

	glPushMatrix();
	glTranslatef(-1.2, 1.5, -0.25);
	glRotatef(90, 1, 0, 0);
	glRotatef(-25, 0, 1, 0);
	megaman->Show(BRAS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.1, -0.2, -0.25);
	glRotatef(90, 0, 1, 0);
	glRotatef(35, 1, 0, 0);
	megaman->Show(AVANT_BRAS);
	glPopMatrix();

	glPushMatrix();
	glRotatef(angleCanonY, 0, 1, 0);
	glTranslatef(translateCanonX, 0, translateCanonZ);

	glPushMatrix();
	glTranslatef(0, translateArmY, translateArmZ);
	glRotatef(angleArmX, 1, 0, 0);

	glPushMatrix();
	glTranslatef(1.2, 1.5, -0.25);
	glRotatef(90, 1, 0, 0);
	glRotatef(25, 0, 1, 0);
	megaman->Show(BRAS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, -0.2, -0.25);
	glRotatef(90, 0, 1, 0);
	glRotatef(145, 1, 0, 0);
	glRotatef(angleForearmY, 1, 0, 0);
	if (canon)
	{
		megaman->Show(CANON);
	}
	else
	{
		megaman->Show(AVANT_BRAS);
	}
	glPopMatrix();
    glPopMatrix();
	glPopMatrix();
}

void Megaman::SetLegs(Object *megaman){
	glPushMatrix();
	glTranslatef(-0.6, -1.5, -0.2);
	glRotatef(90, 1, 0, 0);
	glRotatef(angleLegX_2, 1, 0, 0);
	megaman->Show(JAMBE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.6, -2.5, translateForelegZ_2);
	glRotatef(90, 1, 0, 0);
	glRotatef(angleForelegX_2, 1, 0, 0);
	megaman->Show(AVANT_JAMBE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.6, -1.5, -0.2);
	glRotatef(90, 1, 0, 0);
	glRotatef(angleLegX, 1, 0, 0);
	megaman->Show(JAMBE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.6, -2.5, translateForelegZ);
	glRotatef(90, 1, 0, 0);
	glRotatef(angleForelegX, 1, 0, 0);
	megaman->Show(AVANT_JAMBE);
	glPopMatrix();
}


/***** UPDATE *****/

/**
* All method that move elements
* @param value (int value) : inutile
*/
void Megaman::Update(){

    MoveArm();

    Walk();

    ShootBullet();

    Jump();

	glutPostRedisplay();
}
/**
* Movement of arm
*/
void Megaman::MoveArm(){
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
}

/**
* Walking
*/
void Megaman::Walk(){

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
                    moveZ += VITESSE_WALK;
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
                    moveZ += VITESSE_WALK;
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
}

/**
* Shooting bullet
*/
void Megaman::ShootBullet(){
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
}

void Megaman::Jump(){
    if (!onFloor)
	{
		if (jump) {
			jumpY += 0.05;
			if (jumpY >= 4) {
				jump = false;
			}
		}
		else {
			jumpY -= 0.05;
			if (jumpY <= 0) {
				onFloor = true;
				jumpY = 0;
			}
		}
	}
}
