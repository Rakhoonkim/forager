#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{
	_playerManager = new playerManager;
	_playerManager->init();
	MAPMANAGER->MapLoad("inGameNumber1.map");
	return S_OK;
}

void stageScene::release()
{
	_playerManager->release();
}

void stageScene::update()
{
	_playerManager->update();
}

void stageScene::render()
{
	//PatBlt(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY, WINSIZEX, WINSIZEY,WHITENESS);
	IMAGEMANAGER->findImage("background")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY);
	MAPMANAGER->render();
	_playerManager->render();
	CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY, WINSIZEX, WINSIZEY);
}
