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
	// 플레이어 
	_playerManager = new playerManager;
	_playerManager = GAMEDATA->getPlayerManager();

	_enemyManager = new enemyManager;
	_enemyManager->init();
	_playerManager->get_player()->setPlayerXY(22, 33);
	//temple
	_templeManager = new templeManager;
	_templeManager->setBulletManager(_enemyManager->getBulletManager());
	_templeManager->setPlayer(_playerManager->get_player()->get_PlayerAddress());
	_templeManager->init();


	_playerManager->set_EnemyManager(_enemyManager);
	_enemyManager->setPlayer(_playerManager->get_player());

	GAMEDATA->setTempleManager(_templeManager);
	GAMEDATA->setEenemyManager(_enemyManager);

	MAPMANAGER->removeTiles();  // 맵 초기화 
	MAPMANAGER->BossMapLoad("inGameNumber3.map");

	temp = false;

	return S_OK;
}

void bossScene::release()
{
	_templeManager->release();
	_playerManager->release();
	_enemyManager->release();
}

void bossScene::update()
{
	_templeManager->update();
	_playerManager->update();
	_enemyManager->update();
	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		temp = true;
	}
	if (temp) { _enemyManager->BossAttack(); }
}

void bossScene::render()
{
	PatBlt(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY, WINSIZEX, WINSIZEY, BLACKNESS);
	MAPMANAGER->stageRender();      //MAP
	if (CURSORMANAGER->getCursor()->getObjectPoint()) CURSORMANAGER->render(); // CURSOR
	ITEMMANAGER->render();
	_enemyManager->render();
	_playerManager->render();  //PLAYER 
	EFFECTMANAGER->render(CAMERAMANAGER->getWorldDC());
	_templeManager->render(); 

	if (!UIMANAGER->getLand()->getLand()) CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY, WINSIZEX, WINSIZEY);
	UIMANAGER->render();	// UIs
}
