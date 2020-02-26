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
	
	_playerManager->set_CropsManager(_objectManager->get_CropsManager());
	_playerManager->set_BuildManager(_objectManager->get_buildManager());
	_playerManager->set_EnemyManager(_objectManager->get_enemyManager());
	_playerManager->set_puzzleManager(_objectManager->get_puzzleManager());


	_objectManager->get_enemyManager()->setPlayer(_playerManager->get_player());  // 플레이어 링크 
	_objectManager->get_CropsManager()->setPlayer(_playerManager->get_player());
	// 맵 


	MAPMANAGER->setObjectManager(_objectManager);
	MAPMANAGER->MapLoad("inGameNumber2.map");
	

	UIMANAGER->getEquipment()->setSkillPount(&_playerManager->get_player()->get_PlayerAddress()->skillPount);
	
	GAMEDATA->setPlayerManager(_playerManager);
	GAMEDATA->setObjectManager(_objectManager);
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
	// 이펙트?
	EFFECTMANAGER->EffectRender(CAMERAMANAGER->getWorldDC());		 // 이펙트
	if (CURSORMANAGER->getCursor()->getObjectPoint()) CURSORMANAGER->render(); // CURSOR
	_objectManager->render();  //OBJECT
	ITEMMANAGER->render();
	_playerManager->render();  //PLAYER 
	EFFECTMANAGER->render(CAMERAMANAGER->getWorldDC());


	if (!UIMANAGER->getLand()->getLand()) CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY, WINSIZEX, WINSIZEY);

	UIMANAGER->render();	// UI
}
