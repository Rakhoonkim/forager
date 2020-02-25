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
	_puzzle.centerX = _puzzle.x +(_puzzle.width / 2);
	_puzzle.centerY = _puzzle.y + (_puzzle.height / 2);
	_puzzle.remove = false;
	_puzzle.rc = RectMake(_puzzle.x, _puzzle.y, _puzzle.width, _puzzle.height);

	_puzzle.isClick = false;

	MAPMANAGER->setBuildTilesFarming(idx, idy);  // 오프젝트타일로 
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
	Rectangle(CAMERAMANAGER->getWorldDC(), _puzzle.rc);
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

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
	_puzzle.centerX = _puzzle.x + (_puzzle.width / 2);
	_puzzle.centerY = _puzzle.y + (_puzzle.height / 2);
	_puzzle.remove = false;
	_puzzle.rc = RectMake(_puzzle.x, _puzzle.y, _puzzle.width, _puzzle.height);

	_isOpen = false;
	_puzzle.isClick = false;
	MAPMANAGER->setBuildTilesFarming(idx, idy);  // 오프젝트타일로 
	return S_OK;
}

void framePuzzle::update()
{
	if (_puzzle.isClick && !_isOpen)
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			if (UIMANAGER->getInven()->itemCount("keyDrop") > 0)
			{
				UIMANAGER->getInven()->removeInven("keyDrop", 1);
				ITEMMANAGER->DropEnemyItem(ENEMY::BOAR, _puzzle.centerX, _puzzle.centerY);
				ITEMMANAGER->DropForgeItem(FORGERECIPE::COIN, _puzzle.centerX, _puzzle.centerY,3);
				ITEMMANAGER->DropForgeItem(FORGERECIPE::BOTTLE, _puzzle.centerX, _puzzle.centerY,1);
				KEYANIMANAGER->findAnimation(_puzzle.imageName)->start();
				MAPMANAGER->setRemoveObject(_puzzle.idx, _puzzle.idy);  // 오프젝트타일 해제  
				_isOpen = true;

			}
		}

	}
	if (KEYANIMANAGER->findAnimation(_puzzle.imageName)->getFrameMaxFrame()-1 == KEYANIMANAGER->findAnimation(_puzzle.imageName)->getNowPlayNum())
	{
		_puzzle.remove = true;
	}

	cout << _puzzle.isClick << endl;
}

void framePuzzle::render()
{
	IMAGEMANAGER->findImage(_puzzle.imageName)->aniRender(CAMERAMANAGER->getWorldDC(), _puzzle.rc.left, _puzzle.rc.top,KEYANIMANAGER->findAnimation(_puzzle.imageName));

	if (_puzzle.isClick)
	{
		IMAGEMANAGER->findImage("Ebutton")->render(CAMERAMANAGER->getWorldDC(), _puzzle.centerX - (IMAGEMANAGER->findImage("Ebutton")->getWidth() / 2), _puzzle.centerY);
		IMAGEMANAGER->findImage("treasureChestKey")->render(CAMERAMANAGER->getWorldDC(), _puzzle.centerX - (IMAGEMANAGER->findImage("treasureChestKey")->getWidth() / 2), _puzzle.centerY -50);
	}
}


