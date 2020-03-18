#include "stdafx.h"
#include "SceneObject.h"
#include <iostream>
#include <vector>
#include "SceneManager.h"
SceneObject::SceneObject(int id, Vector3 position, Vector3 rotation, Vector3 scale, Model* model, Shader* shader, std::vector<Texture*> textures, bool depthTest)
{
	this->type = "normal";
	this->id = id;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	this->model = model;
	this->shader = shader;
	this->textures = textures;
	this->depthTest = depthTest;
	this->wiredFormat = false;
	this->folCam = false;
}

SceneObject::SceneObject()
{
}
void SceneObject::setDepth(bool depthTest)
{
	this->depthTest = depthTest;
}

bool SceneObject::followsCamera()
{
	return this->folCam;
}

void SceneObject::setFollowsCamera(int i)
{
	this->camera = i;
	this->folCam = true;
}
void SceneObject::setID(int id)
{
	this->id = id;
}

void SceneObject::setModel(Model* model)
{
	this->model = model;
}

void SceneObject::setPosition(Vector3 position)
{
	this->position = position;
}

void SceneObject::setRotation(Vector3 rotation)
{
	this->rotation = rotation;
}

void SceneObject::setScale(Vector3 scale)
{
	this->scale = scale;
}

void SceneObject::setShader(Shader* shader)
{
	this->shader = shader;
}

void SceneObject::setType(char* type)
{
	this->type = Globals::copyString(type);
}

bool SceneObject::isTerrain()
{
	if (strcmp(this->type, "terrain") == 0)
		return true;
	else
		return false;
}

bool SceneObject::isSky()
{
	if (strcmp(this->type, "skybox") == 0)
		return true;
	else
		return false;
}
void SceneObject::setWired(bool wired)
{
	this->wiredFormat = wired;
}

void SceneObject::addTexture(Texture* textura)
{
	this->textures.insert(this->textures.end(),textura);
}
SceneObject::~SceneObject()
{
}
void SceneObject::addLight(Light* light)
{
	this->lights = light;
}
void SceneObject::sendCommonData()
{

	// pregatirea shader-ului
	int err = glGetError();
	glUseProgram(shader->getShaderID());
	Matrix aux;

	for (std::vector<int>::size_type i = 0; i != textures.size(); i++)
	{

		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(textures[i]->getTextureType(), textures[i]->getBufferID());
		if (shader->getTexture(i) != -1)
		{
			glUniform1i(shader->getTexture(i), i);
		}
	}


	glBindBuffer(GL_ARRAY_BUFFER, model->getVertexesBufferID());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->getIndicesBufferID());
	if (shader->getPosition() != -1)
	{
		glEnableVertexAttribArray(shader->getPosition());
		glVertexAttribPointer(shader->getPosition(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (shader->getColour() != -1)
	{
		glEnableVertexAttribArray(shader->getColour());
		glVertexAttribPointer(shader->getColour(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
	}

	if (shader->getObjectNorm() != -1)
	{
		glEnableVertexAttribArray(shader->getObjectNorm());
		glVertexAttribPointer(shader->getObjectNorm(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(Vector3)));
	}
	Matrix S; S.SetScale(scale);
	Matrix RotX; RotX.SetRotationX(rotation.x);
	Matrix RotY; RotY.SetRotationY(rotation.y);
	Matrix RotZ; RotZ.SetRotationZ(rotation.z);
	Matrix T; T.SetTranslation(position);
	Matrix x = S*RotX*RotY*RotZ*T*SceneManager::getInstance()->getActiveCamera()->getViewMatrix()*SceneManager::getInstance()->getActiveCamera()->getPerspective();
	if (shader->getMVP() != -1)
	{
		glUniformMatrix4fv(shader->getMVP(), 1, GL_FALSE, (GLfloat*)x.m);
	}

	if (shader->getUV() != -1)
	{
		glEnableVertexAttribArray(shader->getUV());
		glVertexAttribPointer(shader->getUV(), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) * 5));
	}

	if (shader->getUV2() != -1)
	{
		glEnableVertexAttribArray(shader->getUV2());
		glVertexAttribPointer(shader->getUV2(), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) * 5 + sizeof(Vector2)));
	}

	if (shader->getFogColor() != -1)
	{
		glUniform3f(shader->getFogColor(), SceneManager::getInstance()->getFogColor().x, SceneManager::getInstance()->getFogColor().y, SceneManager::getInstance()->getFogColor().z);
	}

	if (shader->getFogBigRadius() != -1)
	{
		glUniform1f(shader->getFogBigRadius(), SceneManager::getInstance()->getFogBigRadius());
	}

	if (shader->getFogSmallRadius() != -1)
	{
		glUniform1f(shader->getFogSmallRadius(), SceneManager::getInstance()->getFogSmallRadius());
	}

	if (shader->getModelMatrix() != -1)
	{
		glUniformMatrix4fv(shader->getModelMatrix(), 1, GL_FALSE, (GLfloat*)(S*RotX*RotY*RotZ*T).m);
	}
	
	if (shader->getCameraPos() != -1)
	{
		glUniform3f(shader->getCameraPos(), SceneManager::getInstance()->getActiveCamera()->getPosition().x, SceneManager::getInstance()->getActiveCamera()->getPosition().y, SceneManager::getInstance()->getActiveCamera()->getPosition().z);
	}

	if (shader->getLightRatio() != -1)
	{
		glUniform1f(shader->getLightRatio(), SceneManager::getInstance()->getLightRatio());
	}

	if (shader->getLightAmbientColor() != -1)
	{
		glUniform3f(shader->getLightAmbientColor(), SceneManager::getInstance()->getAmbientColor().x, SceneManager::getInstance()->getAmbientColor().y, SceneManager::getInstance()->getAmbientColor().z);
	}

	if (shader->getLightDiffuseColor() != -1)
	{
		glUniform3f(shader->getLightDiffuseColor(), this->lights->getDiffuseColor().x, this->lights->getDiffuseColor().y, this->lights->getDiffuseColor().z);
	}
	
	if (shader->getLightDirection() != -1)
	{
		glUniform3f(shader->getLightDirection(), this->lights->getDirection().x, this->lights->getDirection().y, this->lights->getDirection().z);
	}

	if (shader->getLightSpecPower() != -1)
	{
		glUniform1f(shader->getLightSpecPower(), this->lights->getSpecPower());
	}

	if (shader->getLightSpectralColor() != -1)
	{
		glUniform3f(shader->getLightSpectralColor(), this->lights->getSpectralColor().x, this->lights->getSpectralColor().y, this->lights->getSpectralColor().z);
	}
}
void SceneObject::Update()
{

}
void SceneObject::Draw( )
{

	this->sendCommonData();
	glDrawElements(GL_TRIANGLES, model->getIndicesNumber(), GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

std::vector<Texture*> SceneObject::getTextures()
{
	return this->textures;
}