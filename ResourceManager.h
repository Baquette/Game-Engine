#pragma once
#include <map>
  
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Globals.h"

#include "../Utilities/utilities.h"

class ResourceManager
{
private:
	static ResourceManager *instance;
	std::map<int, ModelResource*> models;
	std::map<int, ShaderResource*> shaders;
	std::map<int, TextureResource*> textures;
	std::map<int, Model*> loadedModels;
	std::map<int, Shader*> loadedShaders;
	std::map<int, Texture*> loadedTextures;
	const char *filePath = "../Resources/XMLS/resourceManager.xml";
	ResourceManager();
public:
	static ResourceManager* getInstance();
	Model* loadModel(int id);
	Shader* loadShader(int id);
	Texture* loadTexture(int id);

	~ResourceManager();
};