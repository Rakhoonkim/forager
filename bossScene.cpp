#include "stdafx.h"
#include "bossScene.h"
#include "stageScene.h"

bossScene::bossScene()
{
}

bossScene::~bossScene()
{
}

HRESULT bossScene::init()
{
	// ÇÃ·¹ÀÌ¾î 
	ZORDER->release();
	_playerManager = new playerManager;
	_playerManager = GAMEDATA->getPlayerManager();
	ZORDER->addZorder(STAGEOBJECT::PLAYER, _playerManager->get_player(), NULL, NULL, NULL, NULL);
	_enemyManager = new enemyManager;
	_enemyManager->init();
	_playerManager->get_player()->setPlayerXY(22, 33);
	//temple
	_templeManager = new templeManager;
	_templeManager->setBulletManager(_enemyManager->getBulletManager());
	_templeManager->setPlayer(_playerManager->get_player()->get_PlayerAddress());
	_templeManager->init();
	
	_enemyManager->AutoEnemySet(true);
	_playerManager->set_EnemyManager(_enemyManager);
	_enemyManager->setPlayer(_playerManager->get_player());
	GAMEDATA->setTempleManager(_templeManager);
	GAMEDATA->setEnemyManager(_enemyManager);

	MAPMANAGER->removeTiles();  // ¸Ê ÃÊ±âÈ­ 
	MAPMANAGER->BossMapLoad("inGameNumber3.map");



	_exitScene = RectMake(1340, 2100, 100, 60);



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
	ZORDER->update();
	if (_templeManager->getBossAttack()) { _enemyManager->BossAttack(); }
	exitTemple();
}

void bossScene::render()
{
	PatBlt(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY, WINSIZEX, WINSIZEY, BLACKNESS);
	MAPMANAGER->stageRender();      //MAP
	if (CURSORMANAGER->getCursor()->getObjectPoint()) CURSORMANAGER->render(); // CURSOR
	_enemyManager->render();   // ÃÑ¾Ë ·»´õ
	ITEMMANAGER->render();
	EFFECTMANAGER->render(CAMERAMANAGER->getWorldDC());
	ZORDER->render();
	_playerManager->render();  //PLAYER 
	_templeManager->render(); 
	if (!UIMANAGER->getLand()->getLand()) CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY, WINSIZEX, WINSIZEY);
	UIMANAGER->render();	// UIs

}

void bossScene::exitTemple()
{
	RECT temp;
	if (IntersectRect(&temp, &_exitScene, &_playerManager->get_player()->get_playerRect()))
	{
		_objectManager = GAMEDATA->getObjectManager();
		_playerManager->set_EnemyManager(GAMEDATA->getObjectManager()->get_enemyManager());
		GAMEDATA->setPlayerManager(_playerManager);
		//_playerManager = GAMEDATA->getPlayerManager();
		SCENEMANAGER->changeScene("STAGE");
		ZORDER->setZorder(GAMEDATA->getZorder());
		GAMEDATA->setPlayerManager(_playerManager);
		GAMEDATA->setObjectManager(_objectManager);
		SCENEMANAGER->getCurrentScene()->nextScene();
	}
}
