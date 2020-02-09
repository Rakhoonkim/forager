#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{
	// 플레이어 
	_playerManager = new playerManager;
	_playerManager->init();
	// 오브젝트 
	_objectManager = new objectManager;
	_objectManager->init();
	// 맵 
	_playerManager->set_CropsManager(_objectManager->get_CropsManager());
	MAPMANAGER->MapLoad("inGameNumber1.map");
	return S_OK;
}

void stageScene::release()
{
	_playerManager->release();
	_objectManager->release();
}

void stageScene::update()
{
	_playerManager->update();
	_objectManager->update();
}

void stageScene::render()
{
	//PatBlt(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY, WINSIZEX, WINSIZEY,WHITENESS);
	IMAGEMANAGER->findImage("background")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY);
	MAPMANAGER->render();      //MAP
	if (CURSORMANAGER->getCursor()->getObjectPoint()) CURSORMANAGER->render(); // CURSOR
	_objectManager->render();  //OBJECT
	_playerManager->render();  //PLAYER 
	CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY, WINSIZEX, WINSIZEY);
}
