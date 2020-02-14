#include "stdafx.h"
#include "building.h"

building::building()
{
}

building::~building()
{
}

HRESULT building::init(BUILDING building, const char* imageName, int idx, int idy, bool Farming)
{
	_building.object = OBJECT::NONE;
	_building.tree = TREE::NONE;

	_building.imageName = imageName;
	_building.building = building;
	_building.idx = idx;
	_building.idy = idy;
	if (Farming)
	{
		_building.x = idx * 60 + 30;
		_building.y = idy * 60 + 30;
	}
	else
	{
		_building.x = idx * 60 + 60;
		_building.y = idy * 60 + 60;
	}
	_building.frameX = 0;
	_building.frameY = 0;

	// 건물마다 센터가 달라야 함
	_building.centerX = idx * 60 + 60;		// 4개 중 가운데 
	_building.centerY = idy * 60 + 60;		// 4개 중 


	//건물마다 달리해줘야 하는 값
	_building.hp = 0;
	_building.maxHp = 0;

	_building.isClick = false;
	_isUse = false;

	//가방지갑

	_backPack = 1;  // 1- 스몰   2 - 미디엄
	_wallet = 3;    // 3- 스몰 , 4 - 슬라임

	if (building == BUILDING::SEWING_STATION || building == BUILDING::FORGE || building == BUILDING::FISHTRAP)
	{
		_building.rc = RectMakeCenter(_building.x, _building.y, IMAGEMANAGER->findImage(imageName)->getWidth(), IMAGEMANAGER->findImage(imageName)->getHeight());
	}
	else if (building == BUILDING::FURNACE || building == BUILDING::BRIDGE)
	{
		_building.rc = RectMakeCenter(_building.x, _building.y - 15, IMAGEMANAGER->findImage(imageName)->getFrameWidth(), IMAGEMANAGER->findImage(imageName)->getFrameHeight());
	}
	/*
	tagButton _furnaceButton[MAXFURNACELIST];
	tagButton _forgeButton[MAXFORGELIST];
	tagButton _sewingButton[MAXSEWINGLIST];*/

	for (int i = 0; i < MAXFURNACELIST; i++)
	{
		_furnaceButton[i].alpha = 0;
		_furnaceButton[i].isClick = false;
		_furnaceButton[i].isEffect = false;
	}
	for (int i = 0; i < MAXFORGELIST; i++)
	{
		_forgeButton[i].alpha = 0;
		_forgeButton[i].isClick = false;
		_forgeButton[i].isEffect = false;
	}
	for (int i = 0; i < MAXSEWINGLIST; i++)
	{
		_sewingButton[i].alpha = 0;
		_sewingButton[i].isClick = false;
		_sewingButton[i].isEffect = false;
	}

	//버튼 초기화 

	return S_OK;
}

void building::release()
{
}

void building::update()
{
}

void building::render()
{
}

void building::EffectRender()
{
}

void building::buttonEffect()
{
}

void building::buttonClick()
{
}

void building::setHp(int maxHp, int hp)
{
	_building.maxHp = maxHp;
	_building.hp = hp;
}

//■■■■■■■■■■■■■■■■■■■■■■ furnace ■■■■■■■■■■■■■■■■■■■■■■

furnace::furnace()
{

}

furnace::~furnace()
{
}

void furnace::update()
{
	if (_building.isClick)
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			if (!_isUse) _isUse = true;
			else _isUse = false;
		}
	}
	if (_isUse)
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_isUse = false;
		}
		buttonClick();
		buttonEffect();
	}
	for (int i = 0; i < MAXFURNACELIST; i++)
	{
		_furnaceButton[i].rc = RectMake(CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 - IMAGEMANAGER->findImage("furnaceBackground")->getWidth() / 2 + 15, CAMERAMANAGER->getWorldCamera().cameraY + 140 + i * (IMAGEMANAGER->findImage("furnaceList")->getFrameHeight() + 3), IMAGEMANAGER->findImage("furnaceList")->getFrameWidth(), IMAGEMANAGER->findImage("furnaceList")->getFrameHeight());
	}
}

void furnace::render()
{
	IMAGEMANAGER->findImage(_building.imageName)->frameRender(CAMERAMANAGER->getWorldDC(), _building.x - (IMAGEMANAGER->findImage(_building.imageName)->getFrameWidth() / 2), _building.y - (IMAGEMANAGER->findImage(_building.imageName)->getFrameHeight() / 2) - 15);
	if (_building.isClick) IMAGEMANAGER->findImage("Ebutton")->render(CAMERAMANAGER->getWorldDC(), _building.centerX - (IMAGEMANAGER->findImage("Ebutton")->getWidth() / 2), _building.centerY - (IMAGEMANAGER->findImage("Ebutton")->getHeight() / 2));
	//Rectangle(CAMERAMANAGER->getWorldDC(), _building.rc);
}

