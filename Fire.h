#pragma once
#include "SceneObject.h"
class Fire :
	public SceneObject
{
private:
	float u_DispMax;
	float u_Time;
public:
	void sendFireData();
	float getDispMax();
	float getTime();
	void setTime(float);
	void setDispMax(float);
	void Draw();
	void Update();
	Fire();
	~Fire();
};

