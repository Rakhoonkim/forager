#include "stdafx.h"
#include "cropsManager.h"

cropsManager::cropsManager()
{
}

cropsManager::~cropsManager()
{
}

HRESULT cropsManager::init()
{
	imageSetting();
	createImageCrops(OBJECT::CINDERBLOOM, 25, 19);
	return S_OK;
}

void cropsManager::release()
{
}

void cropsManager::update()
{
	for (_viCrops = _vCrops.begin(); _viCrops != _vCrops.end(); ++_viCrops)
	{
		(*_viCrops)->update();
	}

	if (KEYMANAGER->isStayKeyDown('M'))
	{
		POINT rnd;
		rnd = MAPMANAGER->randomObjectTile();

		cout << rnd.x << rnd.y << endl;
	}
	removeCrops();			// 자동 제거 
}

void cropsManager::render()
{
	for (_viCrops = _vCrops.begin(); _viCrops != _vCrops.end(); ++_viCrops)
	{
		(*_viCrops)->render();
	}
}

void cropsManager::imageSetting()
{
	// 1장짜리 
	IMAGEMANAGER->addImage("cinderBloom", "./image/object/cinderBloomObject.bmp", 54, 54, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("nightShade", "./image/object/nightShadeObject.bmp", 48, 48, true, RGB(255, 0, 255));

	// 0 1 2 이미지 
	IMAGEMANAGER->addFrameImage("beet", "./image/object/beetObject.bmp", 90, 36, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hotPepper", "./image/object/hotPepperObject.bmp", 135, 42, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("wheat", "./image/object/wheatObject.bmp", 135, 51, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cotton", "./image/obeject/cottonObject.bmp", 124, 51, 3, 1, true, RGB(255, 0, 255));

	// 01 -> 234 인 이미지 
	IMAGEMANAGER->addFrameImage("bush", "./image/object/beetObject.bmp", 210, 42, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("flower", "./image/object/flowerObject.bmp", 135, 39, 5, 1, true, RGB(255, 0, 255));

	// 0 , 1 , 2, 3 따로 사용하는 이미지 
	IMAGEMANAGER->addFrameImage("volcano", "./image/object/volcanoObject.bmp", 288, 51, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rock", "./image/object/rockObject.bmp", 384, 51, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cactus", "./image/object/cactusObject.bmp", 276, 96, 4, 1, true, RGB(255, 0, 255));

}

//enum class OBJECT
//{
//	ROCK, COAL, IRON, GOLD, VOLCANIC_COAL, VOLCANIC_IRON, VOLCANIC_GOLD,  		// 잔디형식 
//	COTTON, BEET, WHEAT, BUSH, FLOWER_1, FLOWER_2, FLOWER_3,
//	HOT_PEPPER, PUMPKIN, LAVENDER, CINDERBLOOM, NIGHTSHADE,
//	NONE,
//};
void cropsManager::createImageCrops(OBJECT object, int idx, int idy)
{
	if (object == OBJECT::CINDERBLOOM)
	{
		crops* crops;
		crops = new imageCrops;
		crops->init(object, "cinderBloom", idx, idy);
		crops->setHp(1, 1);
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::NIGHTSHADE)
	{
		crops* crops;
		crops = new imageCrops;
		crops->init(object, "nightShade", idx, idy);
		crops->setHp(1, 1);
		_vCrops.push_back(crops);
	}
	else
	{
		return;
	}
}

void cropsManager::createFrameCrops(OBJECT object, int idx, int idy)
{

}

void cropsManager::removeCrops()
{
	for (_viCrops = _vCrops.begin(); _viCrops != _vCrops.end();)
	{
		//리무브 
		if ((*_viCrops)->getCrops()->hp <= 0)
		{
			_vCrops.erase(_viCrops);
			//커서 초기화 
			CURSORMANAGER->setCursor();
			CURSORMANAGER->getCursor()->setCursorChange();
			break;
		}
		else ++_viCrops;
	}
}
