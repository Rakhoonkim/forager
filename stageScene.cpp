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
	
	_weather = new weather;
	_weather->init();

	_playerManager->set_CropsManager(_objectManager->get_CropsManager());
	_playerManager->set_BuildManager(_objectManager->get_buildManager());
	_playerManager->set_EnemyManager(_objectManager->get_enemyManager());
	_playerManager->set_puzzleManager(_objectManager->get_puzzleManager());
	

	_objectManager->get_enemyManager()->setPlayer(_playerManager->get_player());  // 플레이어 링크 
	_objectManager->get_CropsManager()->setPlayer(_playerManager->get_player());
	// 맵 
	MAPMANAGER->release();
	MAPMANAGER->setObjectManager(_objectManager);
	MAPMANAGER->MapLoad("inGameNumber2.map");

	UIMANAGER->getEquipment()->setSkillPount(&_playerManager->get_player()->get_PlayerAddress()->skillPount);
	
	//게임 데이터 저장
	GAMEDATA->setPlayerManager(_playerManager);
	GAMEDATA->setObjectManager(_objectManager);
	GAMEDATA->save();

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
	//_weather->update(); // 날씨
	ZORDER->update();
	BossEntranceMouseCllision();  // 보스씬 마우스
	AlphaImage();
}

void stageScene::render()
{
	//PatBlt(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY, WINSIZEX, WINSIZEY,WHITENESS);
	IMAGEMANAGER->findImage("background")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY);
	MAPMANAGER->stageRender();      //MAP

	EFFECTMANAGER->EffectRender(CAMERAMANAGER->getWorldDC());		 // 이펙트
	if (CURSORMANAGER->getCursor()->getObjectPoint()) CURSORMANAGER->render(); // CURSOR
	ZORDER->render();
	_playerManager->render();  //PLAYER 
	ITEMMANAGER->render();
	EFFECTMANAGER->render(CAMERAMANAGER->getWorldDC());
	_objectManager->render();  //OBJECT에서 빌딩만 
	if (!UIMANAGER->getLand()->getLand()) CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY, WINSIZEX, WINSIZEY);
	//_weather->render(getMemDC());
	UIMANAGER->render();	// UI
}

void stageScene::BossEntranceMouseCllision()
{
	if (180 >= getDistance(_objectManager->get_puzzleManager()->getFireTempleEntrance()->getPuzzle()->x, _objectManager->get_puzzleManager()->getFireTempleEntrance()->getPuzzle()->y, _playerManager->get_player()->get_PlayerAddress()->x, _playerManager->get_player()->get_PlayerAddress()->y))
	{
		if (PtInRect(&_objectManager->get_puzzleManager()->getFireTempleEntrance()->getPuzzle()->rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			//CURSORMANAGER->setBuildPoint();
			//CURSORMANAGER->getCursor()->setCursorXY(_objectManager->get_puzzleManager()->getFireTempleEntrance()->getPuzzle()->x - CAMERAMANAGER->getWorldCamera().cameraX + 49, _objectManager->get_puzzleManager()->getFireTempleEntrance()->getPuzzle()->y - CAMERAMANAGER->getWorldCamera().cameraY + 75);
			_objectManager->get_puzzleManager()->getFireTempleEntrance()->getPuzzle()->isClick = true;
		}
		else _objectManager->get_puzzleManager()->getFireTempleEntrance()->getPuzzle()->isClick = false;
	}
	else _objectManager->get_puzzleManager()->getFireTempleEntrance()->getPuzzle()->isClick = false;
}

void stageScene::nextScene()
{
	_playerManager = GAMEDATA->getPlayerManager();
	_objectManager = GAMEDATA->getObjectManager();
	_objectManager->get_enemyManager()->AutoEnemySet(true);
	//_playerManager->set_CropsManager(_objectManager->get_CropsManager());
	//_playerManager->set_BuildManager(_objectManager->get_buildManager());
	//_playerManager->set_EnemyManager(_objectManager->get_enemyManager());
	//_playerManager->set_puzzleManager(_objectManager->get_puzzleManager());
	//_objectManager->get_enemyManager()->setPlayer(_playerManager->get_player());  // 플레이어 링크 
	//_objectManager->get_CropsManager()->setPlayer(_playerManager->get_player());
	MAPMANAGER->setObjectManager(_objectManager);
	UIMANAGER->getEquipment()->setSkillPount(&_playerManager->get_player()->get_PlayerAddress()->skillPount);
	UIMANAGER->playerAdressLink(_playerManager->get_player()->get_PlayerAddress());
	_playerManager->get_player()->setPlayerXY(36, 29);
}

void stageScene::AlphaImage()
{
	RECT temp;
	if (_playerManager->get_player()->get_PlayerAddress()->y - 30 <= _objectManager->get_puzzleManager()->getDruidTree()->getPuzzle()->y  && IntersectRect(&temp, &_objectManager->get_puzzleManager()->getDruidTree()->getRect(), &_playerManager->get_player()->get_playerRect()))
	{
		_objectManager->get_puzzleManager()->getDruidTree()->setAlpha(150);
	}
	else _objectManager->get_puzzleManager()->getDruidTree()->setAlpha(0);

	RECT temp2;
	if (_playerManager->get_player()->get_PlayerAddress()->y - 30<= _objectManager->get_puzzleManager()->getFireTempleEntrance()->getPuzzle()->y  && IntersectRect(&temp2, &_objectManager->get_puzzleManager()->getFireTempleEntrance()->getRect(), &_playerManager->get_player()->get_playerRect()))
	{
		_objectManager->get_puzzleManager()->getFireTempleEntrance()->setAlpha(150);
	}
	else _objectManager->get_puzzleManager()->getFireTempleEntrance()->setAlpha(0);
}

