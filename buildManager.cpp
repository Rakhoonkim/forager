#include "stdafx.h"
#include "buildManager.h"

buildManager::buildManager()
{
}

buildManager::~buildManager()
{
}

HRESULT buildManager::init()
{
	imageSetting();
	createImageBuilding(BUILDING::FURNACE, 17, 14);
	createImageBuilding(BUILDING::FORGE, 20, 14);
	createImageBuilding(BUILDING::SEWING_STATION, 23, 14);
	//createImageBuilding(BUILDING::FORGE, 22, 16);
	_isUsed = false;
	return S_OK;
}

void buildManager::release()
{
}

void buildManager::update()
{
	for (_viBuilding = _vBuilding.begin(); _viBuilding != _vBuilding.end(); _viBuilding++)
	{
		(*_viBuilding)->update();
	}
	usedCheck();
}

void buildManager::render()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//cout << " 눌리냐?? " << endl;
		KEYMANAGER->setKeyDown(VK_LBUTTON, false);
	}
	for (_viBuilding = _vBuilding.begin(); _viBuilding != _vBuilding.end(); _viBuilding++)
	{
		(*_viBuilding)->render();
	}
	for (_viBuilding = _vBuilding.begin(); _viBuilding != _vBuilding.end(); _viBuilding++)
	{
		(*_viBuilding)->EffectRender();
	}

	//IMAGEMANAGER->findImage("furnaceBackground")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 - 200, CAMERAMANAGER->getWorldCamera().cameraY + 50 );
	//IMAGEMANAGER->findImage("forgeBackground")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2, CAMERAMANAGER->getWorldCamera().cameraY + 50);
	//IMAGEMANAGER->findImage("sewingBackground")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2 + 200, CAMERAMANAGER->getWorldCamera().cameraY + 50);
}

void buildManager::imageSetting()
{
	//산업
	IMAGEMANAGER->addImage("forge", "./image/ui/build/forge.bmp", 96, 96, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sewingStation", "./image/ui/build/sewingStation.bmp", 96, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("furnace", "./image/ui/build/furnace.bmp", 1170, 129, 13, 1, true, RGB(255, 0, 255));
	KEYANIMANAGER->addDefaultFrameAnimation("furnace", "furnace", 10, false, true);
	//농경
	IMAGEMANAGER->addImage("fishTrap", "./image/ui/build/fishTrap.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bridge", "./image/ui/build/bridge.bmp", 96, 42, 2, 1, true, RGB(255, 0, 255));

	//장비 키면 
	IMAGEMANAGER->addImage("furnaceBackground", "./image/ui/build/furnaceBackground.bmp", 250, 512, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("furnaceList", "./image/ui/build/furnaceList.bmp", 220, 405,1,9, true, RGB(255, 0, 255), true);

	IMAGEMANAGER->addImage("forgeBackground", "./image/ui/build/forgeBackground.bmp", 250, 337, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("forgeList", "./image/ui/build/forgeList.bmp", 220, 225, 1, 5, true, RGB(255, 0, 255), true);

	IMAGEMANAGER->addImage("sewingBackground", "./image/ui/build/sewingBackground.bmp", 250, 225, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sewingList", "./image/ui/build/sewingList.bmp", 220,225, 1, 5, true, RGB(255, 0, 255),true);

	IMAGEMANAGER->addImage("EbuttonFarming", "./image/ui/build/EbuttonFarming.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ebutton", "./image/ui/build/Ebutton.bmp", 50, 50, true, RGB(255, 0, 255));


	//연기

	IMAGEMANAGER->addFrameImage("smoke", "./image/ui/build/smoke.bmp", 135, 26, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smokeExplosion", "./image/ui/build/smokeExplosion.bmp", 135, 26, 5, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("smoke", "smoke", 135, 26, 27, 26, 1, 0.1f, 10);


	EFFECTMANAGER->addEffect("smokeExplosion", "smokeExplosion", 135, 26, 27, 26, 10, 0.8f, 5);

}

void buildManager::createImageBuilding(BUILDING build, int idx, int idy)
{
	if (build == BUILDING::FORGE)
	{
		building* construction;
		construction = new forge;
		construction->init(build, "forge", idx, idy);
		construction->setHp(20, 20);
		_vBuilding.push_back(construction);
	}
	else if (build == BUILDING::SEWING_STATION)
	{
		building* construction;
		construction = new sewingStation;
		construction->init(build, "sewingStation", idx, idy);
		construction->setHp(20, 20);
		_vBuilding.push_back(construction);
	}
	else if (build == BUILDING::FURNACE)
	{
		building* construction;
		construction = new furnace;
		construction->init(build, "furnace", idx, idy);
		construction->setHp(20, 20);
		construction->setAni();
		_vBuilding.push_back(construction);
	}
	else if (build == BUILDING::FISHTRAP)
	{
		building* construction;
		construction = new fishTrap;
		construction->init(build, "fishTrap", idx, idy,true);
		construction->setHp(20, 20);
		_vBuilding.push_back(construction);
	}
	else if (build == BUILDING::BRIDGE)
	{
		//인덱스 워터 속성 바꾸기 
		building* construction;
		construction = new bridge;
		construction->init(build, "bridge", idx, idy, true);
		construction->setHp(20, 20);
		_vBuilding.push_back(construction);

		MAPMANAGER->setRemoveWater(idx, idy); // 맵을 이동할 수 있게 정의 
	}
}

void buildManager::createFrameBuilding(BUILDING build, int x, int y)
{
}

//괜찮을까..for문 계속돌아서 사용중인지 아닌지 판단
bool buildManager::usedCheck()
{
	for (_viBuilding = _vBuilding.begin(); _viBuilding != _vBuilding.end(); _viBuilding++)
	{
		if ((*_viBuilding)->getUsed())
		{
			return true;
		}
	}
	return false;
}

void buildManager::removeBuilding()
{
	for (_viBuilding = _vBuilding.begin(); _viBuilding != _vBuilding.end(); ++_viBuilding)
	{
		if ((*_viBuilding)->getBuilding()->hp <= 0)
		{
			_vBuilding.erase(_viBuilding);
			CURSORMANAGER->setCursor();
			CURSORMANAGER->getCursor()->setCursorChange();
			break;
		}
		else ++_viBuilding;
	}
}
