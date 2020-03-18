// NewTrainingFramework.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <math.h>
#include <iostream>
#include "Vertex.h"
#include <conio.h>
#include "Globals.h"
#include "SceneManager.h"
#include "../Utilities/utilities.h"// if you use STL, please include this line AFTER all other include
float time;

int Init ( ESContext *esContext )
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	ResourceManager::getInstance();
 
	SceneManager::getInstance();
 
	return 0;
}

void Draw ( ESContext *esContext )
{
	 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SceneManager::getInstance()->Draw();
	 
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update ( ESContext *esContext, float deltaTime )
{
	if (time > 0.05)
	{
		SceneManager::getInstance()->Update();
		time -= 0.05;
	}
	else
	{
		time += deltaTime;
	}
	
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{
		case 'A':SceneManager::getInstance()->getActiveCamera()->moveOx(1.0f); break;
		case 'S':SceneManager::getInstance()->getActiveCamera()->moveOy(1.0f); break;
		case 'W':SceneManager::getInstance()->getActiveCamera()->moveOy(-1.0f); break;
		case 'D':SceneManager::getInstance()->getActiveCamera()->moveOx(-1.0f); break;
		case 'K':SceneManager::getInstance()->getActiveCamera()->moveOz(1.0f); break;
		case 'I':SceneManager::getInstance()->getActiveCamera()->moveOz(-1.0f); break;
		case 'J':SceneManager::getInstance()->getActiveCamera()->rotateOz(-1.0f); break;
		case 'L':SceneManager::getInstance()->getActiveCamera()->rotateOz(1.0f); break;
		case VK_UP:SceneManager::getInstance()->getActiveCamera()->rotateOx(0.1f); break;
		case VK_DOWN:SceneManager::getInstance()->getActiveCamera()->rotateOx(-0.1f); break;
		case VK_RIGHT:SceneManager::getInstance()->getActiveCamera()->rotateOy(0.1f); break;
		case VK_LEFT:SceneManager::getInstance()->getActiveCamera()->rotateOy(-0.1f); break;
		}
		std::cout << key;
	}
}

void CleanUp()
{
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;
	
	 
	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();


	printf("Press any key...\n");
	_getch();

	
	return 0;
}

