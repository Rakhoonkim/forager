#include "stdafx.h"
#include "temple.h"

temple::temple()
{
}

temple::~temple()
{
}

HRESULT temple::init(const char* imageName, int idx, int idy)
{
	_temple.imageName = imageName;
	
	_temple.idx = idx;
	_temple.idy = idy;

	_temple.x = idx * 60;
	_temple.y = idy * 60;

	_temple.frameX = 0; // 초기화 
	_temple.anlge = 0;

	_temple.time = TIMEMANAGER->getWorldTime();

	_temple.rc = RectMake(_temple.x, _temple.y, IMAGEMANAGER->findImage(imageName)->getFrameWidth(), IMAGEMANAGER->findImage(imageName)->getFrameHeight());

	return S_OK;
}

void temple::release()
{
}

void temple::update()
{
}

void temple::render()
{
	IMAGEMANAGER->findImage(_temple.imageName)->render(CAMERAMANAGER->getWorldDC(), _temple.x, _temple.y);
}

// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ lantern ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

HRESULT lantern::init(const char* imageName, int idx, int idy)
{
	_temple.imageName = imageName;
	_temple.ani = KEYANIMANAGER->findAnimation(imageName);

	_temple.idx = idx;
	_temple.idy = idy;

	_temple.x = idx * 60;
	_temple.y = idy * 60 - 42;
	_temple.ani->start();
	_temple.frameX = 0; // 초기화 
	_temple.anlge = 0;

	_temple.time = TIMEMANAGER->getWorldTime();

	_temple.rc = RectMake(_temple.x, _temple.y, IMAGEMANAGER->findImage(imageName)->getFrameWidth(), IMAGEMANAGER->findImage(imageName)->getFrameHeight());

	return S_OK;
}

void lantern::render()
{
	IMAGEMANAGER->findImage(_temple.imageName)->aniRender(CAMERAMANAGER->getWorldDC(), _temple.x, _temple.y, _temple.ani);
}

// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ lantern ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

void cannon::update()
{


	if (_temple.time + 3 < TIMEMANAGER->getWorldTime())
	{
		_temple.time = TIMEMANAGER->getWorldTime();
		if (_temple.frameX == 0)
		{
			_bulletManager->getBullet()->fire(_temple.x, _temple.y, _temple.anlge, 10, 350);
		}
		else if (_temple.frameX == 1)
		{
			_bulletManager->getBullet()->fire(_temple.x + 15, _temple.y + IMAGEMANAGER->findImage(_temple.imageName)->getFrameHeight() / 2, _temple.anlge, 10, 350);
		}
		else if (_temple.frameX == 2)
		{
			_bulletManager->getBullet()->fire(_temple.x, _temple.y + 15, _temple.anlge, 10, 350);
		}
		else if (_temple.frameX == 3)
		{
			_bulletManager->getBullet()->fire(_temple.x + 20, _temple.y + 10, _temple.anlge, 10, 350);
		}
	}

}

void cannon::setFrameX(int frameX)
{
	if (frameX == 0)
	{
		_temple.frameX = frameX;
		_temple.anlge = 1.08;
		_temple.y -= 10;
	}
	else if (frameX == 1)
	{
		_temple.frameX = frameX;
		_temple.anlge = -1.95;
	}
	else if (frameX == 2)
	{
		_temple.frameX = frameX;
		_temple.x -= 12;
		_temple.anlge = 2.69;
	}
	else if (frameX == 3)
	{
		_temple.frameX = frameX;
		_temple.x += 15;
		_temple.anlge = -0.4;
	}

	_temple.rc = RectMake(_temple.x, _temple.y, IMAGEMANAGER->findImage(_temple.imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_temple.imageName)->getFrameHeight());
}

void cannon::render()
{
	IMAGEMANAGER->findImage(_temple.imageName)->frameRender(CAMERAMANAGER->getWorldDC(), _temple.x, _temple.y, _temple.frameX, 0);
}


//■■■■■■■■■■■■■■■■■■■■■ door ■■■■■■■■■■■■■■■■■■■■■


HRESULT door::init(const char* imageName, int idx, int idy)
{
	_temple.imageName = imageName;

	_temple.idx = idx;
	_temple.idy = idy;

	_temple.x = idx * 60;
	_temple.y = idy * 60;

	_temple.frameX = 0; // 초기화 
	_temple.anlge = 0;

	_temple.time = TIMEMANAGER->getWorldTime();

	_temple.rc = RectMake(_temple.x, _temple.y, IMAGEMANAGER->findImage(imageName)->getFrameWidth(), IMAGEMANAGER->findImage(imageName)->getFrameHeight());

	return S_OK;
}

void door::render()
{
	IMAGEMANAGER->findImage(_temple.imageName)->frameRender(CAMERAMANAGER->getWorldDC(), _temple.x, _temple.y, _temple.frameX, 0);
	//Rectangle(CAMERAMANAGER->getWorldDC(), _temp.rc);
}