void furnace::EffectRender()
{
	if (_isUse)
	{
		IMAGEMANAGER->findImage("furnaceBackground")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 - IMAGEMANAGER->findImage("furnaceBackground")->getWidth() / 2, CAMERAMANAGER->getWorldCamera().cameraY + 75);

		for (int i = 0; i < MAXFURNACELIST; i++)
		{
			if (!_furnaceButton[i].isEffect)
			{
				IMAGEMANAGER->findImage("furnaceList")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _furnaceButton[i].rc.left, _furnaceButton[i].rc.top, 0, i,120);
			}
			else
			{
				IMAGEMANAGER->findImage("furnaceList")->frameRender(CAMERAMANAGER->getWorldDC(), _furnaceButton[i].rc.left, _furnaceButton[i].rc.top, 0, i);
			}
			//Rectangle(CAMERAMANAGER->getWorldDC(), _furnaceButton[i].rc);
		}
	}
}

void furnace::buttonEffect()
{
	for (int i = 0; i < MAXFURNACELIST; i++)
	{
		//if (_furnaceButton[i].isEffect) continue;

		if (PtInRect(&_furnaceButton[i].rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			_furnaceButton[i].isEffect = true;
			break;
		}
	}

	for (int i = 0; i < MAXFURNACELIST; i++)
	{
		if (!_furnaceButton[i].isEffect) continue;

		if (!PtInRect(&_furnaceButton[i].rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			_furnaceButton[i].isEffect = false;
		}

	}
}

void furnace::buttonClick()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < MAXFURNACELIST; i++)
		{
			if (PtInRect(&_furnaceButton[i].rc, _ptMouse)) _furnaceButton[i].isClick = true;
			break;
		}
	}
}

//■■■■■■■■■■■■■■■■■■■■■■ forge ■■■■■■■■■■■■■■■■■■■■■■
void forge::update()
{
	if (_building.isClick)
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			if (!_isUse) _isUse = true;
			else _isUse = false;
		}
	}
	if (_isUse)
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_isUse = false;
		}
		buttonEffect();
	}
	for (int i = 0; i < MAXFORGELIST; i++)
	{
		_forgeButton[i].rc = RectMake(CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 - IMAGEMANAGER->findImage("forgeBackground")->getWidth() / 2 + 15, CAMERAMANAGER->getWorldCamera().cameraY + 140 + i * (IMAGEMANAGER->findImage("forgeList")->getFrameHeight() + 3), IMAGEMANAGER->findImage("forgeList")->getFrameWidth(), IMAGEMANAGER->findImage("forgeList")->getFrameHeight());
	}
}

void forge::render()
{
	IMAGEMANAGER->findImage(_building.imageName)->render(CAMERAMANAGER->getWorldDC(), _building.x - (IMAGEMANAGER->findImage(_building.imageName)->getWidth() / 2), _building.y - (IMAGEMANAGER->findImage(_building.imageName)->getHeight() / 2));
	if (_building.isClick) IMAGEMANAGER->findImage("Ebutton")->render(CAMERAMANAGER->getWorldDC(), _building.centerX - (IMAGEMANAGER->findImage("Ebutton")->getWidth() / 2), _building.centerY - (IMAGEMANAGER->findImage("Ebutton")->getHeight() / 2));
}

void forge::EffectRender()
{
	if (_isUse)
	{
		IMAGEMANAGER->findImage("forgeBackground")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 - IMAGEMANAGER->findImage("forgeBackground")->getWidth() / 2, CAMERAMANAGER->getWorldCamera().cameraY + 75);

		for (int i = 0; i < MAXFORGELIST; i++)
		{
			if (!_forgeButton[i].isEffect)
			{
				IMAGEMANAGER->findImage("forgeList")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _forgeButton[i].rc.left, _forgeButton[i].rc.top, 0, i,120);
			}
			else
			{
				IMAGEMANAGER->findImage("forgeList")->frameRender(CAMERAMANAGER->getWorldDC(), _forgeButton[i].rc.left, _forgeButton[i].rc.top, 0, i);
			}
		}
	}
}

void forge::buttonEffect()
{
	for (int i = 0; i < MAXFORGELIST; i++)
	{
		if (PtInRect(&_forgeButton[i].rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			_forgeButton[i].isEffect = true;
			break;
		}
	}

	for (int i = 0; i < MAXFORGELIST; i++)
	{
		if (!_forgeButton[i].isEffect) continue;

		if (!PtInRect(&_forgeButton[i].rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			_forgeButton[i].isEffect = false;
		}
	}
}

void forge::buttonClick()
{
}

//■■■■■■■■■■■■■■■■■■■■■■ sewingStation ■■■■■■■■■■■■■■■■■■■■■■
void sewingStation::update()
{
	if (_building.isClick)
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_isUse = true;
		}
	}
	if (_isUse)
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_isUse = false;
		}
		buttonEffect();
		buttonClick();
	}
	for (int i = 0; i < MAXSEWINGLIST; i++)
	{
		_sewingButton[i].rc = RectMake(CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 - IMAGEMANAGER->findImage("forgeBackground")->getWidth() / 2 + 15, CAMERAMANAGER->getWorldCamera().cameraY + 315 + i * (IMAGEMANAGER->findImage("forgeList")->getFrameHeight() + 3), IMAGEMANAGER->findImage("forgeList")->getFrameWidth(), IMAGEMANAGER->findImage("forgeList")->getFrameHeight());
	}
}

