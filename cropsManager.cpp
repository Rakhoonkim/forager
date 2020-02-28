#include "stdafx.h"
#include "cropsManager.h"
#include "player.h"

cropsManager::cropsManager()
{
}

cropsManager::~cropsManager()
{
}

HRESULT cropsManager::init()
{
	imageSetting();

	//====================== TEST 오프젝트==================================
	//createImageCrops(OBJECT::CINDERBLOOM, 17, 16);
	//createImageCrops(OBJECT::NIGHTSHADE, 18, 16);

	//createFrameCrops(OBJECT::BEET, 19, 16);
	//createFrameCrops(OBJECT::HOT_PEPPER, 20, 16);
	//createFrameCrops(OBJECT::COTTON, 21, 16);
	//createFrameCrops(OBJECT::WHEAT, 22, 16);
	//createFrameCrops(OBJECT::PUMPKIN, 23, 16);

	//createimageFrameCrops(OBJECT::ROCK, 24, 16);
	//createimageFrameCrops(OBJECT::COAL, 25, 16);
	//createimageFrameCrops(OBJECT::GOLD, 26, 16);
	//createimageFrameCrops(OBJECT::IRON, 27, 16);
	//createimageFrameCrops(OBJECT::VOLCANIC_COAL, 17, 17);
	//createimageFrameCrops(OBJECT::VOLCANIC_GOLD, 18, 17);
	//createimageFrameCrops(OBJECT::VOLCANIC_IRON, 19, 17);

	//createFrameCrops(OBJECT::FLOWER_1, 20, 17);
	//createFrameCrops(OBJECT::FLOWER_1, 21, 17);
	//createFrameCrops(OBJECT::FLOWER_1, 22, 17);
	//createFrameCrops(OBJECT::BUSH, 23, 17);
	//createFrameCrops(OBJECT::BUSH, 24, 17);
	//createFrameCrops(OBJECT::BUSH, 25, 17);


	//craateTreeCrops(TREE::BASIC, 17, 20);
	//craateTreeCrops(TREE::RED, 18, 20);
	//craateTreeCrops(TREE::CACTUS, 19, 20);
	//craateTreeCrops(TREE::SNOW, 20, 20);

	_effect = new alphaEffect;
	_effect->init();


	//작물을 만들기 위한 
	_cropsTimer = TIMEMANAGER->getWorldTime();
	_rockTimer = TIMEMANAGER->getWorldTime();
	_treeTimer = TIMEMANAGER->getWorldTime();
	_maxCrops = 0;
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

		// 바닥 퍼지는 이펙트 
		if ((*_viCrops)->getCrops()->isEffect)
		{
			EFFECTMANAGER->play("attackEffect", (*_viCrops)->getCrops()->centerX, (*_viCrops)->getCrops()->centerY);
			(*_viCrops)->getCrops()->isEffect = false;
		}

		//깜박거리는 효과 
		if (!(*_viCrops)->getCrops()->isHit)
		{
			(*_viCrops)->getCrops()->hitTime = TIMEMANAGER->getWorldTime();
		}
		else
		{
		    // 깜박거리는 카운터 
			(*_viCrops)->getCrops()->hitCount++;
			if ((*_viCrops)->getCrops()->hitCount % 5 ==0)
			{
				if ((*_viCrops)->getCrops()->alpha == 0)
				{
					(*_viCrops)->getCrops()->alpha = 150;
				}
				else (*_viCrops)->getCrops()->alpha = 0;
			}
			// 0.7초가 지나면 되돌린다.
			if ((*_viCrops)->getCrops()->hitTime + 0.7 <= TIMEMANAGER->getWorldTime())
			{
				(*_viCrops)->getCrops()->isHit = false;
				(*_viCrops)->getCrops()->hitCount = 0;
			}
		}
	}

	// TEST 랜덤 타일 넘버 
	if (KEYMANAGER->isStayKeyDown('M'))
	{
		POINT rnd;
		rnd = MAPMANAGER->randomObjectTile();
		//cout << rnd.x << rnd.y << endl;
	}

	CropsMakeUpdate();
	removeCrops();			// 작물 HP < 0시 제거 
	_effect->update();
	cout << "최대 작물 개수 : " << _maxCrops << endl;
}

void cropsManager::render()
{
	//for (_viCrops = _vCrops.begin(); _viCrops != _vCrops.end(); ++_viCrops)
	//{
	//	(*_viCrops)->render();
	//}
	_effect->render();
}

