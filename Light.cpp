#include "stdafx.h"
#include "Light.h"
#include "Globals.h"
void Light::Draw()
{

}

void Light::Update()
{

}
Light::Light()
{
}


Light::~Light()
{
}
Vector3 Light::getSpectralColor()
{
	return this->spectralColor;
}
Vector3 Light::getPosition()
{
	return this->position;
}
Vector3 Light::getDirection()
{
	return this->direction;
}
Vector3 Light::getDiffuseColor()
{
	return this->diffuseColor;
}
float Light::getSpecPower()
{
	return this->specPower;
}
void Light::setDiffuseColor(Vector3 col)
{
	this->diffuseColor = col;
}

void Light::setPosition(Vector3 pos)
{
	this->position = pos;
}

void Light::setSpecPower(float power)
{
	this->specPower = power;
}

void Light::setSpectralColor(Vector3 col)
{
	this->spectralColor = col;
}

void Light::setType(char* source)
{
	this->type = Globals::copyString(source);
}

void Light::setDirection(Vector3 direction)
{
	this->direction = direction;
}