#include "stdafx.h"
#include "Globals.h"
#include "Shader.h"
#include <iostream>

Shader::Shader(ShaderResource *source)
{
	this->source = new ShaderResource();
	this->source->fsPath = Globals::copyString(source->fsPath);
	this->source->vsPath = Globals::copyString(source->vsPath);
	this->source->id = source->id;
	this->Load();
}


Shader::~Shader()
{
	glDeleteProgram(shaderID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	std::cout << "Destructor shader";
}


Shader* Shader::Load()
{


	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, source->fsPath);
	
	vertexShader = esLoadShader(GL_VERTEX_SHADER, source->vsPath);

	shaderID = esLoadProgram(vertexShader, fragmentShader);

	positionAttribute = glGetAttribLocation(shaderID, "a_posL");
	colourAttribute = glGetAttribLocation(shaderID, "a_colour");
	MVP = glGetUniformLocation(shaderID, "u_MVP");
	uv = glGetAttribLocation(shaderID, "a_uv");
	norm = glGetAttribLocation(shaderID, "a_norm");
	textureUniform[0] = glGetUniformLocation(shaderID, "u_texture");
	textureUniform[1] = glGetUniformLocation(shaderID, "u_texture2");
	textureUniform[2] = glGetUniformLocation(shaderID, "u_texture3");
	textureUniform[3] = glGetUniformLocation(shaderID, "u_texture4");
	textureUniform[4] = glGetUniformLocation(shaderID, "u_texture5");
	uv2 = glGetAttribLocation(shaderID, "a_uv2");
	high = glGetUniformLocation(shaderID, "u_high");
	fogBigRadius = glGetUniformLocation(shaderID, "fogBigRadius");
	fogSmallRadius = glGetUniformLocation(shaderID, "fogSmallRadius");
	fogColor = glGetUniformLocation(shaderID, "fogColor");
	modelMatrix = glGetUniformLocation(shaderID, "modelMatrix");
	cameraPos = glGetUniformLocation(shaderID, "cameraPos");
	fireDispMax = glGetUniformLocation(shaderID, "fireDispMax");
	fireTime = glGetUniformLocation(shaderID, "fireTime");
	lightAmbientColor = glGetUniformLocation(shaderID, "lightAmbientColor");
	lightDiffuseColor = glGetUniformLocation(shaderID, "lightDiffuseColor");
	lightDirection = glGetUniformLocation(shaderID, "lightDirection");
	lightRatio = glGetUniformLocation(shaderID, "lightRatio");
	lightSpecPower = glGetUniformLocation(shaderID, "lightSpecPower");
	lightSpectralColor = glGetUniformLocation(shaderID, "lightSpectralColor");
	return this;
}
GLint Shader::getLightSpectralColor()
{
	return this->lightSpectralColor;
}
GLint Shader::getLightSpecPower()
{
	return this->lightSpecPower;
}
GLint Shader::getLightRatio()
{
	return this->lightRatio;
}
GLint Shader::getLightDirection()
{
	return this->lightDirection;
}
GLint Shader::getLightDiffuseColor()
{
	return this->lightAmbientColor;
}
GLint Shader::getLightAmbientColor()
{
	return this->lightAmbientColor;
}
GLint Shader::getObjectNorm()
{
	return this->norm;
}
GLint Shader::getFireDispMax()
{
	return this->fireDispMax;
}

GLint Shader::getFireTime()
{
	return this->fireTime;
}
GLint Shader::getCameraPos()
{
	return this->cameraPos;
}
GLint Shader::getUV2()
{
	return this->uv2;
}
int Shader::getShaderID()
{
	return this->shaderID;
}

GLint Shader::getColour()
{
	return this->colourAttribute;
}

GLint Shader::getMVP()
{
	return this->MVP;
}

GLint Shader::getPosition()
{
	return this->positionAttribute;
}

GLint Shader::getTexture(int i)
{
	return this->textureUniform[i];
}

GLint Shader::getUV()
{
	return this->uv;
}

GLint Shader::getModelMatrix()
{
	return this->modelMatrix;
}

GLint Shader::getHigh()
{
	return this->high;
}

GLint Shader::getFogBigRadius()
{
	return this->fogBigRadius;
}

GLint Shader::getFogSmallRadius()
{
	return this->fogSmallRadius;
}

GLint Shader::getFogColor()
{
	return this->fogColor;
}