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
	return S_OK;
}

void buildManager::release()
{
}

void buildManager::update()
{
}

void buildManager::render()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		cout << " ³ª´«¤©·Á?? " << endl;
		
	}

	IMAGEMANAGER->findImage("fishTrap")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2, CAMERAMANAGER->getWorldCamera().cameraY + WINSIZEY / 2);
	//IMAGEMANAGER->findImage("bridge")->frameRender(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX + WINSIZEX / 2, CAMERAMANAGER->getWorldCamera().cameraY + WINSIZEY / 2,0,0);

}

void buildManager::imageSetting()
{
	//»ê¾÷
	IMAGEMANAGER->addImage("forge", "./image/ui/build/forge.bmp", 96, 96, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sewingStation", "./image/ui/build/sewingStation.bmp", 96, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("furnace", "./image/ui/build/furnace.bmp", 1170, 129, 13, 1, true, RGB(255, 0, 255));

	//³ó°æ
	IMAGEMANAGER->addImage("fishTrap", "./image/ui/build/fishTrap.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bridge", "./image/ui/build/bridge.bmp", 96, 42, 2, 1, true, RGB(255, 0, 255));

}
