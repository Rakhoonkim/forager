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
	//createImageBuilding(BUILDING::FORGE, 22, 16);
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
}

void buildManager::render()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		cout << " 눌리냐?? " << endl;
		KEYMANAGER->setKeyDown(VK_LBUTTON, false);
	}
	for (_viBuilding = _vBuilding.begin(); _viBuilding != _vBuilding.end(); _viBuilding++)
	{
		(*_viBuilding)->render();
	}


	IMAGEMANAGER->findImage("furnaceBackground")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2, CAMERAMANAGER->getWorldCamera().cameraY + 50 );
	//IMAGEMANAGER->findImage("bridge")->frameRender(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2, CAMERAMANAGER->getWorldCamera().cameraY + WINSIZEY / 2,0,0);

}

void buildManager::imageSetting()
{
	//산업
	IMAGEMANAGER->addImage("forge", "./image/ui/build/forge.bmp", 96, 96, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sewingStation", "./image/ui/build/sewingStation.bmp", 96, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("furnace", "./image/ui/build/furnace.bmp", 1170, 129, 13, 1, true, RGB(255, 0, 255));

	//농경
	IMAGEMANAGER->addImage("fishTrap", "./image/ui/build/fishTrap.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bridge", "./image/ui/build/bridge.bmp", 96, 42, 2, 1, true, RGB(255, 0, 255));

	//
	IMAGEMANAGER->addImage("furnaceBackground", "./image/ui/build/furnaceBackground.bmp", 250, 512, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("furnaceList", "./image/ui/build/furnaceList.bmp", 220, 405,1,9, true, RGB(255, 0, 255));

}

void buildManager::createImageBuilding(BUILDING build, int idx, int idy)
{
	if (build == BUILDING::FORGE)
	{
		building* construction;
		construction = new imageBuilding;
		construction->init(build, "forge", idx, idy);
		construction->setHp(20, 20);
		_vBuilding.push_back(construction);
	}
	else if (build == BUILDING::SEWING_STATION)
	{
		building* construction;
		construction = new imageBuilding;
		construction->init(build, "sewingStation", idx, idy);
		construction->setHp(20, 20);
		_vBuilding.push_back(construction);
	}
	else if (build == BUILDING::FURNACE)
	{
		building* construction;
		construction = new frameBuilding;
		construction->init(build, "furnace", idx, idy);
		construction->setHp(20, 20);
		_vBuilding.push_back(construction);
	}
	else if (build == BUILDING::FISHTRAP)
	{
		building* construction;
		construction = new imageBuilding;
		construction->init(build, "fishTrap", idx, idy,true);
		construction->setHp(20, 20);
		_vBuilding.push_back(construction);
	}
	else if (build == BUILDING::BRIDGE)
	{
		building* construction;
		construction = new frameBuilding;
		construction->init(build, "bridge", idx, idy, true);
		construction->setHp(20, 20);
		_vBuilding.push_back(construction);
	}
}

void buildManager::createFrameBuilding(BUILDING build, int x, int y)
{
}

void buildManager::removeBuilding()
{
	for (_viBuilding = _vBuilding.begin(); _viBuilding != _vBuilding.end(); ++_viBuilding)
	{
		if ((*_viBuilding)->getBuilding().hp <= 0)
		{
			_vBuilding.erase(_viBuilding);
			CURSORMANAGER->setCursor();
			CURSORMANAGER->getCursor()->setCursorChange();
			break;
		}
		else ++_viBuilding;
	}
}
