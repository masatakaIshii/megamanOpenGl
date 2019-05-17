#pragma once

class Vector2f {
public:
	Vector2f();
	Vector2f(float posx, float posy);
	float x;
	float y;
};


class Vector3f {
public:
	Vector3f();
	Vector3f(float posx, float posy, float posz);
	float x;
	float y;
	float z;
};

class Vector4f {
public:
	Vector4f();
	Vector4f(float posx, float posy, float posz, float alpha);
	float x;
	float y;
	float z;
	float alpha;
};