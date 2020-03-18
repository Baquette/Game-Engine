#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
#include "Model.h"
#include "FileReader.h"
#include "Vertex.h"
#include "Globals.h"
#include "../Utilities/utilities.h"

Model::Model(ModelResource* source)
{
	this->source = new ModelResource();
	this->source->filePath = Globals::copyString(source->filePath);
	this->source->id = source->id;
	int vertex = 0;
	std::ifstream model(source->filePath);
	if (model.is_open())
	{
		std::string line;
		std::getline(model, line);
		for (std::string::size_type i = 0; i<line.size(); i++)
		{
			if (line[i] == ' ')
			{
				int k = 0;
				i++;

				int op = i;
				while (line[i] <= '9'&&line[i] >= '0')
				{
					i++;
				}
				for (std::string::size_type j = i - 1; j >= op; j--)
				{
					vertex += pow(10, k)*(line[j] - '0');
					k++;
				}
			}
		}
		this->vertexNumber = vertex;
		this->verticesData = new Vertex[vertex];
		for (int l = 0; l < vertex; l++)
		{
			std::getline(model, line);
			int op = 0;
			for (std::string::size_type i = 0; i < line.size(); i++)
			{
				float b = 0;

				if (line[i] == '[')
				{
					for (int j = 0; j < 3; j++)
					{
						b = 0;
						while (line[i] != '.')
						{

							i++;
						}
						std::string::size_type x = i - 1;
						int k = 0;
						while (line[x] >= '0'&&line[x] <= '9')
						{
							b += (float)pow(10, k)*(line[x] - '0');
							x--;
							k++;
						}
						int ok = 0;
						if (line[x] == '-')
						{
							ok = 1;
						}
						i++;
						k = -1;
						while (line[i] != ',')
						{
							b += (float)pow(10, k)*(line[i] - '0');
							i++; k--;
							if (line[i] == ']' || line[i] == ';')
							{

								break;
							}
						}
						if (ok == 1)
						{
							b = b - 2 * b;
						}

						switch (op)
						{
						case 0:switch (j)
						{
						case 0:verticesData[l].pos.x = (GLfloat)b; break;
						case 1:verticesData[l].pos.y = (GLfloat)b; break;
						case 2:verticesData[l].pos.z = (GLfloat)b; break;
						}break;
						case 1:switch (j)
						{
						case 0:verticesData[l].norm.x = (GLfloat)b; break;
						case 1:verticesData[l].norm.y = (GLfloat)b; break;
						case 2:verticesData[l].norm.z = (GLfloat)b; break;
						}break;
						case 2:switch (j)
						{
						case 0:verticesData[l].binorm.x = (GLfloat)b; break;
						case 1:verticesData[l].binorm.y = (GLfloat)b; break;
						case 2:verticesData[l].binorm.z = (GLfloat)b; break;
						}break;
						case 3:switch (j)
						{
						case 0:verticesData[l].tgt.x = (GLfloat)b; break;
						case 1:verticesData[l].tgt.y = (GLfloat)b; break;
						case 2:verticesData[l].tgt.z = (GLfloat)b; break;
						}break;
						case 4:switch (j)
						{
						case 0:verticesData[l].uv.x = (GLfloat)b; break;
						case 1:verticesData[l].uv.y = (GLfloat)b; break;
						}break;
						}
						i++;
						if (line[i] == ';')
						{
							j++;
						}

					}

					op++;
				}

			}
		}

		vertex = 0;
		std::getline(model, line);
		for (std::string::size_type i = 0; i<line.size(); i++)
		{
			if (line[i] == ' ')
			{
				int k = 0;
				i++;

				int op = i;
				while (line[i] <= '9'&&line[i] >= '0')
				{
					i++;
				}
				for (std::string::size_type j = i - 1; j >= op; j--)
				{
					vertex += pow(10, k)*(line[j] - '0');
					k++;
				}
			}
		}
		this->indicesNumber = vertex;
		this->indices = new GLushort[vertex];
		int pol = 0;
		std::getline(model, line);
		do
		{
			for (std::string::size_type i = 0; i<line.size(); i++)
			{
				if (line[i] >= '0'&&line[i] <= '9')
				{
					int k = i;
					while (line[i] >= '0'&&line[i] <= '9')
					{
						i++;
					}
					if (line[i] != '.')
					{
						int b = 0;
						int po = 0;
						for (std::string::size_type l = i - 1; l >= k; l--)
						{
							b += pow(10, po)*(line[l] - '0');
							po++;
						}

						indices[pol++] = b;

					}
				}
			}
		} while (getline(model, line));

	}

	this->Load();
}

Model::Model()
{

}
Model::~Model()
{
	delete[] verticesData;
	delete[] indices;
	glDeleteBuffers(1, &this->indicesBufferID);
	glDeleteBuffers(1, &this->vertexesBufferID);
	glDeleteBuffers(1, &this->wiredIndicesBufferID);
	std::cout << "Destructor model";
}

void Model::setIndices(GLushort* p)
{
	this->indices = p;
}
void Model::setVertices(Vertex* p)
{
	this->verticesData = p;
}
void Model::setIndicesNumber(int x)
{
	this->indicesNumber = x;
}
void Model::setVerticesNumber(int x)
{
	this->vertexNumber = x;
}
Model* Model::Load()
{ 
	//Generarea id-urilor bufferelor
	glGenBuffers(1, &(this->indicesBufferID));
	glGenBuffers(1, &(this->vertexesBufferID));
	glGenBuffers(1, &(this->wiredIndicesBufferID));


	//Buffer-ul pentru Vertexi
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexesBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertexNumber, this->verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//Buffer-ul pentru Indici
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indicesBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*this->indicesNumber, this->indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	//Buffer-ul pentru Wired
	// o prelucrare in plus pentru a face rost de modul wired

	return this;
}

GLuint Model::getIndicesBufferID()
{
	return this->indicesBufferID;
}

GLuint Model::getVertexesBufferID()
{
	return this->vertexesBufferID;
}

int Model::getVerticesNumber()
{
	return this->vertexNumber;
}

int Model::getIndicesNumber()
{
	return this->indicesNumber;
}

Vertex* Model::getVertices()
{
	return this->verticesData;
}

GLushort* Model::getIndices()
{
	return this->indices;
}
 

void Model::addX(float add)
{
	for (int i = 0; i < vertexNumber; i++)
	{
		verticesData[i].pos.x += add;
	}
}
void Model::addY(float add)
{
	for (int i = 0; i < vertexNumber; i++)
	{
		verticesData[i].pos.y += add;
	}
}
void Model::addZ(float add)
{
	for (int i = 0; i < vertexNumber; i++)
	{
		verticesData[i].pos.z += add;
	}
}

void Model::updateUVx(float add)
{
	for (int i = 0; i < vertexNumber; i++)
	{
		verticesData[i].uv.x += add;
	}
    this->Load();
}
void Model::updateUVy(float add)
{
	for (int i = 0; i < vertexNumber; i++)
	{
		verticesData[i].uv.y += add;
	}
	this->Load();
}