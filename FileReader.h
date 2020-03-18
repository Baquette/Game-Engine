#pragma once
#include "Vertex.h"
#include "../Utilities/utilities.h"

class FileReader
{ 

public:
    static void readNFG(char* filePath, Vertex *vertexes, int *vertexNumber, GLushort *indices, int *indicesNumber);

	FileReader();
	~FileReader();
};

