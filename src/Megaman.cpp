#include "Megaman.h"

Megaman::Megaman(){
    this->canon = false;
    this->shoot = false;
    this->bullet = false;
    this->shootBullet = false;
    this->fire = false;
    this->walk = false;
    this->rightLeg = false;
    this->walkEtape = 1;
    this->seconds;
    this->puissance = 0;

        // Transformations
    this->angleArmX = 0;
    this->angleForearmY = 0;
    this->translateArmZ = 0;
    this->translateArmY = 0;
    this->translateBulletX[10];
    this->translateBulletZ[10];
    this->angleForelegX = 0;
    this->angleLegX = 0;
    this->translateForelegZ = -0.2;
    this->angleForelegX_2 = 0;
    this->angleLegX_2 = 0;
    this->translateForelegZ_2 = -0.2;
}

/***** DRAW *****/

/**
* To construct Megaman
*/
void Megaman::Draw(){
    Object megaman(TETE, GL_CERCLE, 0.5, 18.0, 18.0);
    megaman.AddObject(CORPS, GL_TRAPEZE3D, 1.5, 0.8, -0.5, 0.3f);

    Megaman::SetColors(&megaman);

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	megaman.Show(CORPS);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, -0.25);
	megaman.Show(TETE);
	glPopMatrix();

	Megaman::SetArms(&megaman);

    Megaman::SetLegs(&megaman);

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

void Megaman::SetColors(Object *megaman){

	megaman->Addcolor(BLUE, 0, 0, 1);
	megaman->Addcolor(WHITE, 1, 1, 1);
	megaman->Addcolor(RED, 1, 0, 0);
	if (fire)
	{
		megaman->SetDefaultColor(RED);
	}
	else
	{
		megaman->SetDefaultColor(BLUE);
	}
}

void Megaman::SetArms(Object *megaman){

	megaman->AddObject(BRAS, GL_POLYGON, 0.15, 3, 30);
	megaman->AddObject(AVANT_BRAS, GL_POLYGON, 0.15, 2, 30);
	megaman->AddObject(CANON, GL_POLYGON, 0.3, 1.5, 30);

	glPushMatrix();

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

	glPopMatrix();

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
}

void Megaman::SetLegs(Object *megaman){

	megaman->AddObject(JAMBE, GL_POLYGON, 0.2, 2, 30);
	megaman->AddObject(AVANT_JAMBE, GL_POLYGON, 0.2, 2, 30);
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
void Megaman::Update(int value){

    Megaman::MoveArm();

    Megaman::Walk();

    Megaman::ShootBullet();

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
