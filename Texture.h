#pragma once

#include "../Utilities/TGA.h"
#include "../Utilities/utilities.h"
struct TextureResource {
	int id;
	char *texturePath;
	GLenum textureType;
	GLenum min_filter;
	GLenum mag_filter;
	GLenum wrap_s;
	GLenum wrap_t;
};

class Texture
{
private:
	GLuint bufferID;
	TextureResource *source;

	char *pixeli;
	int width;
	int heigth;
	int bpp;
public:
	Texture(TextureResource*);
	GLuint getBufferID();
	GLenum getTextureType();
	~Texture();
	Texture* Load();
};

