#pragma once
#include "../Utilities/utilities.h"

class Light
{
private:
	Vector3 position;
	Vector3 direction;
	Vector3 spectralColor;
	Vector3 diffuseColor;
	float specPower;
	char* type;
public:
	Vector3 getDirection();
	Vector3 getPosition();
	Vector3 getSpectralColor();
	Vector3 getDiffuseColor();
	float getSpecPower();
	void setDirection(Vector3);
	void setPosition(Vector3);
	void setSpectralColor(Vector3);
	void setDiffuseColor(Vector3);
	void setSpecPower(float);
	void setType(char*);
	void Draw();
	void Update();
	Light();
	~Light();
};

