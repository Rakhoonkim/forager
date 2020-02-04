#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
	_worldImage = new image;
	_worldImage->init(3600, 2160);		// 사이즈 아직 미정 

	_worldDC = _worldImage->getMemDC();
	
	_cameraSizeX = 3600;
	_cameraSizeY = 2160;
}

cameraManager::~cameraManager()
{

}

HRESULT cameraManager::init()
{

	return S_OK;
}

void cameraManager::release()
{

}

void cameraManager::update()
{

}

void cameraManager::render()
{

}

void cameraManager::setWorldSize(string strKey)
{
	_cameraSizeX = IMAGEMANAGER->findImage(strKey)->getFrameWidth();
	_cameraSizeY = IMAGEMANAGER->findImage(strKey)->getFrameHeight();
}

void cameraManager::setCameraSizeXY(float x, float y)
{
	_cameraSizeX = x;
	_cameraSizeY = y;
}

void cameraManager::setCameraXY(int x, int y)
{
	_cameraX = x - _cameraSizeX / 2;
	_cameraY = y - _cameraSizeY / 2;
}

void cameraManager::setCameraXY(float x, float y)
{
	_cameraX = x - _cameraSizeX / 2;
	_cameraY = y - _cameraSizeY / 2;
}

void cameraManager::setCameraMapToolXY(int x, int y)
{
	_cameraX = x;
	_cameraY = y;
}

