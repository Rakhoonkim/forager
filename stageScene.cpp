#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{
	// �÷��̾� 
	_playerManager = new playerManager;
	_playerManager->init();
	// ������Ʈ 
	_objectManager = new objectManager;
	_objectManager->init();
	
	_playerManager->set_CropsManager(_objectManager->get_CropsManager());
	_playerManager->set_BuildManager(_objectManager->get_buildManager());
	_playerManager->set_EnemyManager(_objectManager->get_enemyManager());

	_objectManager->get_enemyManager()->setPlayer(_playerManager->get_player());  // �÷��̾� ��ũ 
	_objectManager->get_CropsManager()->setPlayer(_playerManager->get_player());
	// �� 
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
	// ����Ʈ?
	EFFECTMANAGER->EffectRender(CAMERAMANAGER->getWorldDC());		 // ����Ʈ
	if (CURSORMANAGER->getCursor()->getObjectPoint()) CURSORMANAGER->render(); // CURSOR
	_objectManager->render();  //OBJECT
	ITEMMANAGER->render();
	_playerManager->render();  //PLAYER 
	EFFECTMANAGER->render(CAMERAMANAGER->getWorldDC());
	CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY, WINSIZEX, WINSIZEY);
}
