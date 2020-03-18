#pragma once
#include "SceneObject.h"
class SkyBox : public SceneObject
{
public:
	SkyBox();
	~SkyBox();
	void Draw();
	void Update();
};

