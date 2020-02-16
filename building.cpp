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

	//크래프트 버튼 
	_craftButton.isClick = false;
	_craftPage = false;
	// 작동중
	_isWork = false;
	_timer = 0;
	//가방지갑
	_direction = 0;

	_backPack = 1;  // 1- 스몰   2 - 미디엄
	_wallet = 3;    // 3- 스몰 , 4 - 슬라임

	_effectCount = 0;	// 이펙트 카운트

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

void building::craftButton()
{
}

void building::isWorking()
{
}

void building::setHp(int maxHp, int hp)
{
	_building.maxHp = maxHp;
	_building.hp = hp;
}

void building::buttonInit()
{
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
	_craftButton.rc = RectMake(CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 160, CAMERAMANAGER->getWorldCamera().cameraY + 300, 180, 45);
	_addButton[0].rc = RectMake(CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 128, CAMERAMANAGER->getWorldCamera().cameraY + 300, 32, 45);
	_addButton[1].rc = RectMake(CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 160 + IMAGEMANAGER->findImage("craft")->getWidth(), CAMERAMANAGER->getWorldCamera().cameraY + 300, 32, 45);

	isWorking();
}

void furnace::render()
{
	if (!_isWork)
	{
		IMAGEMANAGER->findImage(_building.imageName)->frameRender(CAMERAMANAGER->getWorldDC(), _building.x - (IMAGEMANAGER->findImage(_building.imageName)->getFrameWidth() / 2), _building.y - (IMAGEMANAGER->findImage(_building.imageName)->getFrameHeight() / 2) - 15);
	}
	else
	{
		IMAGEMANAGER->findImage(_building.imageName)->aniRender(CAMERAMANAGER->getWorldDC(), _building.x - (IMAGEMANAGER->findImage(_building.imageName)->getFrameWidth() / 2), _building.y - (IMAGEMANAGER->findImage(_building.imageName)->getFrameHeight() / 2) - 15, _building.ani);
	}
	if (_building.isClick) IMAGEMANAGER->findImage("Ebutton")->render(CAMERAMANAGER->getWorldDC(), _building.centerX - (IMAGEMANAGER->findImage("Ebutton")->getWidth() / 2), _building.centerY - (IMAGEMANAGER->findImage("Ebutton")->getHeight() / 2));
	//Rectangle(CAMERAMANAGER->getWorldDC(), _building.rc);
}

void furnace::EffectRender()
{
	if (_isUse)
	{
		IMAGEMANAGER->findImage("furnaceBackground")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 - IMAGEMANAGER->findImage("furnaceBackground")->getWidth() / 2, CAMERAMANAGER->getWorldCamera().cameraY + 75);

		//크래프트 메시지 
		if (_craftPage)
		{
			IMAGEMANAGER->findImage("craftBackground")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + IMAGEMANAGER->findImage("furnaceBackground")->getWidth() / 2, CAMERAMANAGER->getWorldCamera().cameraY + 130);
			//Rectangle(CAMERAMANAGER->getWorldDC(), _craftButton.rc);
			IMAGEMANAGER->findImage("craft")->render(CAMERAMANAGER->getWorldDC(), _craftButton.rc.left, _craftButton.rc.top);
			//Rectangle(CAMERAMANAGER->getWorldDC(), _addButton[0].rc);
			//Rectangle(CAMERAMANAGER->getWorldDC(), _addButton[1].rc);
			IMAGEMANAGER->findImage("arrowButton")->frameRender(CAMERAMANAGER->getWorldDC(), _addButton[0].rc.left, _addButton[0].rc.top, 1, 0);
			IMAGEMANAGER->findImage("arrowButton")->frameRender(CAMERAMANAGER->getWorldDC(), _addButton[1].rc.left, _addButton[1].rc.top, 0, 0);
			IMAGEMANAGER->findImage("piece")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 240, CAMERAMANAGER->getWorldCamera().cameraY + 150);
		}



		for (int i = 0; i < MAXFURNACELIST; i++)
		{
			if (!_furnaceButton[i].isEffect)
			{
				IMAGEMANAGER->findImage("furnaceList")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _furnaceButton[i].rc.left, _furnaceButton[i].rc.top, 0, i, 120);
			}
			else
			{
				IMAGEMANAGER->findImage("furnaceList")->frameRender(CAMERAMANAGER->getWorldDC(), _furnaceButton[i].rc.left, _furnaceButton[i].rc.top, 0, i);
			}
			//Rectangle(CAMERAMANAGER->getWorldDC(), _furnaceButton[i].rc);
			if (_craftPage && _furnaceButton[i].isClick)
			{
				IMAGEMANAGER->findImage("craftItem")->frameRender(CAMERAMANAGER->getWorldDC(), _craftButton.rc.left + 30, CAMERAMANAGER->getWorldCamera().cameraY + 135, i, 0);
				IMAGEMANAGER->findImage("pieceList")->frameRender(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 185, CAMERAMANAGER->getWorldCamera().cameraY + 180, i, 0);
			}
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
			if (!_isWork && PtInRect(&_furnaceButton[i].rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
			{
				_direction = i;
				_itemCount = 1;  // 일단 기본값 
				_craftPage = true;
				break;
			}
		}

		//버튼 클릭 초기화 
		for (int i = 0; i < MAXFURNACELIST; i++)
		{
			_furnaceButton[i].isClick = false;
		}
		_furnaceButton[_direction].isClick = true;


		//크래프트 버튼 클릭
		if (PtInRect(&_craftButton.rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			craftButton();
		}
	}
}

