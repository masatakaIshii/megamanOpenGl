#include<windows.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include "object.hpp"

Object::Object()
{

}

Object::Object(int indice, GLenum mode, float x, float y, float z)
{
	m_mode[indice] = mode;
	Vector3f buffer(x, y, z);
	m_pos[indice] = buffer;
	m_countObject++;
	m_colorObject[indice] = -1;
}

void Object::Addcolor(int indice, float red, float green, float blue)
{
	Vector3f color(red, green, blue);
	m_color[indice] = color;
	if(indice == m_countColor)
	{
		m_countColor++;
	}
}

void Object::SetColor(int indiceObject, int indiceColor)
{
	m_colorObject[indiceObject] = indiceColor;
}

void Object::SetDefaultColor(int indiceColor)
{
	m_defaultColor = m_color[indiceColor];
	m_activeDefaultColor = true;
}

void Object::AddObject(int indice, GLenum mode, float x, float y, float z)
{
	m_mode[indice] = mode;
	Vector3f buffer(x, y, z);
	m_pos[indice] = buffer;
	if(indice == m_countObject)
	{
		m_countObject++;
	}
	m_colorObject[indice] = -1;
}

void Object::AddObject(int indice, GLenum mode, float x, float y, float z, float decalage)
{
	m_mode[indice] = mode;
	Vector3f buffer(x, y, z);
	Vector3f decalageBuffer(decalage, 0, 0);
	m_decalage[indice] = decalageBuffer;
	m_pos[indice] = buffer;
	if (indice == m_countObject)
	{
		m_countObject++;
	}
	m_colorObject[indice] = -1;
}

void Object::AddObject(int indice, GLenum mode, float x, float y, float z, float decalage, float pos3D)
{
	m_mode[indice] = mode;
	Vector3f buffer(x, y, z);
	Vector3f decalageBuffer(decalage, 0, 0);
	m_decalage[indice] = decalageBuffer;
	m_pos[indice] = buffer;
	m_pos3D[indice] = pos3D;
	if (indice == m_countObject)
	{
		m_countObject++;
	}
	m_colorObject[indice] = -1;
}

void Object::AddObject(int indice, GLenum mode, float x, float y, float z, int indiceColor)
{
	m_mode[indice] = mode;
	Vector3f buffer(x, y, z);
	m_pos[indice] = buffer;
	if (indice == m_countObject)
	{
		m_countObject++;
	}
	m_colorObject[indice] = indiceColor;
}

