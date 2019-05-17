#pragma once
#include "vector.hpp"
#include "definitions.hpp"

class Object {
public:
	Object();
	Object(int indice, GLenum mode, float x, float y, float z);
	void AddObject(int indice, GLenum mode, float x, float y, float z);
	void AddObject(int indice, GLenum mode, float x, float y, float z, int indiceColor);
	void AddObject(int indice, GLenum mode, float x, float y, float z, float decalage);
	void AddObject(int indice, GLenum mode, float x, float y, float z, float decalage, float pos3D);
	void Addcolor(int indice, float red, float green, float blue);
	void SetColor(int indiceObject, int indiceColor);
	void SetDefaultColor(int indiceColor);
	void Show(int indice);
	void Show(int indice[], int size);
	void ShowAll();

private:
	void chooseColor(int indice);
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
};