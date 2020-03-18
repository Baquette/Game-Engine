#include "stdafx.h"
#include "SkyBox.h"
#include "SceneManager.h"


 
void SkyBox::Update()
{
	if (folCam)
	{
		SceneManager::getInstance()->getCamera(camera)->getPosition();
		Vector3 fin = Vector3(SceneManager::getInstance()->getCamera(camera)->getPosition().x, 0, SceneManager::getInstance()->getCamera(camera)->getPosition().z);
		this->setPosition(fin);
	}
}
SkyBox::SkyBox()
{

}

void SkyBox::Draw()
{
	this->sendCommonData();
	glDrawElements(GL_TRIANGLES, model->getIndicesNumber(), GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
SkyBox::~SkyBox()
{
}
