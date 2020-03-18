#pragma once
#include "SceneObject.h"
class TerrainObject :public SceneObject
{
private:
	Vector3 origin;
	static TerrainObject* instanta;
	int verticalCells;
	int horizontalCells;
	Vector3 color,high;
	float cellScale;
	float offsetY;
public:

	TerrainObject();
	void generateModel();
	~TerrainObject();
	float getcellScale();
	void setColor(Vector3 color);
	void setOffSetY(int);
	void setcellScale(float);
	void setVerticalCellsNumber(int);
	void setHorizontalCellsNumber(int);
	void setHigh(Vector3);
	void sendTerrainData();
	void Draw();
	void updateOrigin();
	static TerrainObject* getTeren();
    Vector3 getOrigin();
	void setOrigin(Vector3);
	float getY();
	void Update();
	void updateX(float x);
	void updateZ(float z);
};

