#include "forms.hpp"

void printRectangle(float x, float y, float z) {
	glVertex3f(x, -y, z);
	glVertex3f(-x, -y, z);
	glVertex3f(-x, y, z);
	glVertex3f(x, y, z);

	glVertex3f(x, -y, -z);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, y, -z);
	glVertex3f(x, y, -z);

	glVertex3f(x, -y, -z);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, -y, z);
	glVertex3f(x, -y, z);

	glVertex3f(x, y, -z);
	glVertex3f(-x, y, -z);
	glVertex3f(-x, y, z);
	glVertex3f(x, y, z);

	glVertex3f(x, y, -z);
	glVertex3f(x, -y, -z);
	glVertex3f(x, -y, z);
	glVertex3f(x, y, z);

	glVertex3f(-x, y, -z);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, -y, z);
	glVertex3f(-x, y, z);
}

void printTrapeze3D(float x, float y, float z, float decalage, float pos3D) {
	glVertex3f(x, -y - decalage,pos3D);
	glVertex3f(-x, -y,pos3D);
	glVertex3f(-x, y,pos3D);
	glVertex3f(x, y + decalage,pos3D);

	glVertex3f(x, -y - decalage, z);
	glVertex3f(-x, -y, z);
	glVertex3f(-x, y, z);
	glVertex3f(x, y + decalage, z);

	glVertex3f(x, -y - decalage, z);
	glVertex3f(x, -y - decalage,pos3D);
	glVertex3f(x, y + decalage,pos3D);
	glVertex3f(x, y + decalage, z);

	glVertex3f(-x, -y, z);
	glVertex3f(-x, -y,pos3D);
	glVertex3f(-x, y,pos3D);
	glVertex3f(-x, y, z);

	glVertex3f(x, -y, z);
	glVertex3f(x, -y,pos3D);
	glVertex3f(-x, y,pos3D);
	glVertex3f(-x, y, z);
}