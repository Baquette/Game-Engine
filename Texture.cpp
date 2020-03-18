#include "stdafx.h"
#include "Texture.h"
#include "Globals.h"
#include <iostream>

Texture::Texture(TextureResource* source)
{
	this->source = new TextureResource();
	this->source->id = source->id;
	this->source->mag_filter = source->mag_filter;
	this->source->min_filter = source->min_filter;
	this->source->texturePath = Globals::copyString(source->texturePath);
	this->source->textureType = source->textureType;
	this->source->wrap_s = source->wrap_s;
	this->source->wrap_t = source->wrap_t;
	int err = glGetError();
	this->Load();
}

GLuint Texture::getBufferID()
{
	return this->bufferID;
}

GLenum Texture::getTextureType()
{
	return this->source->textureType;
}
Texture::~Texture()
{
	delete[] pixeli;
	glDeleteTextures(1, &bufferID);
	std::cout << "Destructor texture";
}

Texture* Texture::Load()
{
	
	int err = glGetError();
	//preluarea pixelilor din textura
	this->pixeli = LoadTGA(Globals::copyString(source->texturePath), &this->width, &this->heigth, &this->bpp);
	 
	//Generarea+deschiderea bufferului texturii
	glGenTextures(1, &(this->bufferID));
	glBindTexture(source->textureType, this->bufferID);
	err = glGetError();
	//Definirea Parametrilor din buffer
	glTexParameteri(source->textureType, GL_TEXTURE_MIN_FILTER, source->min_filter);
	err = glGetError();
	glTexParameteri(source->textureType, GL_TEXTURE_MAG_FILTER, source->mag_filter);
	err = glGetError();
	glTexParameteri(source->textureType, GL_TEXTURE_WRAP_S, source->wrap_s);

	glTexParameteri(source->textureType, GL_TEXTURE_WRAP_T, source->wrap_t);
	err = glGetError();
	GLenum rg;
	switch (this->bpp)
	{
	case 32: rg = GL_RGBA; break;
	case 24: rg = GL_RGB; break;
	}
	if (source->textureType == GL_TEXTURE_2D)
	{
		glTexImage2D(source->textureType, 0, rg, this->width, this->heigth, 0, rg, GL_UNSIGNED_BYTE, pixeli);
		
	}
	else if (source->textureType == GL_TEXTURE_CUBE_MAP)
	{
		  err = glGetError();
		glTexImage2D( GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, rg, this->width/4, this->heigth/3, 0, rg, GL_UNSIGNED_BYTE, 0);
		for (int i = 0; i < heigth / 3; i++)
		{
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, 0, i, width / 4, 1, rg, GL_UNSIGNED_BYTE, pixeli + i*width*(bpp / 8) + (width / 4)*(bpp / 8) + 2 * width*(bpp / 8)*(heigth / 3));
		}

		  err = glGetError();
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,   0, rg, this->width / 4, this->heigth / 3, 0, rg, GL_UNSIGNED_BYTE, 0);
		for (int i = 0; i < heigth / 3; i++)
		{
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, 0, i, width / 4, 1, rg, GL_UNSIGNED_BYTE, pixeli + i*width*(bpp / 8) + (width / 4)*(bpp / 8));
		}


		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, rg, this->width / 4, this->heigth / 3, 0, rg, GL_UNSIGNED_BYTE, 0);
		for (int i = 0; i < heigth / 3; i++)
		{
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, 0, i, width / 4, 1, rg, GL_UNSIGNED_BYTE, pixeli + i*width*(bpp / 8) + (width / 4)*(bpp / 8) + width*(bpp / 8)*(heigth / 3));
		}


		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0,rg, this->width / 4, this->heigth / 3, 0, rg, GL_UNSIGNED_BYTE, 0);
		for (int i = 0; i < heigth / 3; i++)
		{
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, 0, i, width / 4, 1, rg, GL_UNSIGNED_BYTE, pixeli + i*width*(bpp / 8) + 3 * (width / 4)*(bpp / 8) + width*(bpp / 8)*(heigth / 3));
		}


		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, rg, this->width / 4, this->heigth / 3, 0, rg, GL_UNSIGNED_BYTE, 0);
		for (int i = 0; i < heigth / 3; i++)
		{
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, 0, i, width / 4, 1, rg, GL_UNSIGNED_BYTE, pixeli + i*width*(bpp / 8) + 2 * (width / 4)*(bpp / 8) + width*(bpp / 8)*(heigth / 3));
		}


		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, rg, this->width / 4, this->heigth / 3, 0, rg, GL_UNSIGNED_BYTE, 0);
		for (int i = 0; i < heigth / 3; i++)
		{
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, 0, i, width / 4, 1, rg, GL_UNSIGNED_BYTE, pixeli + i*width*(bpp / 8) + width*(bpp / 8)*(heigth / 3));
		}
	}
	  err = glGetError();
	 
	//Inchiderea bufferului
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return this;
}