void furnace::buttonInit()
{
	// 버튼 초기화 하는 함수 
	_isWork = true;
	_building.ani->start();
	_craftPage = false;
	_isUse = false;
	_furnaceButton[_direction].isClick = false;
}

void furnace::isWorking()
{
	if (!_isWork) return;

	_effectCount++;
	if (_effectCount > RND->getInt(20))
	{
		EFFECTMANAGER->MovePlay("smoke", _building.x - RND->getInt(15) - 5, _building.y - 80 ,true);
		_effectCount = 0;
	}


	if (_timer + 5 <= TIMEMANAGER->getWorldTime())
	{
		switch (_furnace)
		{
		case FURNACERECIPE::COAL:
			ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::COAL, _building.x, _building.y, _itemCount);
			break;
		case FURNACERECIPE::BRICK:
			ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::BRICK, _building.x, _building.y, _itemCount);
			break;
		case FURNACERECIPE::IRON:
			ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::IRON, _building.x, _building.y, _itemCount);
			break;
		case FURNACERECIPE::GOLD:
			ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::GOLD, _building.x, _building.y, _itemCount);
			break;
		case FURNACERECIPE::STEEL:
			ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::STEEL, _building.x, _building.y, _itemCount);
			break;
		case FURNACERECIPE::GLASS:
			ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::GLASS, _building.x, _building.y, _itemCount);
			break;
		case FURNACERECIPE::BREAD:
			ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::BREAD, _building.x, _building.y, _itemCount);
			break;
		case FURNACERECIPE::FISH:
			ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::FISH, _building.x, _building.y, _itemCount);
			break;
		case FURNACERECIPE::MEAT:
			ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::MEAT, _building.x, _building.y, _itemCount);
			break;
		case FURNACERECIPE::NONE:
			break;
		default:
			break;
		}
		_isWork = false;

	}

	cout << "작동중이다 " << endl;
}

