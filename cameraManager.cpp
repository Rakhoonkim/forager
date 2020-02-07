#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
	//�ΰ��� ī�޶� 
	_worldCamera.cameraWorldSizeX = 3600;
	_worldCamera.cameraWorldSizeY = 2160;

	_worldCamera.cameraSizeX = WINSIZEX;
	_worldCamera.cameraSizeY = WINSIZEY;

	_worldCamera.cameraX = 0;
	_worldCamera.cameraY = 0;

	_worldCamera.image = new image;
	_worldCamera.image = IMAGEMANAGER->addImage("WorldDC", _worldCamera.cameraWorldSizeX, _worldCamera.cameraWorldSizeY);		// ������ ���� ���� 

	_worldCamera.hdc = _worldCamera.image->getMemDC();

	// ���� ī�޶� 
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
//ī�޶� ���� 
void cameraManager::setCameraXY(float x, float y)
{
	_worldCamera.cameraX = x - _worldCamera.cameraSizeX / 2;
	_worldCamera.cameraY = y - _worldCamera.cameraSizeY / 2;

	//����ó�� �߰� ���� 
	//
}

void cameraManager::setCameraMapToolXY(int x, int y)
{

}


// 3x3 ���� ������ ���� 
void cameraManager::setMapToolCameraXY(float x, float y)
{
	_mapToolCamera.cameraX = x;
	_mapToolCamera.cameraY = y;
}

