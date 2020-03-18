#pragma once
#include <map>
#include "Camera.h"
#include "Globals.h"
#include "SceneObject.h"
#include "Light.h"
#include "TerrainObject.h"
#include "ResourceManager.h"
#include "../Utilities/utilities.h"
 
class SceneManager
{
private:
	float lightRatio;
	Vector3 AmbientColor;
	static SceneManager* instance;
	std::map<int, Camera*> cameras;
	std::map<int, Light*> lights;
	Vector3 backgroundColor;
	std::map<int, SceneObject*> obiecte;
	char* filePath = "../Resources/XMLS/sceneManager.xml";
	int activeCamera;
	float fogSmallRadius;
	float fogBigRadius;
	Vector3 fogColor;
public:
	float getLightRatio();
	Vector3 getAmbientColor();
	Camera* getActiveCamera();
	Camera* getCamera(int);
	Vector3 getFogColor();
	float getFogSmallRadius();
	float getFogBigRadius();
	SceneManager();
	static SceneManager* getInstance();
	~SceneManager();
	void Draw();
	void Update();
};