void Object::Show(int indice)
{
	if ((int)m_mode[indice] == 7) // GL_QUADS
	{
		glBegin(m_mode[indice]);
		chooseColor(indice);
		glVertex3f(m_pos[indice].x, -m_pos[indice].y, m_pos[indice].z);
		glVertex3f(-m_pos[indice].x, -m_pos[indice].y, m_pos[indice].z);
		glVertex3f(-m_pos[indice].x, m_pos[indice].y, m_pos[indice].z);
		glVertex3f(m_pos[indice].x, m_pos[indice].y, m_pos[indice].z);
		glEnd();
	}
	else if ((int)m_mode[indice] == 9) // GL_POLYGON
	{
		chooseColor(indice);
		glBegin(m_mode[indice]);
		GLUquadricObj *polygon = gluNewQuadric();
		gluCylinder(polygon, m_pos[indice].x, m_pos[indice].x, m_pos[indice].y, m_pos[indice].z, m_pos[indice].z);
		glEnd();
	}
	else if ((int)m_mode[indice] == 16) // GL_CERCLE
	{
		chooseColor(indice);
		glutSolidSphere(m_pos[indice].x, m_pos[indice].y, m_pos[indice].z);
	}
	else if ((int)m_mode[indice] == 17) // GL_TRAPEZE
	{
		glBegin(GL_QUADS);
		chooseColor(indice);
		glVertex3f(m_pos[indice].x, -m_pos[indice].y - m_decalage[indice].x, m_pos[indice].z);
		glVertex3f(-m_pos[indice].x , -m_pos[indice].y, m_pos[indice].z);
		glVertex3f(-m_pos[indice].x , m_pos[indice].y, m_pos[indice].z);
		glVertex3f(m_pos[indice].x, m_pos[indice].y + m_decalage[indice].x, m_pos[indice].z);
		glEnd();
	}
	else if ((int)m_mode[indice] == 33) // GL_TRAPEZE3D
	{
		glBegin(GL_QUADS);
		chooseColor(indice);
		glVertex3f(m_pos[indice].x, -m_pos[indice].y - m_decalage[indice].x, m_pos3D[indice]);
		glVertex3f(-m_pos[indice].x, -m_pos[indice].y, m_pos3D[indice]);
		glVertex3f(-m_pos[indice].x, m_pos[indice].y, m_pos3D[indice]);
		glVertex3f(m_pos[indice].x, m_pos[indice].y + m_decalage[indice].x, m_pos3D[indice]);
		glEnd();

		glBegin(GL_QUADS);
		chooseColor(indice);
		glVertex3f(m_pos[indice].x, -m_pos[indice].y - m_decalage[indice].x, m_pos[indice].z);
		glVertex3f(-m_pos[indice].x, -m_pos[indice].y, m_pos[indice].z);
		glVertex3f(-m_pos[indice].x, m_pos[indice].y, m_pos[indice].z);
		glVertex3f(m_pos[indice].x, m_pos[indice].y + m_decalage[indice].x, m_pos[indice].z);
		glEnd();

		glBegin(GL_QUADS);
		chooseColor(indice);
		glVertex3f(m_pos[indice].x, -m_pos[indice].y - m_decalage[indice].x, m_pos[indice].z);
		glVertex3f(m_pos[indice].x, -m_pos[indice].y - m_decalage[indice].x, m_pos3D[indice]);
		glVertex3f(m_pos[indice].x, m_pos[indice].y + m_decalage[indice].x, m_pos3D[indice]);
		glVertex3f(m_pos[indice].x, m_pos[indice].y + m_decalage[indice].x, m_pos[indice].z);
		glEnd();

		glBegin(GL_QUADS);
		chooseColor(indice);
		glVertex3f(-m_pos[indice].x, -m_pos[indice].y, m_pos[indice].z);
		glVertex3f(-m_pos[indice].x, -m_pos[indice].y, m_pos3D[indice]);
		glVertex3f(-m_pos[indice].x, m_pos[indice].y, m_pos3D[indice]);
		glVertex3f(-m_pos[indice].x, m_pos[indice].y, m_pos[indice].z);
		glEnd();

		glBegin(GL_QUADS);
		chooseColor(indice);
		glVertex3f(m_pos[indice].x, -m_pos[indice].y, m_pos[indice].z);
		glVertex3f(m_pos[indice].x, -m_pos[indice].y, m_pos3D[indice]);
		glVertex3f(-m_pos[indice].x, m_pos[indice].y, m_pos3D[indice]);
		glVertex3f(-m_pos[indice].x, m_pos[indice].y, m_pos[indice].z);
		glEnd();
	}
}

void Object::Show(int indice[], int size)
{
	for (int i = 0; i < size; i++)
	{
		Show(indice[i]);
	}
}

void Object::ShowAll()
{
	for (int indice = 0; indice < m_countObject; indice++)
	{
		Show(indice);
	}
}

void Object::chooseColor(int indice)
{
	if (m_colorObject[indice] != -1)
	{
		glColor3f(m_color[m_colorObject[indice]].x, m_color[m_colorObject[indice]].y, m_color[m_colorObject[indice]].z);
	}
	else
	{
		if (m_activeDefaultColor)
		{
			glColor3f(m_defaultColor.x, m_defaultColor.y, m_defaultColor.z);
		}
	}
}
