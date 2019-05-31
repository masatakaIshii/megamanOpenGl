#pragma once
#include "vector.hpp"
#include "definitions.hpp"
#include <math.h>

class Object {
public:
	Object();
	Object(int indice, GLenum mode, float x, float y, float z);
	void AddObject(int indice, GLenum mode, float x, float y, float z);
	void AddObject(int indice, GLenum mode, float x, float y, float z, int indiceColor);
	void AddObject(int indice, GLenum mode, float x, float y, float z, float decalage);
	void AddObject(int indice, GLenum mode, float x, float y, float z, float decalage, float pos3D);
	void AddObject(int indice, GLenum mode, float x, float y, float z, float decalage, float start, float degres);
	void AddBigObject(int indice, GLenum mode, float x[], float y[], float z[], float decalage[], float start[], float degres[], int size);
	void Addcolor(int indice, float red, float green, float blue);
	void SetColor(int indiceObject, int indiceColor);
	void SetDefaultColor(int indiceColor);
	void Show(int indice);
	void Show(int indice[], int size);
	void ShowAll();
	void BigShow(int indice, int indice2);
	void BigShow(int indice, int indice2, int color);

private:
	void chooseColor(int indice);
	void remplirTab(int indice, float tab[], int size, int tabRemplir);
	GLenum m_mode[NUMBER_OBJECTS];
	Vector3f m_pos[NUMBER_OBJECTS];
	Vector3f m_decalage[NUMBER_OBJECTS];
	float m_pos3D[NUMBER_OBJECTS] = { 0 };
	int m_countObject = 0;
	int m_colorObject[NUMBER_OBJECTS] = { -1 };
	//int m_existObject[NUMBER_OBJECTS] = { -1 };
	Vector3f m_color[NUMBER_COLORS];
	int m_countColor = 0;
	Vector3f m_defaultColor;
	bool m_activeDefaultColor = false;
	int m_message[NUMBER_OBJECTS] = { 1 };

	float m_start[NUMBER_OBJECTS][NUMBER_PARTS] = {{ 0 }};
	float m_degres[NUMBER_OBJECTS][NUMBER_PARTS] = {{ 0 }};
	int m_sizeParts[NUMBER_PARTS] = { 1 };
	Vector3f m_posBig[NUMBER_OBJECTS][NUMBER_PARTS];
	Vector3f m_decalageBig[NUMBER_OBJECTS][NUMBER_PARTS];
};
