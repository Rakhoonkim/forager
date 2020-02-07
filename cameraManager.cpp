#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
	//인게임 카메라 
	_worldCamera.cameraWorldSizeX = 3600;
	_worldCamera.cameraWorldSizeY = 2160;

	_worldCamera.cameraSizeX = WINSIZEX;
	_worldCamera.cameraSizeY = WINSIZEY;

	_worldCamera.cameraX = 0;
	_worldCamera.cameraY = 0;

	_worldCamera.image = new image;
	_worldCamera.image = IMAGEMANAGER->addImage("WorldDC", _worldCamera.cameraWorldSizeX, _worldCamera.cameraWorldSizeY);		// 사이즈 아직 미정 

	_worldCamera.hdc = _worldCamera.image->getMemDC();

	// 맵툴 카메라 
	_mapToolCamera.cameraWorldSizeX = 2700;
	_mapToolCamera.cameraWorldSizeY = 2160;

	_mapToolCamera.cameraSizeX = 900;
	_mapToolCamera.cameraSizeY = 720;

	_mapToolCamera.cameraX = 0;
	_mapToolCamera.cameraY = 0;

	_mapToolCamera.image = new image;
	_mapToolCamera.image = IMAGEMANAGER->addImage("mapToolDC", _mapToolCamera.cameraWorldSizeX, _mapToolCamera.cameraWorldSizeY);

	_mapToolCamera.hdc = _mapToolCamera.image->getMemDC();
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

void cameraManager::setCameraSizeXY(float x, float y)
{

}


void cameraManager::setCameraXY(int x, int y)
{

}
//카메라 고정 
void cameraManager::setCameraXY(float x, float y)
{
	_worldCamera.cameraX = x - _worldCamera.cameraSizeX / 2;
	_worldCamera.cameraY = y - _worldCamera.cameraSizeY / 2;

	//예외처리 추가 예정 
	//
}

void cameraManager::setCameraMapToolXY(int x, int y)
{

}


// 3x3 으로 지정할 예정 
void cameraManager::setMapToolCameraXY(float x, float y)
{
	_mapToolCamera.cameraX = x;
	_mapToolCamera.cameraY = y;
}

