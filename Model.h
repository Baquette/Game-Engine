#pragma once


#include "Vertex.h"
#include "../Utilities/utilities.h"

struct ModelResource {
	int id;
	char *filePath;
};


class Model
{
private:
	GLuint indicesBufferID;
	GLuint wiredIndicesBufferID;
	GLuint vertexesBufferID;
	int indicesNumber;
	int wiredIndicesNumber;
	int vertexNumber;
	Vertex *verticesData;
	GLushort *indices;
	
public:
	ModelResource* source;
	Model();
	Model(ModelResource*);
	~Model();
	Model* Load();

	Vertex* getVertices();
	GLushort* getIndices();
	int getVerticesNumber();
	int getIndicesNumber();
	GLuint getIndicesBufferID();
	GLuint getVertexesBufferID();
	void setIndices(GLushort*);
	void setVertices(Vertex*);
	void setVerticesNumber(int);
	void setIndicesNumber(int);
	void addX(float add);
	void addY(float add);
	void addZ(float add);
	void updateUVx(float add);
	void updateUVy(float add);
};

