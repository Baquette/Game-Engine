#include "stdafx.h"
#include "TerrainObject.h"
#include <iostream>
#include "SceneManager.h"

void TerrainObject::updateOrigin()
{
	this->origin = SceneManager::getInstance()->getActiveCamera()->getPosition();
	this->origin.y = this->offsetY;
	this->position = this->origin;
}
void TerrainObject::setOrigin(Vector3 origin)
{
	this->origin = origin;
	this->origin.y = this->offsetY;
	this->position = this->origin;
}
Vector3 TerrainObject::getOrigin()
{
	return this->origin;
}
TerrainObject::TerrainObject()
{
	instanta = this;
}

float TerrainObject::getcellScale()
{
	return this->cellScale;
}

TerrainObject::~TerrainObject()
{
}

void TerrainObject::setOffSetY(int x)
{
	this->offsetY = x;
}

void TerrainObject::setHorizontalCellsNumber(int i)
{
	this->horizontalCells = i;
}

float TerrainObject::getY()
{
	return this->offsetY;
}

void TerrainObject::setcellScale(float i)
{
	this->cellScale = i;
}

TerrainObject* TerrainObject::getTeren()
{
	return instanta;
}
void TerrainObject::setVerticalCellsNumber(int i)
{
	this->verticalCells = i;
}
void TerrainObject::generateModel()
{
	this->model = new Model();
	float vertZ =  this->origin.y-(this->cellScale*this->verticalCells / 2);
	float vertX =  this->origin.x-(this->cellScale*this->horizontalCells / 2);
	 
	Vertex* vertexes = new Vertex[(this->verticalCells + 1)*(this->horizontalCells + 1)];
	int count = 0;
	float ux = 0;
	float uy = 0;
	for (int i = 0; i <= this->verticalCells; i++)
	{
		float vertX = this->origin.x - (this->cellScale*this->horizontalCells / 2);
		ux = 0;
		for (int j = 0; j <= this->horizontalCells; j++)
		{
			vertexes[count].pos = Vector3(vertX, this->offsetY, vertZ);
			vertexes[count].uv  = Vector2(ux,uy);
			vertexes[count].uv2 = Vector2(j, i);
			 
			ux += (float)((float)1 / (float)this->horizontalCells);
			count++;
			vertX += this->cellScale;
		}
		uy += (float)((float)1 / (float)this->verticalCells);
		vertZ += this->cellScale;
	}
	this->model->setVertices(vertexes);
	this->model->setVerticesNumber((this->verticalCells + 1)*(this->horizontalCells + 1));
	GLushort* indices=new GLushort[6*this->verticalCells*this->horizontalCells];
	int k = 0;
	for (int i = 0; i < this->verticalCells; i++)
	{
		for (int j = 0; j < this->horizontalCells; j++)
		{
			indices[k++] = i*(this->verticalCells + 1) + j;
			indices[k++] = i*(this->verticalCells + 1) + j + 1;
			indices[k++] = (i + 1)*(this->verticalCells + 1) + j;
			indices[k++] = i*(this->verticalCells + 1) + j + 1;
			indices[k++] = (i + 1)*(this->verticalCells + 1) + j;
			indices[k++] = (i + 1)*(this->verticalCells + 1) + j + 1;
			
		}
	}
	this->model->setIndices(indices);
	this->model->setIndicesNumber(6 * this->verticalCells*this->horizontalCells);
	this->model->Load();
	 

}

void TerrainObject::setColor(Vector3 color)
{
	this->color = color;
}

void TerrainObject::setHigh(Vector3 high)
{
	this->high = high;
}

void TerrainObject::sendTerrainData() 
{
	if (shader->getHigh() != -1)
	{
		glUniform3f(shader->getHigh(), high.x, high.y, high.z);
	}
}
void TerrainObject::Update()
{
	float dx = SceneManager::getInstance()->getActiveCamera()->getPosition().x - position.x;
	float dz = SceneManager::getInstance()->getActiveCamera()->getPosition().z - position.z;

	if (abs(dx) > cellScale)
	{
		if (dx < 0)
		{
			this->model->updateUVx((float)-1 / horizontalCells);
			this->position.x -= cellScale;
		}
		else
		{
			this->model->updateUVx((float)1 / horizontalCells);
			this->position.x += cellScale;
		}
		
	}
	else if (abs(dz) > cellScale)
	{
		if (dz < 0)
		{
			this->model->updateUVy((float)-1 / verticalCells);
			this->position.z -= cellScale;
		}
		else
		{
			this->model->updateUVy((float)1 / verticalCells);
			this->position.z += cellScale;
		}
	}
}
void TerrainObject::Draw()
{
	this->sendTerrainData();
	this->sendCommonData();
	 
	 
	glDrawElements(GL_TRIANGLES, model->getIndicesNumber(), GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void TerrainObject::updateX(float x)
{
	 
	this->model->updateUVx((float)1/x);
}
void TerrainObject::updateZ(float x)
{
  
	this->model->updateUVy((float)1/x);
}

TerrainObject* TerrainObject::instanta;