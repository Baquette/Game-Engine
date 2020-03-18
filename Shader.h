#pragma once
#include "../Utilities/utilities.h"

struct ShaderResource {
	int id;
	char *vsPath;
	char *fsPath;
};

class Shader
{
private:
	int fragmentShader, vertexShader, shaderID;
	ShaderResource *source;
	GLint positionAttribute;
	GLint colourAttribute;
	GLint uv;
	GLint norm;
	GLint MVP;
	GLint high;
	GLint textureUniform[5];
	GLint uv2;
	GLint fogSmallRadius;
	GLint fogBigRadius;
	GLint fogColor;
	GLint modelMatrix;
	GLint cameraPos;
	GLint fireDispMax;
	GLint fireTime;
	GLint lightRatio;
	GLint lightAmbientColor;
	GLint lightSpectralColor;
	GLint lightDiffuseColor;
	GLint lightSpecPower;
	GLint lightDirection;
public:
	Shader(ShaderResource *source);
	~Shader();
	Shader* Load();
	GLint getLightRatio();
	GLint getLightAmbientColor();
	GLint getLightSpectralColor();
	GLint getLightDiffuseColor();
	GLint getLightSpecPower();
	GLint getLightDirection();
	GLint getObjectNorm();
	GLint getFireDispMax();
	GLint getFireTime();
	GLint getShaderID();
	GLint getPosition();
	GLint getColour();
	GLint getUV();
	GLint getHigh();
	GLint getMVP();
	GLint getTexture(int i);
	GLint getUV2();
	GLint getFogSmallRadius();
	GLint getFogBigRadius();
	GLint getFogColor();
	GLint getModelMatrix();
	GLint getCameraPos();
};

