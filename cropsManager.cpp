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
	createImageCrops(OBJECT::CINDERBLOOM, 17, 16);
	createImageCrops(OBJECT::NIGHTSHADE, 18, 16);
	createFrameCrops(OBJECT::BEET, 19, 16);
	createFrameCrops(OBJECT::HOT_PEPPER, 20, 16);
	createFrameCrops(OBJECT::COTTON, 21, 16);
	createFrameCrops(OBJECT::WHEAT, 22, 16);
	createFrameCrops(OBJECT::PUMPKIN, 23, 16);

	createimageFrameCrops(OBJECT::ROCK, 24, 16);
	createimageFrameCrops(OBJECT::COAL, 25, 16);
	createimageFrameCrops(OBJECT::GOLD, 26, 16);
	createimageFrameCrops(OBJECT::IRON, 27, 16);
	createimageFrameCrops(OBJECT::VOLCANIC_COAL, 17, 17);
	createimageFrameCrops(OBJECT::VOLCANIC_GOLD, 18, 17);
	createimageFrameCrops(OBJECT::VOLCANIC_IRON, 19, 17);

	craateTreeCrops(TREE::BASIC, 17, 20);
	craateTreeCrops(TREE::RED, 18, 20);
	craateTreeCrops(TREE::CACTUS, 19, 20);
	craateTreeCrops(TREE::SNOW, 20, 20);


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
	IMAGEMANAGER->addFrameImage("pumpkin", "./image/object/pumpkinObject.bmp", 135, 48, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cotton", "./image/object/cottonObject.bmp", 124, 51, 3, 1, true, RGB(255, 0, 255));

	// 01 -> 234 인 이미지 
	IMAGEMANAGER->addFrameImage("bush", "./image/object/beetObject.bmp", 210, 42, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("flower", "./image/object/flowerObject.bmp", 135, 39, 5, 1, true, RGB(255, 0, 255));

	// 0 , 1 , 2, 3 따로 사용하는 이미지 
	IMAGEMANAGER->addFrameImage("volcano", "./image/object/volcanoObject.bmp", 288, 51, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rock", "./image/object/rockObject.bmp", 384, 51, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cactus", "./image/object/cactusObject.bmp", 276, 96, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tree", "./image/object/treeObject.bmp", 468, 126, 4, 1, true, RGB(255, 0, 255));
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
		crops->setIsClick();
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::NIGHTSHADE)
	{
		crops* crops;
		crops = new imageCrops;
		crops->init(object, "nightShade", idx, idy);
		crops->setHp(1, 1);
		crops->setIsClick();
		_vCrops.push_back(crops);
	}
	else
	{
		return;
	}
}

void cropsManager::createFrameCrops(OBJECT object, int idx, int idy)
{
	if (object == OBJECT::BEET)
	{
		crops* crops;
		crops = new frameCrops;
		crops->init(object, "beet", idx, idy);
		crops->setHp(1, 1);
		crops->setSpeed(10); 
		crops->setTime();
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::HOT_PEPPER)
	{
		crops* crops;
		crops = new frameCrops;
		crops->init(object, "hotPepper", idx, idy);
		crops->setHp(1, 1);
		crops->setSpeed(12);
		crops->setTime();
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::WHEAT)
	{
		crops* crops;
		crops = new frameCrops;
		crops->init(object, "wheat", idx, idy);
		crops->setHp(1, 1);
		crops->setSpeed(10);
		crops->setTime();
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::PUMPKIN)
	{
		crops* crops;
		crops = new frameCrops;
		crops->init(object, "pumpkin", idx, idy);
		crops->setHp(1, 1);
		crops->setSpeed(14);
		crops->setTime();
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::COTTON)
	{
		crops* crops;
		crops = new frameCrops;
		crops->init(object, "cotton", idx, idy);
		crops->setHp(1, 1);
		crops->setSpeed(12);
		crops->setTime();
		_vCrops.push_back(crops);
	}
	else
	{
		return;
	}
}

void cropsManager::createimageFrameCrops(OBJECT object, int idx, int idy)
{
	if (object == OBJECT::ROCK)
	{
		crops* crops;
		crops = new imageFrameCrops;
		crops->init(object, "rock", idx, idy);
		crops->setHp(3, 3);
		crops->setIsClick();
		crops->setFrameX(RND->getInt(2));
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::COAL)
	{
		crops* crops;
		crops = new imageFrameCrops;
		crops->init(object, "rock", idx, idy);
		crops->setHp(4, 4);
		crops->setIsClick();
		crops->setFrameX(RND->getFromIntTo(2,4));
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::GOLD)
	{
		crops* crops;
		crops = new imageFrameCrops;
		crops->init(object, "rock", idx, idy);
		crops->setHp(5, 5);
		crops->setIsClick();
		crops->setFrameX(RND->getFromIntTo(4, 6));
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::IRON)
	{
		crops* crops;
		crops = new imageFrameCrops;
		crops->init(object, "rock", idx, idy);
		crops->setHp(4, 4);
		crops->setIsClick();
		crops->setFrameX(RND->getFromIntTo(6, 8));
		_vCrops.push_back(crops);
	}
	else if(object == OBJECT::VOLCANIC_IRON)
	{
		crops* crops;
		crops = new imageFrameCrops;
		crops->init(object, "volcano", idx, idy);
		crops->setHp(10, 10);
		crops->setIsClick();
		crops->setFrameX(RND->getFromIntTo(4, 6));
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::VOLCANIC_COAL)
	{
		crops* crops;
		crops = new imageFrameCrops;
		crops->init(object, "volcano", idx, idy);
		crops->setHp(10, 10);
		crops->setIsClick();
		crops->setFrameX(RND->getInt(2));
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::VOLCANIC_GOLD)
	{
		crops* crops;
		crops = new imageFrameCrops;
		crops->init(object, "volcano", idx, idy);
		crops->setHp(10, 10);
		crops->setIsClick();
		crops->setFrameX(RND->getFromIntTo(2, 4));
		_vCrops.push_back(crops);
	}

}

void cropsManager::craateTreeCrops(TREE tree, int idx, int idy)
{
	if (tree == TREE::BASIC)
	{
		crops* crops;
		crops = new treeCrops;
		crops->init(tree, "tree", idx, idy);
		crops->setHp(5, 5);
		crops->setIsClick();
		crops->setFrameX(0);
		_vCrops.push_back(crops);
	}
	else if (tree == TREE::RED)
	{
		crops* crops;
		crops = new treeCrops;
		crops->init(tree, "tree", idx, idy);
		crops->setHp(5, 5);
		crops->setIsClick();
		crops->setFrameX(2);
		_vCrops.push_back(crops);
	}
	else if (tree == TREE::SNOW)
	{
		crops* crops;
		crops = new treeCrops;
		crops->init(tree, "tree", idx, idy);
		crops->setHp(5, 5);
		crops->setIsClick();
		crops->setFrameX(3);
		_vCrops.push_back(crops);
	}
	else if (tree == TREE::CACTUS)
	{
		crops* crops;
		crops = new treeCrops;
		crops->init(tree, "cactus", idx, idy);
		crops->setHp(5, 5);
		crops->setIsClick();
		crops->setFrameX(RND->getInt(4));
		_vCrops.push_back(crops);
	}
}

void cropsManager::removeCrops()
{
	for (_viCrops = _vCrops.begin(); _viCrops != _vCrops.end();)
	{
		//리무브 
		if ((*_viCrops)->getCrops()->hp <= 0)
		{
			//아이템 생성
			if ((*_viCrops)->getCrops()->object != OBJECT::NONE)
			{
				ITEMMANAGER->Dropitem((*_viCrops)->getCrops()->object, (*_viCrops)->getCrops()->centerX, (*_viCrops)->getCrops()->centerY);
			}
			else
			{
				ITEMMANAGER->Dropitem((*_viCrops)->getCrops()->tree,  (*_viCrops)->getCrops()->centerX, (*_viCrops)->getCrops()->centerY);
			}
			_vCrops.erase(_viCrops);
			//커서 초기화 
			CURSORMANAGER->setCursor();
			CURSORMANAGER->getCursor()->setCursorChange();
			break;
		}
		else ++_viCrops;
	}
}
