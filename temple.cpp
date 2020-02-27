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
	_temp.imageName = imageName;
	
	_temp.idx = idx;
	_temp.idy = idy;


	_temp.x = idx * 60;
	_temp.y = idy * 60;

	_temp.frameX = 0; // 초기화 
	_temp.anlge = 0;

	_temp.time = TIMEMANAGER->getWorldTime();

	_temp.rc = RectMake(_temp.x, _temp.y, IMAGEMANAGER->findImage(imageName)->getFrameWidth(), IMAGEMANAGER->findImage(imageName)->getFrameHeight());


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
	IMAGEMANAGER->findImage(_temp.imageName)->render(CAMERAMANAGER->getWorldDC(), _temp.x, _temp.y);
}

// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ lantern ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

HRESULT lantern::init(const char* imageName, int idx, int idy)
{
	_temp.imageName = imageName;
	_temp.ani = KEYANIMANAGER->findAnimation(imageName);

	_temp.idx = idx;
	_temp.idy = idy;

	_temp.x = idx * 60;
	_temp.y = idy * 60 - 42;
	_temp.ani->start();
	_temp.frameX = 0; // 초기화 
	_temp.anlge = 0;

	_temp.time = TIMEMANAGER->getWorldTime();

	_temp.rc = RectMake(_temp.x, _temp.y, IMAGEMANAGER->findImage(imageName)->getFrameWidth(), IMAGEMANAGER->findImage(imageName)->getFrameHeight());

	return S_OK;
}

void lantern::render()
{
	IMAGEMANAGER->findImage(_temp.imageName)->aniRender(CAMERAMANAGER->getWorldDC(), _temp.x, _temp.y, _temp.ani);
}

// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ lantern ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

void cannon::update()
{


	if (_temp.time + 3 < TIMEMANAGER->getWorldTime())
	{
		_temp.time = TIMEMANAGER->getWorldTime();
		if (_temp.frameX == 0)
		{
			_bulletManager->getBullet()->fire(_temp.x, _temp.y, _temp.anlge, 10, 350);
		}
		else if (_temp.frameX == 1)
		{
			_bulletManager->getBullet()->fire(_temp.x + 15, _temp.y + IMAGEMANAGER->findImage(_temp.imageName)->getFrameHeight() / 2, _temp.anlge, 10, 350);
		}
		else if (_temp.frameX == 2)
		{
			_bulletManager->getBullet()->fire(_temp.x, _temp.y + 15, _temp.anlge, 10, 350);
		}
		else if (_temp.frameX == 3)
		{
			_bulletManager->getBullet()->fire(_temp.x + 20, _temp.y + 10, _temp.anlge, 10, 350);
		}
	}

}

void cannon::setFrameX(int frameX)
{
	if (frameX == 0)
	{
		_temp.frameX = frameX;
		_temp.anlge = 1.08;
		_temp.y -= 10;
	}
	else if (frameX == 1)
	{
		_temp.frameX = frameX;
		_temp.anlge = -1.95;
	}
	else if (frameX == 2)
	{
		_temp.frameX = frameX;
		_temp.x -= 12;
		_temp.anlge = 2.69;
	}
	else if (frameX == 3)
	{
		_temp.frameX = frameX;
		_temp.x += 15;
		_temp.anlge = -0.4;
	}

	_temp.rc = RectMake(_temp.x, _temp.y, IMAGEMANAGER->findImage(_temp.imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_temp.imageName)->getFrameHeight());

}

void cannon::render()
{
	IMAGEMANAGER->findImage(_temp.imageName)->frameRender(CAMERAMANAGER->getWorldDC(), _temp.x, _temp.y, _temp.frameX, 0);
}


//■■■■■■■■■■■■■■■■■■■■■ door ■■■■■■■■■■■■■■■■■■■■■


HRESULT door::init(const char* imageName, int idx, int idy)
{
	_temp.imageName = imageName;

	_temp.idx = idx;
	_temp.idy = idy;


	_temp.x = idx * 60;
	_temp.y = idy * 60;

	_temp.frameX = 0; // 초기화 
	_temp.anlge = 0;

	_temp.time = TIMEMANAGER->getWorldTime();

	_temp.rc = RectMake(_temp.x, _temp.y, IMAGEMANAGER->findImage(imageName)->getFrameWidth(), IMAGEMANAGER->findImage(imageName)->getFrameHeight());


	return S_OK;
}

void door::render()
{
	IMAGEMANAGER->findImage(_temp.imageName)->frameRender(CAMERAMANAGER->getWorldDC(), _temp.x, _temp.y, _temp.frameX, 0);
	//Rectangle(CAMERAMANAGER->getWorldDC(), _temp.rc);
}
