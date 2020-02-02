#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
	_worldImage = new image;
	_worldImage->init(3800, 1900);		// 사이즈 아직 미정 
	_worldDC = _worldImage->getMemDC();
	
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
