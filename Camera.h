#pragma once
#include "Globals.h"
#include "../Utilities/utilities.h"
class Camera
{
private:
	Matrix universal;
	Matrix R;
	Vector3 position;
	Vector3 target;
	Vector3 direction;
	GLfloat moveSpeed;
	GLfloat rotateSpeed;
	GLfloat fata;
	GLfloat spate;
	GLfloat fov;
	GLfloat ratio;
	GLfloat deltaTime;
	Vector3 xAxis, yAxis, zAxis;
	Matrix viewMatrix, worldMatrix;
	Matrix perspective;
public:
	Camera(Vector3 position, Vector3 target,GLfloat tetha, GLfloat moveSpeed, GLfloat fov, GLfloat fata, GLfloat spate);
	Camera(Vector3 position);
	void setPosition(Vector3 position);
	Vector3 getPosition();
	void setTarget(Vector3 target);
	Vector3 getTarget();
	void setDirection(Vector3 direction);
	Vector3 getDirection();
	void setMoveSpeed(GLfloat moveSpeed);
	GLfloat getMoveSpeed();
	void setRotateSpeed(GLfloat rotateSpeed);
	GLfloat getRotateSpeed();
	void setNear(GLfloat fata);
	GLfloat getNear();
	void setFar(GLfloat spate);
	GLfloat getFar();
	void setFOV(GLfloat fov);
	GLfloat getFOV();
	void setDeltaTime(GLfloat deltaTime);
	GLfloat getDeltaTime();
	Matrix getPerspective();
	void updatePerspective();
	void setAxis();
	void setViewMatrix();
	Matrix getViewMatrix();
	void setWorldMatrix();
	Matrix getWorldMatrix();

	void moveOx(GLfloat direction);
	void moveOy(GLfloat direction);
	void moveOz(GLfloat direction);
	void rotateOx(GLfloat tetha);
	void rotateOy(GLfloat tetha);
	void rotateOz(GLfloat tetha);
	void updateWorldView();

	Camera();
	~Camera();
};

