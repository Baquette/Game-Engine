#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}

Camera::Camera(Vector3 position)
{
	this->position = position;
}
Camera::Camera(Vector3 position,Vector3 target,GLfloat tetha, GLfloat moveSpeed,GLfloat fov,GLfloat fata,GLfloat spate)
{
	this->target = target;
	this->position = position;
	this->deltaTime = 0.3f;
	this->moveSpeed = moveSpeed;
	this->direction = Vector3(0.0f, 1.0f, 0.0f);
	this->rotateSpeed = tetha;
	this->fov = fov;
	this->fata = fata;
	this->spate = spate;
	this->ratio = Globals::screenWidth / Globals::screenHeight;
	this->perspective.SetPerspective(this->fov, this->ratio, this->fata, this->spate);
	this->viewMatrix.SetIdentity();
	this->worldMatrix.SetIdentity();
	this->setAxis();
	this->updateWorldView();

}
Camera::~Camera()
{
}

void Camera::updatePerspective()
{
	this->perspective.SetPerspective(this->fov, this->ratio, this->fata, this->spate);
}
Matrix Camera::getPerspective()
{
	return this->perspective;
}
Vector3 Camera::getDirection()
{
	return this->direction;
}

Vector3 Camera::getPosition()
{
	return this->position;
}

GLfloat Camera::getMoveSpeed()
{
	return this->moveSpeed;
}

GLfloat Camera::getRotateSpeed()
{
	return this->rotateSpeed;
}

GLfloat Camera::getNear()
{
	return this->fata;
}
Vector4 Vec3To4(Vector3 x)
{
	return Vector4(x.x, x.y, x.z, 1.0f);
}
Vector3 Vec4To3(Vector4 x)
{
	return Vector3(x.x, x.y, x.z);
}
GLfloat Camera::getFar()
{
	return this->spate;
}

GLfloat Camera::getFOV()
{
	return this->fov;
}

GLfloat Camera::getDeltaTime()
{
	return this->deltaTime;
}

Matrix Camera::getViewMatrix()
{
	return this->viewMatrix;
}

Matrix Camera::getWorldMatrix()
{
	return this->worldMatrix;
}

void Camera::setPosition(Vector3 position)
{
	this->position = position;
}

void Camera::setTarget(Vector3 target)
{
	this->target = target;
}

void Camera::setDirection(Vector3 direction)
{
	this->direction = direction;
}

void Camera::setMoveSpeed(GLfloat moveSpeed)
{
	this->moveSpeed = moveSpeed;
}

void Camera::setRotateSpeed(GLfloat rotateSpeed)
{
	this->rotateSpeed = rotateSpeed;
}

void Camera::setNear(GLfloat fata)
{
	this->fata = fata;
}

void Camera::setFar(GLfloat spate)
{
	this->spate = spate;
}

void Camera::setFOV(GLfloat fov)
{
	this->fov = fov;
}

void Camera::setDeltaTime(GLfloat deltaTime)
{
	this->deltaTime = deltaTime;
}

void Camera::setAxis()
{
	
	this->zAxis = -(this->target - this->position).Normalize();
	this->yAxis = this->direction.Normalize();
	this->xAxis = zAxis.Cross(yAxis).Normalize();
}

void Camera::setViewMatrix()
{
}

void Camera::setWorldMatrix()
{
}

void Camera::moveOz(GLfloat direction)
{
	Vector3 forward = -(target - position).Normalize()*direction;
	Vector3 deplasare = forward*moveSpeed*deltaTime;
	position += deplasare;
	target += deplasare;
	this->updateWorldView();

}
void Camera::moveOx(GLfloat direction)
{
	Vector3 forward = yAxis.Cross(zAxis).Normalize()*direction;
	position += forward*moveSpeed*deltaTime;
	target += forward*moveSpeed*deltaTime;
	this->updateWorldView();
}

void Camera::moveOy(GLfloat direction)
{
	position += yAxis*moveSpeed*deltaTime*direction;
	target += yAxis*moveSpeed*deltaTime*direction;
	this->updateWorldView();
}
void Camera::rotateOx(GLfloat tetha)
{
	Vector4 localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 rotatedUp = localUp*universal.SetRotationX(tetha);
	direction = Vec4To3((rotatedUp*worldMatrix)).Normalize();
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(this->target - this->position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget*universal.SetRotationX(tetha);
	target = Vec4To3(rotatedTarget*this->worldMatrix);
	this->updateWorldView();
}

void Camera::rotateOz(GLfloat tetha)
{
	Vector4 localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(this->target - this->position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget*universal.SetRotationZ(tetha);
	target = Vec4To3(rotatedTarget*this->worldMatrix);
	this->updateWorldView();
}

void Camera::rotateOy(GLfloat tetha)
{
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(this->target - this->position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget*universal.SetRotationY(tetha);
	target = Vec4To3(rotatedTarget*this->worldMatrix);
	this->updateWorldView();
}
void Camera::updateWorldView()
{
	Matrix R;

	this->setAxis();
	R.m[0][0] = xAxis.x; R.m[0][1] = xAxis.y; R.m[0][2] = xAxis.z; R.m[0][3] = 0;
	R.m[1][0] = yAxis.x; R.m[1][1] = yAxis.y; R.m[1][2] = yAxis.z; R.m[1][3] = 0;
	R.m[2][0] = zAxis.x; R.m[2][1] = zAxis.y; R.m[2][2] = zAxis.z; R.m[2][3] = 0;
	R.m[3][0] = 0; R.m[3][1] = 0; R.m[3][2] = 0; R.m[3][3] = 1;
	
	
	universal.SetTranslation(-position.x, -position.y, -position.z);
	viewMatrix = universal*R.Transpose();

	universal.SetTranslation(position.x, position.y, position.z);
	worldMatrix = R*universal;


}