void furnace::craftButton()
{
	if (_furnaceButton[0].isClick)
	{
		if (ITEMMANAGER->getInventory()->foranceRecipes(FURNACERECIPE::COAL, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("woodDrop", 2);
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_furnace = FURNACERECIPE::COAL;
			buttonInit();
		}
	}
	else if (_furnaceButton[1].isClick)
	{
		if (ITEMMANAGER->getInventory()->foranceRecipes(FURNACERECIPE::BRICK, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("stoneDrop", 2);
			ITEMMANAGER->getInventory()->removeInven("coalDrop", 1);
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_furnace = FURNACERECIPE::BRICK;
			buttonInit();
		}
	}
	else if (_furnaceButton[2].isClick)
	{
		if (ITEMMANAGER->getInventory()->foranceRecipes(FURNACERECIPE::IRON, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("coalDrop", 1);
			ITEMMANAGER->getInventory()->removeInven("ironOreDrop", 2);
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_furnace = FURNACERECIPE::IRON;
			buttonInit();
		}
	}
	else if (_furnaceButton[3].isClick)
	{
		if (ITEMMANAGER->getInventory()->foranceRecipes(FURNACERECIPE::GOLD, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("coalDrop", 1);
			ITEMMANAGER->getInventory()->removeInven("goldOreDrop", 2);
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_furnace = FURNACERECIPE::GOLD;
			buttonInit();
		}
	}
	else if (_furnaceButton[4].isClick)
	{
		if (ITEMMANAGER->getInventory()->foranceRecipes(FURNACERECIPE::STEEL, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("coalDrop", 2);
			ITEMMANAGER->getInventory()->removeInven("goldOreDrop", 2);
			ITEMMANAGER->getInventory()->removeInven("ironOreDrop", 2);
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_furnace = FURNACERECIPE::STEEL;
			buttonInit();
		}
	}
	else if (_furnaceButton[5].isClick)
	{
		if (ITEMMANAGER->getInventory()->foranceRecipes(FURNACERECIPE::GLASS, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("coalDrop", 2);
			//모래 추가 예정
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_furnace = FURNACERECIPE::GLASS;
			buttonInit();
		}
	}
	else if (_furnaceButton[6].isClick)  //============================================== 추가 예정
	{
		if (ITEMMANAGER->getInventory()->foranceRecipes(FURNACERECIPE::BREAD, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("coalDrop", 1);
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_furnace = FURNACERECIPE::BREAD;
			buttonInit();
		}
	}
	else if (_furnaceButton[7].isClick)
	{
		if (ITEMMANAGER->getInventory()->foranceRecipes(FURNACERECIPE::FISH, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("coalDrop", 1);
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_furnace = FURNACERECIPE::FISH;
			buttonInit();
		}
	}
	else if (_furnaceButton[8].isClick)
	{
		if (ITEMMANAGER->getInventory()->foranceRecipes(FURNACERECIPE::MEAT, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("coalDrop", 1);
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_furnace = FURNACERECIPE::MEAT;
			buttonInit();
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
		buttonClick();
		buttonEffect();
	}
	for (int i = 0; i < MAXFORGELIST; i++)
	{
		_forgeButton[i].rc = RectMake(CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 - IMAGEMANAGER->findImage("forgeBackground")->getWidth() / 2 + 15, CAMERAMANAGER->getWorldCamera().cameraY + 140 + i * (IMAGEMANAGER->findImage("forgeList")->getFrameHeight() + 3), IMAGEMANAGER->findImage("forgeList")->getFrameWidth(), IMAGEMANAGER->findImage("forgeList")->getFrameHeight());
	}
	_craftButton.rc = RectMake(CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 160, CAMERAMANAGER->getWorldCamera().cameraY + 300, 180, 45);
	_addButton[0].rc = RectMake(CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 128, CAMERAMANAGER->getWorldCamera().cameraY + 300, 32, 45);
	_addButton[1].rc = RectMake(CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 160 + IMAGEMANAGER->findImage("craft")->getWidth(), CAMERAMANAGER->getWorldCamera().cameraY + 300, 32, 45);
	isWorking();
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

		if (_craftPage)
		{
			IMAGEMANAGER->findImage("craftBackground")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + IMAGEMANAGER->findImage("furnaceBackground")->getWidth() / 2, CAMERAMANAGER->getWorldCamera().cameraY + 130);
			////Rectangle(CAMERAMANAGER->getWorldDC(), _craftButton.rc);
			IMAGEMANAGER->findImage("craft")->render(CAMERAMANAGER->getWorldDC(), _craftButton.rc.left, _craftButton.rc.top);
			////Rectangle(CAMERAMANAGER->getWorldDC(), _addButton[0].rc);
			////Rectangle(CAMERAMANAGER->getWorldDC(), _addButton[1].rc);
			IMAGEMANAGER->findImage("arrowButton")->frameRender(CAMERAMANAGER->getWorldDC(), _addButton[0].rc.left, _addButton[0].rc.top, 1, 0);
			IMAGEMANAGER->findImage("arrowButton")->frameRender(CAMERAMANAGER->getWorldDC(), _addButton[1].rc.left, _addButton[1].rc.top, 0, 0);
			IMAGEMANAGER->findImage("piece")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 240, CAMERAMANAGER->getWorldCamera().cameraY + 150);
		}

		for (int i = 0; i < MAXFORGELIST; i++)
		{
			if (!_forgeButton[i].isEffect)
			{
				IMAGEMANAGER->findImage("forgeList")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _forgeButton[i].rc.left, _forgeButton[i].rc.top, 0, i, 120);
			}
			else
			{
				IMAGEMANAGER->findImage("forgeList")->frameRender(CAMERAMANAGER->getWorldDC(), _forgeButton[i].rc.left, _forgeButton[i].rc.top, 0, i);
			}
			//Rectangle(CAMERAMANAGER->getWorldDC(), _forgeButton[i].rc);
			if (_craftPage && _forgeButton[i].isClick)
			{
				IMAGEMANAGER->findImage("craftItem")->frameRender(CAMERAMANAGER->getWorldDC(), _craftButton.rc.left + 30, CAMERAMANAGER->getWorldCamera().cameraY + 135, i, 1);
				IMAGEMANAGER->findImage("pieceList")->frameRender(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 185, CAMERAMANAGER->getWorldCamera().cameraY + 180, i, 1);
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
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < MAXFORGELIST; i++)
		{
			if (!_isWork && PtInRect(&_forgeButton[i].rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
			{
				_direction = i;
				_itemCount = 1;  // 일단 기본값 
				_craftPage = true;
				break;
			}
		}

		//버튼 클릭 초기화 
		for (int i = 0; i < MAXFORGELIST; i++)
		{
			_forgeButton[i].isClick = false;
		}
		_forgeButton[_direction].isClick = true;


		//크래프트 버튼 클릭
		if (PtInRect(&_craftButton.rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			craftButton();
		}
	}
}

void forge::buttonInit()
{
	_isWork = true;
	_craftPage = false;
	_isUse = false;
	_forgeButton[_direction].isClick = false;
}

void forge::isWorking()
{
	if (!_isWork) return;

	if (_timer + 5 <= TIMEMANAGER->getWorldTime())
	{
		switch (_forge)
		{
		case FORGERECIPE::COIN:
			ITEMMANAGER->DropForgeItem(FORGERECIPE::COIN, _building.x, _building.y, _itemCount);
			break;
		case FORGERECIPE::SHOVEL:
			ITEMMANAGER->DropForgeItem(FORGERECIPE::SHOVEL, _building.x, _building.y, _itemCount);
			break;
		case FORGERECIPE::SWORD:
			ITEMMANAGER->DropForgeItem(FORGERECIPE::SWORD, _building.x, _building.y, _itemCount);
			break;
		case FORGERECIPE::PICKAXE:
			ITEMMANAGER->DropForgeItem(FORGERECIPE::PICKAXE, _building.x, _building.y, _itemCount);
			break;
		case FORGERECIPE::BOTTLE:
			ITEMMANAGER->DropForgeItem(FORGERECIPE::BOTTLE, _building.x, _building.y, _itemCount);
			break;
		case FORGERECIPE::NONE:
			break;
		default:
			break;
		}
		_isWork = false;

	}
}

void forge::craftButton()
{
	if (_forgeButton[0].isClick)
	{
		if (ITEMMANAGER->getInventory()->forgeRecipes(FORGERECIPE::COIN, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("goldingotDrop", 1);
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_forge = FORGERECIPE::COIN;
			buttonInit();
		}
	}
	if (_forgeButton[1].isClick)
	{
		if (ITEMMANAGER->getInventory()->forgeRecipes(FORGERECIPE::SHOVEL, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("ironingotDrop", 20);
			ITEMMANAGER->getInventory()->removeInven("woodDrop", 20);
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_forge = FORGERECIPE::SHOVEL;
			buttonInit();
		}
	}
	if (_forgeButton[2].isClick)
	{
		if (ITEMMANAGER->getInventory()->forgeRecipes(FORGERECIPE::SWORD, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("ironingotDrop", 20);
			//ITEMMANAGER->getInventory()->removeInven("goldingotDrop", 1);  // 젤리 삭제 예정 
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_forge = FORGERECIPE::SWORD;
			buttonInit();
		}
	}
	if (_forgeButton[3].isClick)
	{
		if (ITEMMANAGER->getInventory()->forgeRecipes(FORGERECIPE::PICKAXE, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("ironingotDrop", 15);
			//ITEMMANAGER->getInventory()->removeInven("goldingotDrop", 1);  // 젤리 삭제 예정
			ITEMMANAGER->getInventory()->removeInven("coalDrop", 2);  // 젤리 삭제 예정 
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_forge = FORGERECIPE::PICKAXE;
			buttonInit();
		}
	}
	if (_forgeButton[4].isClick)
	{
		if (ITEMMANAGER->getInventory()->forgeRecipes(FORGERECIPE::BOTTLE, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("threadDrop", 1);
			ITEMMANAGER->getInventory()->removeInven("grassDrop", 2);
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_forge = FORGERECIPE::BOTTLE;
			buttonInit();
		}
	}
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
	_craftButton.rc = RectMake(CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 160, CAMERAMANAGER->getWorldCamera().cameraY + 460, 180, 45);
	_addButton[0].rc = RectMake(CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 128, CAMERAMANAGER->getWorldCamera().cameraY + 460, 32, 45);
	_addButton[1].rc = RectMake(CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 160 + IMAGEMANAGER->findImage("craft")->getWidth(), CAMERAMANAGER->getWorldCamera().cameraY + 460, 32, 45);
	isWorking();
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

		if (_craftPage)
		{
			IMAGEMANAGER->findImage("craftBackground")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + IMAGEMANAGER->findImage("furnaceBackground")->getWidth() / 2, CAMERAMANAGER->getWorldCamera().cameraY + 290);
			////Rectangle(CAMERAMANAGER->getWorldDC(), _craftButton.rc);
			IMAGEMANAGER->findImage("craft")->render(CAMERAMANAGER->getWorldDC(), _craftButton.rc.left, _craftButton.rc.top);
			////Rectangle(CAMERAMANAGER->getWorldDC(), _addButton[0].rc);
			////Rectangle(CAMERAMANAGER->getWorldDC(), _addButton[1].rc);
			IMAGEMANAGER->findImage("arrowButton")->frameRender(CAMERAMANAGER->getWorldDC(), _addButton[0].rc.left, _addButton[0].rc.top, 1, 0);
			IMAGEMANAGER->findImage("arrowButton")->frameRender(CAMERAMANAGER->getWorldDC(), _addButton[1].rc.left, _addButton[1].rc.top, 0, 0);
			IMAGEMANAGER->findImage("piece")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 240, CAMERAMANAGER->getWorldCamera().cameraY + 310);  // 160 더하기 
		}

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
			IMAGEMANAGER->findImage("sewingList")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _sewingButton[1].rc.left, _sewingButton[1].rc.top, 0, _backPack, 120);
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


		if (_craftPage && _sewingButton[0].isClick)
		{
			IMAGEMANAGER->findImage("craftItem")->frameRender(CAMERAMANAGER->getWorldDC(), _craftButton.rc.left + 30, CAMERAMANAGER->getWorldCamera().cameraY + 295, 0, 2);
			IMAGEMANAGER->findImage("pieceList")->frameRender(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 185, CAMERAMANAGER->getWorldCamera().cameraY + 340, 0, 2);
		}
		else if (_craftPage && _sewingButton[1].isClick)
		{
			IMAGEMANAGER->findImage("craftItem")->frameRender(CAMERAMANAGER->getWorldDC(), _craftButton.rc.left + 30, CAMERAMANAGER->getWorldCamera().cameraY + 295, _backPack, 2);
			IMAGEMANAGER->findImage("pieceList")->frameRender(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 185, CAMERAMANAGER->getWorldCamera().cameraY + 340, _backPack, 2);
		}
		else if (_craftPage && _sewingButton[2].isClick)
		{
			IMAGEMANAGER->findImage("craftItem")->frameRender(CAMERAMANAGER->getWorldDC(), _craftButton.rc.left + 30, CAMERAMANAGER->getWorldCamera().cameraY + 295, _wallet, 2);
			IMAGEMANAGER->findImage("pieceList")->frameRender(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 185, CAMERAMANAGER->getWorldCamera().cameraY + 340, _wallet, 2);
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
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < MAXSEWINGLIST; i++)
		{
			if (!_isWork && PtInRect(&_sewingButton[i].rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
			{
				_direction = i;
				_itemCount = 1;  // 일단 기본값 
				_craftPage = true;
				break;
			}
		}

		//버튼 클릭 초기화 
		for (int i = 0; i < MAXSEWINGLIST; i++)
		{
			_sewingButton[i].isClick = false;
		}
		_sewingButton[_direction].isClick = true;


		//크래프트 버튼 클릭
		if (PtInRect(&_craftButton.rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			craftButton();
		}
	}
}

void sewingStation::buttonInit()
{
	_isWork = true;
	_craftPage = false;
	_isUse = false;
	_sewingButton[_direction].isClick = false;
}

void sewingStation::isWorking()  // 수정 
{
	if (!_isWork) return;

	if (_timer + 5 <= TIMEMANAGER->getWorldTime())
	{
		switch (_sewing)
		{
		case SEWINGRECIPE::THREAD:
			ITEMMANAGER->DropsewingItem(SEWINGRECIPE::THREAD, _building.x, _building.y, _itemCount);
			break;
		case SEWINGRECIPE::SMALL_BACKPACK:
			ITEMMANAGER->DropsewingItem(SEWINGRECIPE::SLIME_WALLET, _building.x, _building.y, _itemCount);
			break;
		case SEWINGRECIPE::MEDIUM_BACKPACK:
			ITEMMANAGER->DropsewingItem(SEWINGRECIPE::MEDIUM_BACKPACK, _building.x, _building.y, _itemCount);
			break;
		case SEWINGRECIPE::SMALL_WALLET:
			ITEMMANAGER->DropsewingItem(SEWINGRECIPE::SMALL_WALLET, _building.x, _building.y, _itemCount);
			break;
		case SEWINGRECIPE::SLIME_WALLET:
			ITEMMANAGER->DropsewingItem(SEWINGRECIPE::SLIME_WALLET, _building.x, _building.y, _itemCount);
			break;
		case SEWINGRECIPE::NONE:
			break;
		default:
			break;
		}

		_isWork = false;

	}
}

void sewingStation::craftButton() // 수정 
{
	if (_sewingButton[0].isClick)
	{
		if (ITEMMANAGER->getInventory()->sewingRecipes(SEWINGRECIPE::THREAD, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("fiberDrop", 2);
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_sewing = SEWINGRECIPE::THREAD;
			buttonInit();
		}
	}
	else if (_sewingButton[1].isClick && _backPack == 1)
	{
		if (ITEMMANAGER->getInventory()->sewingRecipes(SEWINGRECIPE::SMALL_BACKPACK, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("threadDrop", 10);
			ITEMMANAGER->getInventory()->removeInven("ironOreDrop", 10);
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_sewing = SEWINGRECIPE::SMALL_BACKPACK;
			buttonInit();
			_backPack++;
		}
	}
	else if (_sewingButton[2].isClick && _backPack == 2)
	{
		if (ITEMMANAGER->getInventory()->sewingRecipes(SEWINGRECIPE::MEDIUM_BACKPACK, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("threadDrop", 20);
			ITEMMANAGER->getInventory()->removeInven("ironingotDrop", 15);
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_sewing = SEWINGRECIPE::MEDIUM_BACKPACK;
			buttonInit();
		}
	}
	else if (_sewingButton[1].isClick && _wallet == 3)
	{
		if (ITEMMANAGER->getInventory()->sewingRecipes(SEWINGRECIPE::SMALL_WALLET, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("threadDrop", 10);
			ITEMMANAGER->getInventory()->removeInven("goldOreDrop", 10);
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_sewing = SEWINGRECIPE::SMALL_WALLET;
			buttonInit();
			_wallet++;
		}
	}
	else if (_sewingButton[2].isClick && _wallet == 4)
	{
		if (ITEMMANAGER->getInventory()->sewingRecipes(SEWINGRECIPE::SLIME_WALLET, _itemCount))
		{
			ITEMMANAGER->getInventory()->removeInven("threadDrop", 20);
			ITEMMANAGER->getInventory()->removeInven("goldingotDrop", 10);
			_timer = TIMEMANAGER->getWorldTime(); //현재시간등록 
			_sewing = SEWINGRECIPE::SLIME_WALLET;
			buttonInit();
		}
	}
}

//■■■■■■■■■■■■■■■■■■■■■■ fishTrap ■■■■■■■■■■■■■■■■■■■■■■
// 입력하는것 수정할 것 
void fishTrap::update()
{
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (!_isWork && !_isUse)
		{
			_isWork = true;
			_timer = TIMEMANAGER->getWorldTime();
		}

	}
	isWorking();
}

void fishTrap::render()
{
	IMAGEMANAGER->findImage(_building.imageName)->render(CAMERAMANAGER->getWorldDC(), _building.x - (IMAGEMANAGER->findImage(_building.imageName)->getWidth() / 2), _building.y - (IMAGEMANAGER->findImage(_building.imageName)->getHeight() / 2));
	if ((_building.isClick)) IMAGEMANAGER->findImage("EbuttonFarming")->render(CAMERAMANAGER->getWorldDC(), _building.x - (IMAGEMANAGER->findImage("EbuttonFarming")->getWidth() / 2), _building.y - (IMAGEMANAGER->findImage("EbuttonFarming")->getHeight() / 2) - 10);
}

void fishTrap::EffectRender()
{
}

void fishTrap::isWorking()
{
	if (!_isWork) return;

	if (_timer + 15 < TIMEMANAGER->getWorldTime())
	{
		ITEMMANAGER->DropFishTrapItem(_building.x, _building.y);
		_isWork = false;
	}


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
