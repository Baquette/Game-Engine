#include "stdafx.h"
#include "rapidxml.hpp"
#include "SceneManager.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "SkyBox.h"
#include "Fire.h"
#include <iterator>
#include <string.h>


using namespace std;
using namespace rapidxml;
float SceneManager::getLightRatio()
{
	return this->lightRatio;
}
Vector3 SceneManager::getAmbientColor()
{
	return this->AmbientColor;
}
Camera* SceneManager::getCamera(int index)
{
	if (cameras.find(index) != cameras.end())
	{
		return cameras.find(activeCamera)->second;
	}
}
void SceneManager::Update()
{
	for (std::map<int, SceneObject*>::iterator it = this->obiecte.begin(); it != this->obiecte.end(); it++)
	{
		it->second->Update();
	}
}
void SceneManager::Draw()
{
	for (std::map<int, SceneObject*>::iterator it = this->obiecte.begin(); it != this->obiecte.end(); it++)
	{
		it->second->Draw();
	}
}

Camera* SceneManager::getActiveCamera()
{
	if (cameras.find(activeCamera) != cameras.end())
	{
		return cameras.find(activeCamera)->second;
	}
}
float SceneManager::getFogBigRadius()
{
	return this->fogBigRadius;
}
float SceneManager::getFogSmallRadius()
{
	return this->fogSmallRadius;
}
Vector3 SceneManager::getFogColor()
{
	return this->fogColor;
}
SceneManager::SceneManager()
{
	std::ifstream f(filePath);
	std::stringstream buf;
	buf << f.rdbuf();
	f.close();
	std::string content(buf.str());
	xml_document<> doc;
	doc.parse<0>(&content[0]);

	xml_node<> *parinte = doc.first_node("sceneManager");
	xml_node<> *bgcolor = parinte->first_node("backgroundColor");
	this->backgroundColor = Vector3((GLfloat)Globals::stringToFloat(bgcolor->first_node("r")->value()), Globals::stringToFloat(bgcolor->first_node("g")->value()), Globals::stringToFloat(bgcolor->first_node("b")->value()));
	//Definirea ratiei luminii si culoarea luminii ambientale
	this->AmbientColor = Vector3(Globals::stringToFloat(parinte->first_node("ambientLight")->first_node("r")->value()), Globals::stringToFloat(parinte->first_node("ambientLight")->first_node("g")->value()), Globals::stringToFloat(parinte->first_node("ambientLight")->first_node("b")->value()));
	this->lightRatio = Globals::stringToFloat(parinte->first_node("lightRatio")->value());


	//Definirea cetii

	xml_node<> *ceata = parinte->first_node("fog");
	this->fogSmallRadius = Globals::stringToFloat(ceata->first_node("smallRadius")->value());
	this->fogBigRadius = Globals::stringToFloat(ceata->first_node("bigRadius")->value());
	this->fogColor = Vector3(Globals::stringToFloat(ceata->first_node("colour")->first_node("r")->value()), Globals::stringToFloat(ceata->first_node("colour")->first_node("g")->value()), Globals::stringToFloat(ceata->first_node("colour")->first_node("b")->value()));
	
	
	//Definirea camerelor
	xml_node<> *cameras = parinte->first_node("cameras");

	for (xml_node<> *camera = cameras->first_node("camera"); camera; camera = camera->next_sibling())
	{
		xml_node<> *position = camera->first_node("position");
		xml_node<> *target = camera->first_node("target");
		xml_node<> *up = camera->first_node("up");
		Vector3 pos = Vector3((GLfloat)Globals::stringToFloat(position->first_node("x")->value()), (GLfloat)Globals::stringToFloat(position->first_node("y")->value()), (GLfloat)Globals::stringToFloat(position->first_node("z")->value()));
		Vector3 tar = Vector3((GLfloat)Globals::stringToFloat(target->first_node("x")->value()), (GLfloat)Globals::stringToFloat(target->first_node("y")->value()), (GLfloat)Globals::stringToFloat(target->first_node("z")->value()));
		Vector3 u = Vector3((GLfloat)Globals::stringToFloat(up->first_node("x")->value()), (GLfloat)Globals::stringToFloat(up->first_node("y")->value()), (GLfloat)Globals::stringToFloat(up->first_node("z")->value()));
		this->cameras.insert(std::pair<int, Camera*>(Globals::stringToNumber(camera->first_attribute("id")->value()), new Camera(pos, tar, Globals::stringToFloat(camera->first_node("rotationSpeed")->value()), Globals::stringToFloat(camera->first_node("translationSpeed")->value()), Globals::stringToFloat(camera->first_node("fov")->value()), Globals::stringToFloat(camera->first_node("near")->value()), Globals::stringToFloat(camera->first_node("far")->value()))));

	}
	this->activeCamera = Globals::stringToNumber(parinte->first_node("activeCamera")->value());

	//Definirea obiectelor din scena
	for (xml_node<> *obiect = parinte->first_node("objects")->first_node("object"); obiect; obiect = obiect->next_sibling())
	{
		SceneObject *object;
		char* type = obiect->first_node("type")->value();
	
		if (strcmp("normal", type) == 0)
		{
			object = new SceneObject();
		}//Else se creeaza alt tip de obiect
		else if (strcmp("terrain", type) == 0)
		{
			TerrainObject *teren = new TerrainObject();
			//Stabilirea culorii 
			xml_node<> *color = obiect->first_node("color");
			Vector3 colour= Vector3((GLfloat)Globals::stringToFloat(color->first_node("r")->value()), Globals::stringToFloat(color->first_node("g")->value()), Globals::stringToFloat(color->first_node("b")->value()));
			teren->setColor(colour);
			xml_node<> *hig = obiect->first_node("high");
			Vector3 high = Vector3((GLfloat)Globals::stringToFloat(hig->first_node("r")->value()), (GLfloat)Globals::stringToFloat(hig->first_node("g")->value()),(GLfloat)Globals::stringToFloat(hig->first_node("b")->value()));
			teren->setHigh(high);
			teren->setVerticalCellsNumber(Globals::stringToNumber(obiect->first_node("Ycells")->value()));
			teren->setHorizontalCellsNumber(Globals::stringToNumber(obiect->first_node("Xcells")->value()));
			teren->setOffSetY(Globals::stringToNumber(obiect->first_node("offsetY")->value()));
			teren->setcellScale(Globals::stringToFloat(obiect->first_node("cellScale")->value()));
			teren->setOrigin(getActiveCamera()->getPosition());
			teren->generateModel();
			object = teren;
		}
		else if (strcmp("skybox", type) == 0)
		{
			SkyBox *sky = new SkyBox();
			object = sky;
		}
		else if (strcmp("fire", type) == 0)
		{
			Fire *foc = new Fire();
			foc->setDispMax(Globals::stringToFloat(obiect->first_node("dispMax")->value()));
			object = foc;
		}
		object->setType(type);
		//Stabilirea modelului
		int objectID = Globals::stringToNumber(obiect->first_attribute("id")->value());
		object->setID(objectID);
		char* modelID = obiect->first_node("model")->value();
		if (Globals::isNumber(modelID))
		{
			int err = glGetError();
			object->setModel(ResourceManager::getInstance()->loadModel(Globals::stringToNumber(modelID)));
			
		}//Else daca este generat etc
		
		//Stabilirea shaderului
		object->setShader(ResourceManager::getInstance()->loadShader(Globals::stringToNumber(obiect->first_node("shader")->value())));
		
		//Adaugarea texturilor
		for (xml_node<> *textura = obiect->first_node("textures")->first_node("texture"); textura; textura = textura->next_sibling())
		{
			int errshader = glGetError();
			object->addTexture(ResourceManager::getInstance()->loadTexture(Globals::stringToNumber(textura->first_attribute("id")->value())));
		}
		 
		//Stabilirea translatiei
		Vector3 translation = Vector3(Globals::stringToFloat(obiect->first_node("position")->first_node("x")->value()), Globals::stringToFloat(obiect->first_node("position")->first_node("y")->value()), Globals::stringToFloat(obiect->first_node("position")->first_node("z")->value()));
		object->setPosition(translation);


		//Stabilirea rotatiei
		Vector3 rotation= Vector3(Globals::stringToFloat(obiect->first_node("rotation")->first_node("x")->value()), Globals::stringToFloat(obiect->first_node("rotation")->first_node("y")->value()), Globals::stringToFloat(obiect->first_node("rotation")->first_node("z")->value()));
		object->setRotation(rotation);

		//Stabilirea scalarii
		Vector3 scale= Vector3(Globals::stringToFloat(obiect->first_node("scale")->first_node("x")->value()), Globals::stringToFloat(obiect->first_node("scale")->first_node("y")->value()), Globals::stringToFloat(obiect->first_node("scale")->first_node("z")->value()));
		object->setScale(scale);

		//Identificarea camerei care urmareste obiectul 
		xml_node<> *folCam = obiect->first_node("folCam");
		if (folCam)
		{
			object->setFollowsCamera(Globals::stringToNumber(folCam->value()));
		}

		//Introducerea in map a obiectului creat
		this->obiecte.insert(std::pair<int, SceneObject*>(objectID,object));
	}

	//Definirea luminilor in scena

	for (xml_node<> *lumina = parinte->first_node("lights")->first_node("light"); lumina; lumina = lumina->next_sibling())
	{
		Light *light=new Light();

		//id-ul luminii
		int id = Globals::stringToNumber(lumina->first_attribute("id")->value());

		//legatura cu obiectul
		if (obiecte.find(Globals::stringToNumber(lumina->first_node("associatedObject")->value())) != obiecte.end())
		{
			int index= Globals::stringToNumber(lumina->first_node("associatedObject")->value());;
			if (obiecte.find(index) != obiecte.end())
			{
				obiecte.find(index)->second->addLight(light);
			}
		}

		//culoarea difuza

		light->setDiffuseColor(Vector3(Globals::stringToFloat(lumina->first_node("diffuseColor")->first_node("r")->value()), Globals::stringToFloat(lumina->first_node("diffuseColor")->first_node("g")->value()), Globals::stringToFloat(lumina->first_node("diffuseColor")->first_node("b")->value())));

		//culoarea speculara

		light->setSpectralColor(Vector3(Globals::stringToFloat(lumina->first_node("specularColor")->first_node("r")->value()), Globals::stringToFloat(lumina->first_node("specularColor")->first_node("g")->value()), Globals::stringToFloat(lumina->first_node("specularColor")->first_node("b")->value())));

		//pozitia luminii

		light->setPosition(Vector3(Globals::stringToFloat(lumina->first_node("position")->first_node("x")->value()), Globals::stringToFloat(lumina->first_node("position")->first_node("y")->value()), Globals::stringToFloat(lumina->first_node("position")->first_node("z")->value())));

		//spec power

		light->setSpecPower(Globals::stringToFloat(lumina->first_node("specPower")->value()));

		//directia luminii

		light->setDirection(Vector3(Globals::stringToFloat(lumina->first_node("direction")->first_node("x")->value()), Globals::stringToFloat(lumina->first_node("direction")->first_node("y")->value()), Globals::stringToFloat(lumina->first_node("direction")->first_node("z")->value())));

		//tipul luminii

		light->setType(lumina->first_node("type")->value());

		this->lights.insert(std::pair<int, Light*>(id, light));

	}
}

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::getInstance()
{
	if (!instance)
	{
		instance = new SceneManager();
	}
	return instance;
}

SceneManager* SceneManager::instance;