void cropsManager::imageSetting()
{
	// 1장짜리 
	IMAGEMANAGER->addImage("cinderBloom", "./image/object/cinderBloomObject.bmp", 54, 54, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("nightShade", "./image/object/nightShadeObject.bmp", 48, 48, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("lavender", "./image/object/lavenderObject.bmp", 54, 54, true, RGB(255, 0, 255));
	// 0 1 2 이미지 
	IMAGEMANAGER->addFrameImage("beet", "./image/object/beetObject.bmp", 90, 36, 3, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("hotPepper", "./image/object/hotPepperObject.bmp", 135, 42, 3, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("wheat", "./image/object/wheatObject.bmp", 135, 51, 3, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("pumpkin", "./image/object/pumpkinObject.bmp", 135, 48, 3, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("cotton", "./image/object/cottonObject.bmp", 124, 51, 3, 1, true, RGB(255, 0, 255), true);

	// 01 -> 234 인 이미지 
	IMAGEMANAGER->addFrameImage("bush", "./image/object/bushObject.bmp", 210, 42, 5, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("flower", "./image/object/flowerObject.bmp", 135, 39, 5, 1, true, RGB(255, 0, 255), true);

	// 0 , 1 , 2, 3 따로 사용하는 이미지 
	IMAGEMANAGER->addFrameImage("volcano", "./image/object/volcanoObject.bmp", 288, 51, 6, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("rock", "./image/object/rockObject.bmp", 384, 51, 8, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("cactus", "./image/object/cactusObject.bmp", 276, 96, 4, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("tree", "./image/object/treeObject.bmp", 468, 126, 4, 1, true, RGB(255, 0, 255),true);
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
	_maxCrops++;  //곡물 수 증가

	crops* crops;
	crops = new imageCrops;

	if (object == OBJECT::CINDERBLOOM)
	{
		crops->init(object, "cinderBloom", idx, idy);
		crops->setHp(1, 1);
		crops->setIsClick();
		crops->setExpCrops(5);
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::NIGHTSHADE)
	{
		crops->init(object, "nightShade", idx, idy);
		crops->setHp(1, 1);
		crops->setIsClick();
		crops->setExpCrops(10);
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::LAVENDER)
	{
		crops->init(object, "lavender", idx, idy);
		crops->setHp(1, 1);
		crops->setIsClick();
		crops->setExpCrops(10);
		_vCrops.push_back(crops);
	}
	else
	{
		return;
	}

	//제트오더 추가 
	ZORDER->addZorder(STAGEOBJECT::CROPS, NULL, crops, NULL, NULL, NULL);
}

void cropsManager::createFrameCrops(OBJECT object, int idx, int idy)
{
	_maxCrops++; //곡물 수 증가
	crops* tempCrops;
	tempCrops = new frameCrops;
	if (object == OBJECT::BEET)
	{
		tempCrops->init(object, "beet", idx, idy);
		tempCrops->setHp(1, 1);
		tempCrops->setSpeed(10);
		tempCrops->setExpCrops(5);
		tempCrops->setTime();
		_vCrops.push_back(tempCrops);
	}
	else if (object == OBJECT::HOT_PEPPER)
	{
		tempCrops->init(object, "hotPepper", idx, idy);
		tempCrops->setHp(1, 1);
		tempCrops->setSpeed(12);
		tempCrops->setExpCrops(15);
		tempCrops->setTime();
		_vCrops.push_back(tempCrops);
	}
	else if (object == OBJECT::WHEAT)
	{
		tempCrops->init(object, "wheat", idx, idy);
		tempCrops->setHp(1, 1);
		tempCrops->setSpeed(10);
		tempCrops->setExpCrops(5);
		tempCrops->setTime();
		_vCrops.push_back(tempCrops);
	}
	else if (object == OBJECT::PUMPKIN)
	{
		tempCrops->init(object, "pumpkin", idx, idy);
		tempCrops->setHp(1, 1);
		tempCrops->setSpeed(14);
		tempCrops->setExpCrops(15);
		tempCrops->setTime();
		_vCrops.push_back(tempCrops);
	}
	else if (object == OBJECT::COTTON)
	{
		tempCrops->init(object, "cotton", idx, idy);
		tempCrops->setHp(1, 1);
		tempCrops->setSpeed(12);
		tempCrops->setExpCrops(10);
		tempCrops->setTime();
		_vCrops.push_back(tempCrops);
	}
	else if (object == OBJECT::FLOWER_1 || object == OBJECT::FLOWER_2 || object == OBJECT::FLOWER_3)
	{
		crops* flower;
		flower = new multiImageCrops;

		flower->init(object, "flower", idx, idy);
		flower->setHp(1, 1);
		flower->setSpeed(12);
		flower->setExpCrops(10);
		flower->setTime();
		_vCrops.push_back(flower);
		ZORDER->addZorder(STAGEOBJECT::CROPS, NULL, flower, NULL, NULL, NULL);
		return;
	}
	else if (object == OBJECT::BUSH)
	{
		crops* bush;
		bush = new multiImageCrops;
		bush->init(object, "bush", idx, idy);
		bush->setHp(3, 3);
		bush->setSpeed(12);
		bush->setExpCrops(7);
		bush->setTime();
		_vCrops.push_back(bush);
		ZORDER->addZorder(STAGEOBJECT::CROPS, NULL, bush, NULL, NULL, NULL);
		return;
	}
	else
	{
		return;
	}
	////제트오더 추가 
	ZORDER->addZorder(STAGEOBJECT::CROPS, NULL, tempCrops, NULL, NULL, NULL);
}

void cropsManager::createimageFrameCrops(OBJECT object, int idx, int idy)
{
	_maxCrops++; //곡물 수 증가
	crops* crops;
	crops = new imageFrameCrops;
	if (object == OBJECT::ROCK)
	{
		crops->init(object, "rock", idx, idy);
		crops->setHp(3, 3);
		crops->setIsClick();
		crops->setExpCrops(10);
		crops->setFrameX(RND->getInt(2));
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::COAL)
	{
		crops->init(object, "rock", idx, idy);
		crops->setHp(4, 4);
		crops->setIsClick();
		crops->setExpCrops(10);
		crops->setFrameX(RND->getFromIntTo(6, 8));
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::GOLD)
	{
		crops->init(object, "rock", idx, idy);
		crops->setHp(5, 5);
		crops->setIsClick();
		crops->setExpCrops(15);
		crops->setFrameX(RND->getFromIntTo(4, 6));
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::IRON)
	{
		crops->init(object, "rock", idx, idy);
		crops->setHp(4, 4);
		crops->setIsClick();
		crops->setExpCrops(15);
		crops->setFrameX(RND->getFromIntTo(2, 4));
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::VOLCANIC_IRON)
	{
		crops->init(object, "volcano", idx, idy);
		crops->setHp(10, 10);
		crops->setIsClick();
		crops->setExpCrops(15);
		crops->setFrameX(RND->getFromIntTo(4, 6));
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::VOLCANIC_COAL)
	{
		crops->init(object, "volcano", idx, idy);
		crops->setHp(10, 10);
		crops->setIsClick();
		crops->setExpCrops(15);
		crops->setFrameX(RND->getInt(2));
		_vCrops.push_back(crops);
	}
	else if (object == OBJECT::VOLCANIC_GOLD)
	{
		crops->init(object, "volcano", idx, idy);
		crops->setHp(10, 10);
		crops->setIsClick();
		crops->setExpCrops(20);
		crops->setFrameX(RND->getFromIntTo(2, 4));
		_vCrops.push_back(crops);
	}

	////제트오더 추가 
	ZORDER->addZorder(STAGEOBJECT::CROPS, NULL, crops, NULL, NULL, NULL);
}

void cropsManager::craateTreeCrops(TREE tree, int idx, int idy)
{
	_maxCrops++; //곡물 수 증가
	crops* crops;
	crops = new treeCrops;
	if (tree == TREE::BASIC)
	{
		crops->init(tree, "tree", idx, idy);
		crops->setHp(5, 5);
		crops->setIsClick();
		crops->setFrameX(0);
		crops->setExpCrops(5);
		_vCrops.push_back(crops);
	}
	else if (tree == TREE::RED)
	{
		crops->init(tree, "tree", idx, idy);
		crops->setHp(5, 5);
		crops->setIsClick();
		crops->setFrameX(2);
		crops->setExpCrops(10);
		_vCrops.push_back(crops);
	}
	else if (tree == TREE::SNOW)
	{
		crops->init(tree, "tree", idx, idy);
		crops->setHp(5, 5);
		crops->setIsClick();
		crops->setFrameX(3);
		crops->setExpCrops(10);
		_vCrops.push_back(crops);
	}
	else if (tree == TREE::CACTUS)
	{
		crops->init(tree, "cactus", idx, idy);
		crops->setHp(5, 5);
		crops->setIsClick();
		crops->setFrameX(RND->getInt(4));
		crops->setExpCrops(10);
		_vCrops.push_back(crops);
	}

	////제트오더 추가 
	ZORDER->addZorder(STAGEOBJECT::CROPS, NULL, crops, NULL, NULL, NULL);
}

void cropsManager::CropsMakeUpdate()
{
	if (_maxCrops >= (15 * MAPMANAGER->getMapCount()))  // 가지고 있는 맵의 개수 
	{
		//작물이 바로 나타나지 않도록 
		_cropsTimer = TIMEMANAGER->getWorldTime();
		_rockTimer = TIMEMANAGER->getWorldTime();
		_treeTimer = TIMEMANAGER->getWorldTime();
		return;
	}


	if (_cropsTimer + RND->getFromIntTo(10, 15) <= TIMEMANAGER->getWorldTime())
	{
		_cropsTimer = TIMEMANAGER->getWorldTime();
		POINT rnd;
		rnd = MAPMANAGER->randomObjectTile();

		int tempRndNum = RND->getInt(100);
		if (tempRndNum <= 55)   //55% 확률 
		{
			int rndNum = RND->getFromIntTo(7, 13); // (0~7)

			createFrameCrops((OBJECT)rndNum, rnd.x, rnd.y);
		}
		else if (tempRndNum <= 85)  // 30% 
		{
			int rndNum = RND->getFromIntTo(14, 18); // (0~7)

			createFrameCrops((OBJECT)rndNum, rnd.x, rnd.y);
		}
		else if(tempRndNum <= 95) // 10 % 
		{
			createFrameCrops(OBJECT::BUSH, rnd.x, rnd.y);
		}
		else 
		{
			createFrameCrops(OBJECT::COTTON, rnd.x, rnd.y);
		}
	}


	if (_rockTimer + RND->getFromIntTo(7, 15) <= TIMEMANAGER->getWorldTime())
	{
		_rockTimer = TIMEMANAGER->getWorldTime();

		POINT rnd;
		rnd = MAPMANAGER->randomObjectTile();
		
		int tempRndNum2 = RND->getInt(100);

		if (tempRndNum2 < 75)  // 75%
		{
			int rndNum = RND->getInt(4); // (0~3)
			if (rnd.x != 0 && rnd.y != 0) createimageFrameCrops((OBJECT)rndNum, rnd.x, rnd.y);
		}
		else
		{
			int rndNum = RND->getFromIntTo(4,7); // (4~6)
			if (rnd.x != 0 && rnd.y != 0) createimageFrameCrops((OBJECT)rndNum, rnd.x, rnd.y);
		}
	
	}


	if (_treeTimer + RND->getFromIntTo(7, 15) <= TIMEMANAGER->getWorldTime())
	{
		_treeTimer = TIMEMANAGER->getWorldTime();

		POINT rnd;
		rnd = MAPMANAGER->randomObjectTile();
		
		if (rnd.x != 0 && rnd.y != 0) craateTreeCrops(TREE::BASIC, rnd.x, rnd.y);
	}

}

void cropsManager::removeCrops()
{
	for (_viCrops = _vCrops.begin(); _viCrops != _vCrops.end();)
	{
		//리무브 
		if ((*_viCrops)->getCrops()->hp <= 0)
		{
			//전체 곡물 수 감소
			_maxCrops--;

			//오브젝트 해제
			MAPMANAGER->setRemoveObject((*_viCrops)->getCrops()->idx, (*_viCrops)->getCrops()->idy);

			//아이템 생성
			if ((*_viCrops)->getCrops()->object != OBJECT::NONE)
			{
				ITEMMANAGER->Dropitem((*_viCrops)->getCrops()->object, (*_viCrops)->getCrops()->centerX, (*_viCrops)->getCrops()->centerY);
			}
			else
			{
				ITEMMANAGER->Dropitem((*_viCrops)->getCrops()->tree, (*_viCrops)->getCrops()->centerX, (*_viCrops)->getCrops()->centerY);
			}
			//경험치 증가
			_player->playerExp((*_viCrops)->getCrops()->exp);
			//이펙트
			_effect->play("expNum", (*_viCrops)->getCrops()->exp, _player->get_PlayerAddress()->x - 15, _player->get_PlayerAddress()->y - 15);
			//작물 제거 
			_vCrops.erase(_viCrops);
			//커서 초기화 
			CURSORMANAGER->setCursor();
			CURSORMANAGER->getCursor()->setCursorChange();
			break;
		}
		else ++_viCrops;
	}
}
