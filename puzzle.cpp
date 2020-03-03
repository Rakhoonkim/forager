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
	_puzzle.temple = TEMPLEOBJECT::NONE;
	_puzzle.puzzle = PUZZLE::NONE;

	_puzzle.imageName = imageName;
	_puzzle.width = IMAGEMANAGER->findImage(imageName)->getWidth();
	_puzzle.height = IMAGEMANAGER->findImage(imageName)->getHeight();

	_puzzle.idx = idx;
	_puzzle.idy = idy;
	_puzzle.x = _puzzle.idx * 60;
	_puzzle.y = _puzzle.idy * 60;
	_puzzle.centerX = _puzzle.x +(_puzzle.width / 2);
	_puzzle.centerY = _puzzle.y + (_puzzle.height / 2);

	_puzzle.alpha = 0;

	_puzzle.rc = RectMakeCenter(_puzzle.x, _puzzle.y, _puzzle.width, _puzzle.height);

	_puzzle.remove = false;
	_puzzle.isClick = false;
	_puzzle.isRender = false;
	
	MAPMANAGER->setBuildTiles(idx, idy);  // 오프젝트타일로 
	
	return S_OK;
}

void puzzle::release()
{
}

void puzzle::update()
{
	_puzzle.x = _puzzle.idx * 60;
	_puzzle.y = _puzzle.idy * 60;
	_puzzle.centerX = _puzzle.x + 30;
	_puzzle.centerY = _puzzle.y +30;
	_puzzle.rc = RectMakeCenter(_puzzle.x, _puzzle.y, _puzzle.width, _puzzle.height);
}

void puzzle::render()
{
	if (_puzzle.alpha > 0)
	{
		IMAGEMANAGER->findImage(_puzzle.imageName)->alphaRender(CAMERAMANAGER->getWorldDC(), _puzzle.rc.left, _puzzle.rc.top,_puzzle.alpha);
	}
	else
	{
		IMAGEMANAGER->findImage(_puzzle.imageName)->render(CAMERAMANAGER->getWorldDC(), _puzzle.rc.left, _puzzle.rc.top);
	}
	//Rectangle(CAMERAMANAGER->getWorldDC(), _puzzle.rc);
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
	_puzzle.temple = TEMPLEOBJECT::NONE;
	_puzzle.puzzle = PUZZLE::NONE;
	_puzzle.imageName = imageName;

	_puzzle.width = IMAGEMANAGER->findImage(imageName)->getFrameWidth();
	_puzzle.height = IMAGEMANAGER->findImage(imageName)->getFrameHeight();

	_puzzle.idx = idx;
	_puzzle.idy = idy;
	_puzzle.x = _puzzle.idx * 60;
	_puzzle.y = (_puzzle.idy - 1) * 60;
	_puzzle.alpha = 0;

	_puzzle.centerX = _puzzle.x + (_puzzle.width / 2);
	_puzzle.centerY = _puzzle.y + (_puzzle.height / 2);

	_puzzle.rc = RectMake(_puzzle.x, _puzzle.y, _puzzle.width, _puzzle.height);

	_puzzle.remove = false;
	_puzzle.isRender = false;
	_puzzle.isClick = false;
	
	_isOpen = false;
	
	MAPMANAGER->setBuildTiles(idx, idy);  // 오프젝트타일로 
	
	return S_OK;
}

void framePuzzle::update()
{
	//만약에 열지 않았으면 
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

	_puzzle.x = _puzzle.idx * 60;
	_puzzle.y = (_puzzle.idy - 1) * 60;
	_puzzle.centerX = _puzzle.x + (_puzzle.width / 2);
	_puzzle.centerY = _puzzle.y + (_puzzle.height / 2);
	_puzzle.rc = RectMake(_puzzle.x, _puzzle.y, _puzzle.width, _puzzle.height);
}

void framePuzzle::render()
{
	IMAGEMANAGER->findImage(_puzzle.imageName)->aniRender(CAMERAMANAGER->getWorldDC(), _puzzle.rc.left, _puzzle.rc.top,KEYANIMANAGER->findAnimation(_puzzle.imageName));

	if (_puzzle.isClick && !_isOpen)
	{
		IMAGEMANAGER->findImage("Ebutton")->render(CAMERAMANAGER->getWorldDC(), _puzzle.centerX - (IMAGEMANAGER->findImage("Ebutton")->getWidth() / 2), _puzzle.centerY);
		IMAGEMANAGER->findImage("treasureChestKey")->render(CAMERAMANAGER->getWorldDC(), _puzzle.centerX - (IMAGEMANAGER->findImage("treasureChestKey")->getWidth() / 2), _puzzle.centerY -50);
	}
}

templeEntrance::templeEntrance()
{
}

templeEntrance::~templeEntrance()
{
}

void templeEntrance::update()
{
	_puzzle.x = _puzzle.idx * 60;
	_puzzle.y = _puzzle.idy * 60;
	_puzzle.centerX = _puzzle.x + 30;
	_puzzle.centerY = _puzzle.y + 30;
	_puzzle.rc = RectMakeCenter(_puzzle.x, _puzzle.y, _puzzle.width, _puzzle.height);

	//던전으로 입장하기
	if (_puzzle.isClick)
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			GAMEDATA->setZorder(ZORDER->getZorder());
			ZORDER->release();
			SCENEMANAGER->changeScene("BOSS");
		}
	}
}

void templeEntrance::render()
{
	if (_puzzle.alpha > 0)
	{
		IMAGEMANAGER->findImage(_puzzle.imageName)->alphaRender(CAMERAMANAGER->getWorldDC(), _puzzle.rc.left, _puzzle.rc.top,_puzzle.alpha);
	}
	else
	{
		IMAGEMANAGER->findImage(_puzzle.imageName)->render(CAMERAMANAGER->getWorldDC(), _puzzle.rc.left, _puzzle.rc.top);
	}
	if(_puzzle.isClick) IMAGEMANAGER->findImage("Ebutton")->render(CAMERAMANAGER->getWorldDC(), _puzzle.x- (IMAGEMANAGER->findImage("Ebutton")->getWidth() / 2), _puzzle.y);
	//Rectangle(CAMERAMANAGER->getWorldDC(), 	_puzzle.rc);
}
