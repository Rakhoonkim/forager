#include "stdafx.h"
#include "bossScene.h"

bossScene::bossScene()
{
}

bossScene::~bossScene()
{
}

HRESULT bossScene::init()
{
	
	// �÷��̾� 
	_playerManager = new playerManager;
	_playerManager = GAMEDATA->getPlayerManager();


	//MAP�ٽ� �ʱ�ȭ �ϱ� 
	MAPMANAGER->removeTiles();  // �� �ʱ�ȭ 
	MAPMANAGER->MapLoad("inGameNumber4.map");

	return S_OK;
}

void bossScene::release()
{
	_playerManager->release();
}

void bossScene::update()
{
	_playerManager->update();
}

void bossScene::render()
{
	PatBlt(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY, WINSIZEX, WINSIZEY, WHITENESS);
	MAPMANAGER->render();      //MAP
	if (CURSORMANAGER->getCursor()->getObjectPoint()) CURSORMANAGER->render(); // CURSOR
	ITEMMANAGER->render();

	_playerManager->render();  //PLAYER 

	EFFECTMANAGER->render(CAMERAMANAGER->getWorldDC());
	if (!UIMANAGER->getLand()->getLand()) CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY, WINSIZEX, WINSIZEY);
	UIMANAGER->render();	// UIs
}
