#pragma once
#include <vector>
#include "Globals.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "Light.h"
#include "../Utilities/utilities.h"

class SceneObject
{
protected:
	int id;
	char* type;
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Model* model;
	Shader* shader;
	std::vector<Texture*> textures;
	Light* lights;
	bool depthTest;
	bool wiredFormat;
	bool folCam;
	int camera;
public:
	/*SceneObject(int id);
	SceneObject(int id, Vector3 position);
	SceneObject(int id, Vector3 position, Vector3 rotation);
	SceneObject(int id, Vector3 position, Vector3 rotation, Vector3 scale);
	SceneObject(int id, Vector3 position, Vector3 rotation, Vector3 scale, Model* model);
	SceneObject(int id, Vector3 position, Vector3 rotation, Vector3 scale, Model* model, Shader* shader);
	SceneObject(int id, Vector3 position, Vector3 rotation, Vector3 scale, Model* model, Shader* shader, vector<Texture*> textures);*/
	SceneObject();
	SceneObject(int id, Vector3 position, Vector3 rotation, Vector3 scale, Model* model, Shader* shader, std::vector<Texture*> textures, bool depthTest);
	~SceneObject();
	virtual void Update();
	virtual void Draw();
	void sendCommonData();
	  bool followsCamera();

	void setID(int id);
	std::vector<Texture*> getTextures();
	void setType(char *type);
	void setPosition(Vector3);
	void setRotation(Vector3);
	void setScale(Vector3);
	void setModel(Model*);
	void setShader(Shader*);
	void addTexture(Texture*);
	void addLight(Light*);
	void setDepth(bool);
	void setWired(bool);
	bool isTerrain();
	bool isSky();
	 void setFollowsCamera(int );
};

