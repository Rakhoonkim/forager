#include "stdafx.h"
#include "puzzle.h"

puzzle::puzzle()
{
}

puzzle::~puzzle()
{
}

HRESULT puzzle::init(const char* imageName, int idx, int idy)
{
	_puzzle.imageName = imageName;
	_puzzle.width = IMAGEMANAGER->findImage(imageName)->getWidth();
	_puzzle.height = IMAGEMANAGER->findImage(imageName)->getHeight();
	_puzzle.idx = idx;
	_puzzle.idy = idy;
	_puzzle.x = _puzzle.idx * 60;
	_puzzle.y = _puzzle.idy * 60;
	_puzzle.centerX = _puzzle.x -(_puzzle.width / 2);
	_puzzle.centerY = _puzzle.y - (_puzzle.height / 2);
	_puzzle.remove = false;
	_puzzle.rc = RectMake(_puzzle.x, _puzzle.y, _puzzle.width, _puzzle.height);


	return S_OK;
}

void puzzle::release()
{
}

void puzzle::update()
{
	_puzzle.rc = RectMake(_puzzle.x, _puzzle.y, _puzzle.width, _puzzle.height);
}

void puzzle::render()
{
	IMAGEMANAGER->findImage(_puzzle.imageName)->render(CAMERAMANAGER->getWorldDC(), _puzzle.rc.left, _puzzle.rc.top);
	//Rectangle(CAMERAMANAGER->getWorldDC(), _puzzle.rc);
}

//¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á

framePuzzle::framePuzzle()
{
}

framePuzzle::~framePuzzle()
{
}

HRESULT framePuzzle::init(const char* imageName, int idx, int idy)
{
	_puzzle.imageName = imageName;
	_puzzle.width = IMAGEMANAGER->findImage(imageName)->getFrameWidth();
	_puzzle.height = IMAGEMANAGER->findImage(imageName)->getFrameHeight();
	_puzzle.idx = idx;
	_puzzle.idy = idy;
	_puzzle.x = _puzzle.idx * 60;
	_puzzle.y = _puzzle.idy * 60;
	_puzzle.centerX = _puzzle.x - (_puzzle.width / 2);
	_puzzle.centerY = _puzzle.y - (_puzzle.height / 2);
	_puzzle.remove = false;
	_puzzle.rc = RectMake(_puzzle.x, _puzzle.y, _puzzle.width, _puzzle.height);

	return S_OK;
}

void framePuzzle::update()
{
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		KEYANIMANAGER->findAnimation(_puzzle.imageName)->start();
	
	}
	if (KEYANIMANAGER->findAnimation(_puzzle.imageName)->getFrameMaxFrame()-1 == KEYANIMANAGER->findAnimation(_puzzle.imageName)->getNowPlayNum())
	{
		_puzzle.remove = true;
	}
}

void framePuzzle::render()
{
	IMAGEMANAGER->findImage(_puzzle.imageName)->aniRender(CAMERAMANAGER->getWorldDC(), _puzzle.rc.left, _puzzle.rc.top,KEYANIMANAGER->findAnimation(_puzzle.imageName));
}

