//#pragma once
#include "vector.hpp"

Vector2f::Vector2f()
{

}

Vector2f::Vector2f(float posx, float posy)
{
	x = posx;
	y = posy;
}

Vector3f::Vector3f()
{

}

Vector3f::Vector3f(float posx, float posy, float posz)
{
	x = posx;
	y = posy;
	z = posz;
}

Vector4f::Vector4f()
{

}

Vector4f::Vector4f(float posx, float posy, float posz, float alphaColor)
{
	x = posx;
	y = posy;
	z = posz;
	alpha = alphaColor;
}
