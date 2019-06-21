#include <windows.h>
#include <iostream>
#include "glut.h"
#include "object.hpp"
#include "forms.hpp"
#include "Map.h"
#include "Block.h"

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
	if (indice == m_countColor)
	{
		m_countColor++;
	}
}
void Object::AddTexture(int indice, char* url)
{
    m_textures[indice] = SOIL_load_OGL_texture(url,SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);;
}

void Object::SetColor(int indiceObject, int indiceColor)
{
	m_colorObject[indiceObject] = indiceColor;
}

void Object::SetTexture(int indiceObject, int indiceTexture)
{
	m_textureObject[indiceObject] = indiceTexture;
	m_haveTexture[indiceObject] = 1;
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
	if (indice == m_countObject)
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

void Object::AddObject(int indice, GLenum mode, float x, float y, float z, float decalage, float start, float degres)
{
	m_mode[indice] = mode;
	Vector3f buffer(x, y, z);
	Vector3f decalageBuffer(decalage, 0, 0);
	m_decalage[indice] = decalageBuffer;
	m_pos[indice] = buffer;
	m_start[indice][0] = start;
	m_degres[indice][0] = degres;
	m_sizeParts[indice] = 1;
	if (indice == m_countObject)
	{
		m_countObject++;
	}
	m_colorObject[indice] = -1;
}

void Object::AddBigObject(int indice, GLenum mode, float x[], float y[], float z[], float decalage[], float start[], float degres[], int size)
{
	if (size > 0 && size <= NUMBER_PARTS)
	{
		m_mode[indice] = mode;
		for (int i = 0; i < size; i++)
		{
			Vector3f buffer(x[i], y[i], z[i]);
			Vector3f decalageBuffer(decalage[i], 0, 0);
			m_decalageBig[indice][i] = decalageBuffer;
			m_posBig[indice][i] = buffer;
		}
		remplirTab(indice, start, size, 0);
		remplirTab(indice, degres, size, 1);
		m_sizeParts[indice] = size;
		if (indice == m_countObject)
		{
			m_countObject++;
		}
		m_colorObject[indice] = -1;
	}
	else
	{
		if (m_message[indice])
		{
			std::cout << "Error Object class : mode define in addObject for form " << indice << " doesn't exist" << std::endl;
			m_message[indice] = 0;
		}
	}

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
		glBegin(GL_QUADS);
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
		glVertex3f(-m_pos[indice].x, -m_pos[indice].y, m_pos[indice].z);
		glVertex3f(-m_pos[indice].x, m_pos[indice].y, m_pos[indice].z);
		glVertex3f(m_pos[indice].x, m_pos[indice].y + m_decalage[indice].x, m_pos[indice].z);
		glEnd();
	}
	else if ((int)m_mode[indice] == 33) // GL_TRAPEZE3D
	{
		glBegin(GL_QUADS);
		chooseColor(indice);
		printTrapeze3D(m_pos[indice].x, m_pos[indice].y, m_pos[indice].z, m_decalage[indice].x, m_pos3D[indice]);
		glEnd();
	}
	else if ((int)m_mode[indice] == 35) //GL_RECTANGLE
	{
		glBegin(GL_QUADS);
		chooseColor(indice);
		printRectangle(m_pos[indice].x, m_pos[indice].y, m_pos[indice].z);
		glEnd();
	}
	else if ((int)m_mode[indice] == 36) // GL_CIRCLE_ARC
	{
		for (int indice2 = 0; indice2 < m_sizeParts[indice]; indice2++)
		{
			float start = DEG2RAD(m_start[indice][indice2]);
			float degres = DEG2RAD(m_degres[indice][indice2]);

			for (float i = start; i < start + degres; i += 0.1)
			{
				glPushMatrix();
				//glTranslatef(-i, i, 0); For do an escalier
				glTranslatef(cos(i) * m_decalageBig[indice][indice2].x + m_decalageBig[indice][indice2].x, sin(i) * m_decalageBig[indice][indice2].x, 0);
				glBegin(GL_QUADS);
				chooseColor(indice);
				printRectangle(m_posBig[indice][indice2].x, m_posBig[indice][indice2].y, m_posBig[indice][indice2].z);
				glEnd();
				glPopMatrix();
			}
		}
	}
	else
	{
		if (m_message[indice])
		{
			std::cout << "Error Object class : mode define in addObject for form " << indice << " doesn't exist" << std::endl;
			m_message[indice] = 0;
		}
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

void Object::BigShow(int indice, int indice2)
{
	if ((int)m_mode[indice] == 36) // GL_CIRCLE_ARC
	{
		float start = DEG2RAD(m_start[indice][indice2]);
		float degres = DEG2RAD(m_degres[indice][indice2]);
		if (degres >= 0)
		{
			for (float i = start; i < start + degres; i += 0.1)
			{
				glPushMatrix();
				//glTranslatef(-i, i, 0); For do an escalier
				glTranslatef(cos(i) * m_decalageBig[indice][indice2].x + m_decalageBig[indice][indice2].x, sin(i) * m_decalageBig[indice][indice2].x, 0);
				glBegin(GL_QUADS);
				chooseColor(indice);
				printRectangle(m_posBig[indice][indice2].x, m_posBig[indice][indice2].y, m_posBig[indice][indice2].z);
				glEnd();
				glPopMatrix();
			}
		}
		else
		{
			for (float i = start; i > start + degres; i -= 0.1)
			{
				glPushMatrix();
				glTranslatef(cos(i) * m_decalageBig[indice][indice2].x + m_decalageBig[indice][indice2].x, sin(i) * m_decalageBig[indice][indice2].x, 0);
				glBegin(GL_QUADS);
				chooseColor(indice);
				printRectangle(m_posBig[indice][indice2].x, m_posBig[indice][indice2].y, m_posBig[indice][indice2].z);
				glEnd();
				glPopMatrix();
			}
		}
	}
}

void Object::BigShow(int indice, int indice2, int color)
{
	if ((int)m_mode[indice] == 36) // GL_CIRCLE_ARC
	{
		float start = DEG2RAD(m_start[indice][indice2]);
		float degres = DEG2RAD(m_degres[indice][indice2]);
		if (degres >= 0)
		{
			for (float i = start; i < start + degres; i += 0.1)
			{
				glPushMatrix();
				//glTranslatef(-i, i, 0); For do an escalier
				glTranslatef(cos(i) * m_decalageBig[indice][indice2].x + m_decalageBig[indice][indice2].x, sin(i) * m_decalageBig[indice][indice2].x, 0);
				glBegin(GL_QUADS);
				glColor3f(m_color[color].x, m_color[color].y, m_color[color].z);
				printRectangle(m_posBig[indice][indice2].x, m_posBig[indice][indice2].y, m_posBig[indice][indice2].z);
				glEnd();
				glPopMatrix();
			}
		}
		else
		{
			for (float i = start; i > start + degres; i -= 0.1)
			{
				glPushMatrix();
				glTranslatef(cos(i) * m_decalageBig[indice][indice2].x + m_decalageBig[indice][indice2].x, sin(i) * m_decalageBig[indice][indice2].x, 0);
				glBegin(GL_QUADS);
				glColor3f(m_color[color].x, m_color[color].y, m_color[color].z);
				printRectangle(m_posBig[indice][indice2].x, m_posBig[indice][indice2].y, m_posBig[indice][indice2].z);
				glEnd();
				glPopMatrix();
			}
		}
	}
}


void Object::chooseColor(int indice)
{
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient_color);

    if(m_haveTexture[indice] == 1)
    {
        //GLuint texture = SOIL_load_OGL_texture("img/cible.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);

        //glBindTexture(GL_TEXTURE_2D,m_textures[indice]);
        /*
        glBindTexture(GL_TEXTURE_2D,texture);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        */
        std::cout << indice << std::endl;
    }

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

void Object::remplirTab(int indice, float tab[], int size, int tabRemplir)
{
	if (size > 0 && size <= NUMBER_PARTS)
	{
		for (int i = 0; i < size; i++)
		{
			if (tabRemplir == 0)
			{
				m_start[indice][i] = tab[i];
			}
			else
			{
				m_degres[indice][i] = tab[i];
			}
		}
	}
	else
	{
		std::cout << "Error Object class : size define in addObject for indice " << indice << "not good" << std::endl;
	}
}