void sewingStation::render()
{
	IMAGEMANAGER->findImage(_building.imageName)->render(CAMERAMANAGER->getWorldDC(), _building.x - (IMAGEMANAGER->findImage(_building.imageName)->getWidth() / 2), _building.y - (IMAGEMANAGER->findImage(_building.imageName)->getHeight() / 2) - 30);
	if (_building.isClick) IMAGEMANAGER->findImage("Ebutton")->render(CAMERAMANAGER->getWorldDC(), _building.centerX - (IMAGEMANAGER->findImage("Ebutton")->getWidth() / 2), _building.centerY - (IMAGEMANAGER->findImage("Ebutton")->getHeight() / 2));
}

void sewingStation::EffectRender()
{
	if (_isUse)
	{
		IMAGEMANAGER->findImage("sewingBackground")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 - IMAGEMANAGER->findImage("sewingBackground")->getWidth() / 2, CAMERAMANAGER->getWorldCamera().cameraY + 250);

		//케릭터의 장비에 따른 고정 렌더링 
		if (!_sewingButton[0].isEffect)
		{
			IMAGEMANAGER->findImage("sewingList")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _sewingButton[0].rc.left, _sewingButton[0].rc.top, 0, 0, 120);
		}
		else
		{
			IMAGEMANAGER->findImage("sewingList")->frameRender(CAMERAMANAGER->getWorldDC(), _sewingButton[0].rc.left, _sewingButton[0].rc.top, 0, 0);
		}

		if (!_sewingButton[1].isEffect)
		{
			IMAGEMANAGER->findImage("sewingList")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _sewingButton[1].rc.left, _sewingButton[1].rc.top, 0, _backPack,120);
		}
		else
		{
			IMAGEMANAGER->findImage("sewingList")->frameRender(CAMERAMANAGER->getWorldDC(), _sewingButton[1].rc.left, _sewingButton[1].rc.top, 0, _backPack);
		}

		if (!_sewingButton[2].isEffect)
		{
			IMAGEMANAGER->findImage("sewingList")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _sewingButton[2].rc.left, _sewingButton[2].rc.top, 0, _wallet, 120);
		}
		else
		{
			IMAGEMANAGER->findImage("sewingList")->frameRender(CAMERAMANAGER->getWorldDC(), _sewingButton[2].rc.left, _sewingButton[2].rc.top, 0, _wallet);
		}	
	}
}

void sewingStation::buttonEffect()
{
	for (int i = 0; i < MAXFORGELIST; i++)
	{
		if (PtInRect(&_sewingButton[i].rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			_sewingButton[i].isEffect = true;
			break;
		}
	}

	for (int i = 0; i < MAXFORGELIST; i++)
	{
		if (!_sewingButton[i].isEffect) continue;

		if (!PtInRect(&_sewingButton[i].rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			_sewingButton[i].isEffect = false;
		}
	}
}

void sewingStation::buttonClick()
{
}

//■■■■■■■■■■■■■■■■■■■■■■ fishTrap ■■■■■■■■■■■■■■■■■■■■■■

void fishTrap::update()
{
}

void fishTrap::render()
{
	IMAGEMANAGER->findImage(_building.imageName)->render(CAMERAMANAGER->getWorldDC(), _building.x - (IMAGEMANAGER->findImage(_building.imageName)->getWidth() / 2), _building.y - (IMAGEMANAGER->findImage(_building.imageName)->getHeight() / 2));
	if (_building.isClick) IMAGEMANAGER->findImage("EbuttonFarming")->render(CAMERAMANAGER->getWorldDC(), _building.x - (IMAGEMANAGER->findImage("EbuttonFarming")->getWidth() / 2), _building.y - (IMAGEMANAGER->findImage("EbuttonFarming")->getHeight() / 2) - 10);
}

void fishTrap::EffectRender()
{
}

//■■■■■■■■■■■■■■■■■■■■■■ bridge ■■■■■■■■■■■■■■■■■■■■■■

void bridge::update()
{
}

void bridge::render()
{
	IMAGEMANAGER->findImage(_building.imageName)->frameRender(CAMERAMANAGER->getWorldDC(), _building.x - (IMAGEMANAGER->findImage(_building.imageName)->getFrameWidth() / 2), _building.y - (IMAGEMANAGER->findImage(_building.imageName)->getFrameHeight() / 2) - 10);
	if (_building.isClick) IMAGEMANAGER->findImage("EbuttonFarming")->render(CAMERAMANAGER->getWorldDC(), _building.x - (IMAGEMANAGER->findImage("EbuttonFarming")->getWidth() / 2), _building.y - (IMAGEMANAGER->findImage("EbuttonFarming")->getHeight() / 2) - 10);
}

void bridge::EffectRender()
{
}
