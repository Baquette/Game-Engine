#include "stdafx.h"
#include "rapidxml.hpp"
#include "ResourceManager.h"
 
 
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;
using namespace rapidxml;



ResourceManager::ResourceManager()
{
	std::ifstream f(filePath);
	std::stringstream buf;
	buf << f.rdbuf();
	f.close();
	std::string content(buf.str());
	xml_document<> doc;
	doc.parse<0>(&content[0]);

	xml_node<> *parinte = doc.first_node("resourceManager");

	//Citirea modelelor =========================
	xml_node<> *modele = parinte->first_node("models");
	for (xml_node<> *nod = modele->first_node("model"); nod; nod = nod->next_sibling("model"))
	{

		ModelResource *model = new ModelResource();
		model->id = Globals::stringToNumber(nod->first_attribute("id")->value());
		model->filePath = Globals::copyString(nod->first_node()->value());
		this->models.insert(std::pair<int, ModelResource*>(model->id, model));
	}

	//Citirea shaderelor ==========================
	xml_node<> *shadere = parinte->first_node("shaders");
	for (xml_node<> *nod = shadere->first_node("shader"); nod; nod = nod->next_sibling("shader"))
	{
		ShaderResource *shader= new ShaderResource();
		
		shader->id = Globals::stringToNumber(nod->first_attribute("id")->value());
		shader->vsPath = Globals::copyString(nod->first_node("vs")->value());
		shader->fsPath = Globals::copyString(nod->first_node("fs")->value());
		this->shaders.insert(std::pair<int, ShaderResource*>(shader->id, shader));
	}

	//Citirea texturilor ===============================

	xml_node<> *texture = parinte->first_node("textures");
	for (xml_node<> *nod = texture->first_node("texture"); nod; nod = nod->next_sibling("texture"))
	{
		TextureResource *textura = new TextureResource();
		textura->id = Globals::stringToNumber(nod->first_attribute("id")->value());
		if (strcmp(nod->first_attribute("type")->value(), "2d")==0)
		{
			textura->textureType = GL_TEXTURE_2D;
		}
		else if (strcmp(nod->first_attribute("type")->value(), "cube") == 0)
		{
			textura->textureType = GL_TEXTURE_CUBE_MAP;
		}
		textura->texturePath = Globals::copyString(nod->first_node("path")->value());


		if (strcmp(nod->first_node("min_filter")->value(), "LINEAR") == 0)
		{
			textura->min_filter = GL_LINEAR;
		}
		else if (strcmp(nod->first_node("min_filter")->value(), "CLAMP_TO_EDGE") == 0)
		{
			textura->min_filter = GL_CLAMP_TO_EDGE;
		}
		else if (strcmp(nod->first_node("min_filter")->value(), "NEAREST") == 0)
		{
			textura->min_filter = GL_NEAREST;
		}


		if(strcmp(nod->first_node("mag_filter")->value(), "LINEAR") == 0)
		{
			textura->mag_filter = GL_LINEAR;
		}
		else if (strcmp(nod->first_node("mag_filter")->value(), "NEAREST") == 0)
		{
			textura->mag_filter = GL_NEAREST;
		}
		else if (strcmp(nod->first_node("mag_filter")->value(), "CLAMP_TO_EDGE") == 0)
		{
			textura->mag_filter = GL_CLAMP_TO_EDGE;
		}


		if (strcmp(nod->first_node("wrap_s")->value(), "CLAMP_TO_EDGE") == 0)
		{
			textura->wrap_s = GL_CLAMP_TO_EDGE;
		}
		else if(strcmp(nod->first_node("wrap_s")->value(), "REPEAT") == 0)
		{
			textura->wrap_s = GL_REPEAT;
		}
		else if (strcmp(nod->first_node("wrap_s")->value(), "MIRRORED_REPEAT") == 0)
		{
			textura->wrap_s = GL_MIRRORED_REPEAT;
		}
		else if (strcmp(nod->first_node("wrap_s")->value(), "LINEAR") == 0)
		{
			textura->wrap_s = GL_LINEAR;
		}

		if (strcmp(nod->first_node("wrap_t")->value(), "CLAMP_TO_EDGE") == 0)
		{
			textura->wrap_t = GL_CLAMP_TO_EDGE;
		}
		else if (strcmp(nod->first_node("wrap_t")->value(), "REPEAT") == 0)
		{
			textura->wrap_t = GL_REPEAT;
		}
		else if (strcmp(nod->first_node("wrap_t")->value(), "MIRRORED_REPEAT") == 0)
		{
			textura->wrap_t = GL_MIRRORED_REPEAT;
		}
		else if (strcmp(nod->first_node("wrap_t")->value(), "LINEAR") == 0)
		{
			textura->wrap_t = GL_LINEAR;
		}


		this->textures.insert(std::pair<int, TextureResource*>(textura->id, textura));
	}
	cout << "testing" << endl;
}

Model* ResourceManager::loadModel(int id)
{
	if (loadedModels.find(id) != loadedModels.end())
	{
		return loadedModels.find(id)->second;
	}
	else
	{
		loadedModels.insert(std::pair<int, Model*>(id, new Model(models.find(id)->second)));
		return loadedModels.find(id)->second;
	}
}


Shader* ResourceManager::loadShader(int id)
{
	if (loadedShaders.find(id) != loadedShaders.end())
	{
		return loadedShaders.find(id)->second;
	}
	else
	{
		loadedShaders.insert(std::pair<int, Shader*>(id, new Shader(shaders.find(id)->second)));
		return loadedShaders.find(id)->second;
	}
}


Texture* ResourceManager::loadTexture(int id)
{
	if (loadedTextures.find(id) != loadedTextures.end())
	{
		return loadedTextures.find(id)->second;
	}
	else
	{
		loadedTextures.insert(std::pair<int, Texture*>(id, new Texture(textures.find(id)->second)));
		return loadedTextures.find(id)->second;
	}
}


ResourceManager::~ResourceManager()
{

}

ResourceManager* ResourceManager::getInstance()
{
	if (!instance)
	{
		instance = new ResourceManager();
	}
	return instance;
}

ResourceManager* ResourceManager::instance;