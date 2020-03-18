#include "stdafx.h"
#include "rapidxml.hpp"
#include "FileReader.h"
#include <iostream>
 
 
#include <fstream>
#include <string> 
#include <sstream>

using namespace std;
using namespace rapidxml;
void FileReader::readNFG(char* filePath,Vertex* vertexes,int *vertexNumber,GLushort* indices,int *indicesNumber)
{
	int vertex = 0;
	std::ifstream model(filePath);
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
		*vertexNumber = vertex;
		vertexes= new Vertex[vertex];
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
						case 0:vertexes[l].pos.x = (GLfloat)b; break;
						case 1:vertexes[l].pos.y = (GLfloat)b; break;
						case 2:vertexes[l].pos.z = (GLfloat)b; break;
						}break;
						case 1:switch (j)
						{
						case 0:vertexes[l].norm.x = (GLfloat)b; break;
						case 1:vertexes[l].norm.y = (GLfloat)b; break;
						case 2:vertexes[l].norm.z = (GLfloat)b; break;
						}break;
						case 2:switch (j)
						{
						case 0:vertexes[l].binorm.x = (GLfloat)b; break;
						case 1:vertexes[l].binorm.y = (GLfloat)b; break;
						case 2:vertexes[l].binorm.z = (GLfloat)b; break;
						}break;
						case 3:switch (j)
						{
						case 0:vertexes[l].tgt.x = (GLfloat)b; break;
						case 1:vertexes[l].tgt.y = (GLfloat)b; break;
						case 2:vertexes[l].tgt.z = (GLfloat)b; break;
						}break;
						case 4:switch (j)
						{
						case 0:vertexes[l].uv.x = (GLfloat)b; break;
						case 1:vertexes[l].uv.y = (GLfloat)b; break;
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
		*indicesNumber = vertex;
		indices = new GLushort[vertex];
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
	 
}



FileReader::FileReader()
{

}


FileReader::~FileReader()
{
}
