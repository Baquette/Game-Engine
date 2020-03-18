#include "stdafx.h"
#include "Fire.h"
#include <time.h>


Fire::Fire()
{
	u_Time = 0;
}
void Fire::sendFireData()
{
	if (shader->getFireDispMax() != -1)
	{
		glUniform1f(shader->getFireDispMax(), this->u_DispMax);
	}
	if (shader->getFireTime() != -1)
	{
		glUniform1f(shader->getFireTime(), this->u_Time);
	}
}
void Fire::Draw()
{

	this->sendCommonData();
	this->sendFireData();
	glDrawElements(GL_TRIANGLES, model->getIndicesNumber(), GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Fire::Update()
{
	u_Time += ((float)(clock())/CLOCKS_PER_SEC/1000);
	if (u_Time > 1)
		u_Time -= 1;
}
Fire::~Fire()
{
}

float Fire::getDispMax()
{
	return this->u_DispMax;
}

void Fire::setDispMax(float i)
{
	this->u_DispMax=i;
}

float Fire::getTime()
{
	return this->u_Time;
}

void Fire::setTime(float i)
{
    this->u_Time = i;
}