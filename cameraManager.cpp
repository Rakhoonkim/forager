#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
	_cameraMove = false;

	//�ΰ��� ī�޶� 
	_worldCamera.cameraWorldSizeX = 3600;
	_worldCamera.cameraWorldSizeY = 2160;

	_worldCamera.cameraSizeX = WINSIZEX;
	_worldCamera.cameraSizeY = WINSIZEY;

	_worldCamera.cameraX = 0;
	_worldCamera.cameraY = 0;

	_worldCamera.cameraCenterX = 0;
	_worldCamera.cameraCenterY = 0;

	_worldCamera.image = new image;
	_worldCamera.image = IMAGEMANAGER->addImage("WorldDC", _worldCamera.cameraWorldSizeX, _worldCamera.cameraWorldSizeY);		// ������ ���� ���� 

	_worldCamera.hdc = _worldCamera.image->getMemDC();

	_worldCamera.cameraSpeed = 10;

	_worldCamera.cameraAngle = 0;

	_worldRect = RectMake(_worldCamera.cameraX, _worldCamera.cameraY, WINSIZEX, WINSIZEY);

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
	move();
}

void cameraManager::render()
{

}

void cameraManager::move()
{
	if (!_cameraMove) return;

	if (_worldCamera.cameraX < _worldCamera.cameraCenterX - _worldCamera.cameraSizeX / 2) // ������ 
	{
		_worldCamera.cameraX += cosf(_worldCamera.cameraAngle) * _worldCamera.cameraSpeed * TIMEMANAGER->getElapsedTime() * 10;
	}
	else if (_worldCamera.cameraX > _worldCamera.cameraCenterX - _worldCamera.cameraSizeX / 2)
	{
		_worldCamera.cameraX -= cosf(_worldCamera.cameraAngle) * _worldCamera.cameraSpeed * TIMEMANAGER->getElapsedTime() * 10;
	}
	else
	{
		_worldCamera.cameraX = _worldCamera.cameraCenterX - _worldCamera.cameraSizeX / 2;
	}


	if (_worldCamera.cameraY < _worldCamera.cameraCenterY - _worldCamera.cameraSizeY / 2) // ������ 
	{
		_worldCamera.cameraY += -sinf(_worldCamera.cameraAngle) * _worldCamera.cameraSpeed * TIMEMANAGER->getElapsedTime() * 10;
	}
	else if (_worldCamera.cameraY > _worldCamera.cameraCenterY - _worldCamera.cameraSizeY / 2)
	{
		_worldCamera.cameraY -= -sinf(_worldCamera.cameraAngle) * _worldCamera.cameraSpeed * TIMEMANAGER->getElapsedTime() * 10;
	}
	else
	{
		_worldCamera.cameraY = _worldCamera.cameraCenterY - _worldCamera.cameraSizeY / 2;
	}
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
	_worldCamera.cameraAngle = getAngle(_worldCamera.cameraX, _worldCamera.cameraY, x - (WINSIZEX / 2), y- (WINSIZEY / 2));

	if (getDistance(_worldCamera.cameraX  , _worldCamera.cameraY , x - (WINSIZEX / 2), y - (WINSIZEY / 2)) > 20)
	{
		_worldCamera.cameraX += cosf(_worldCamera.cameraAngle) * _worldCamera.cameraSpeed * TIMEMANAGER->getElapsedTime() * 35;
		_worldCamera.cameraY += -sinf(_worldCamera.cameraAngle) * _worldCamera.cameraSpeed * TIMEMANAGER->getElapsedTime() * 35;
	}
	
	//_worldCamera.cameraX = x - _worldCamera.cameraSizeX / 2;
	//_worldCamera.cameraY = y - _worldCamera.cameraSizeY / 2;

	//����ó�� �߰� ���� 
	ColiisionWorldCamera();
}

void cameraManager::setCameraInit(float x, float y)
{
	_worldCamera.cameraX = x - _worldCamera.cameraSizeX / 2;
	_worldCamera.cameraY = y - _worldCamera.cameraSizeY / 2;
	_worldCamera.cameraCenterX = x;
	_worldCamera.cameraCenterY = y;
	//�ݸ��� 
}

void cameraManager::ColiisionWorldCamera()
{
	if (_worldCamera.cameraX <= 0) _worldCamera.cameraX = 0;
	if (_worldCamera.cameraY <= 0) _worldCamera.cameraY = 0;
	if (_worldCamera.cameraX + WINSIZEX >= _worldCamera.cameraWorldSizeX) _worldCamera.cameraX = _worldCamera.cameraX + WINSIZEX;
	if (_worldCamera.cameraY + WINSIZEY >= _worldCamera.cameraWorldSizeY) _worldCamera.cameraY = _worldCamera.cameraY + WINSIZEY;
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

void cameraManager::MapToolCameraRectUpdate()
{
	//Ŭ���� Ʋ�� ����� �ʰ� �����ϱ� ���� RECT
	_worldRect = RectMake(_mapToolCamera.cameraX, _mapToolCamera.cameraY, 900, WINSIZEY);
}

