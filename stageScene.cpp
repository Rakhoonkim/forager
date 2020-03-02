#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{
	//�÷��̾� 
	_playerManager = new playerManager;
	_playerManager->init();
	//������Ʈ 
	_objectManager = new objectManager;
	_objectManager->init();
	//����
	_weather = new weather;
	_weather->init();

	//�ּҰ� ����

	//�÷��̾�->������Ʈ
	_playerManager->set_CropsManager(_objectManager->get_CropsManager());
	_playerManager->set_BuildManager(_objectManager->get_buildManager());
	_playerManager->set_EnemyManager(_objectManager->get_enemyManager());
	_playerManager->set_puzzleManager(_objectManager->get_puzzleManager());
	//������Ʈ->�÷��̾�
	_objectManager->get_enemyManager()->setPlayer(_playerManager->get_player()); 
	_objectManager->get_CropsManager()->setPlayer(_playerManager->get_player());

	//�� �����ؾ��� 
	MAPMANAGER->release();
	MAPMANAGER->setObjectManager(_objectManager);
	MAPMANAGER->MapLoad("inGameNumber2.map");

	UIMANAGER->getEquipment()->setSkillPount(&_playerManager->get_player()->get_PlayerAddress()->skillPount);
	
	//���� ������ ����
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
	//_weather->update();  // ����
	ZORDER->update();				 //ZORDER
	templeEntranceMouseCollision();  //�����Ա� 
	setAlphaImage();				 //���ĺ��� ó��
}

void stageScene::render()
{
	//PatBlt(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY, WINSIZEX, WINSIZEY,WHITENESS);
	IMAGEMANAGER->findImage("background")->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY);
	MAPMANAGER->stageRender();									  //MAP

	EFFECTMANAGER->EffectRender(CAMERAMANAGER->getWorldDC());	  //������Ʈ �ؿ� ������ ����Ʈ

	//������Ʈ ����ų�� 
	if (CURSORMANAGER->getCursor()->getObjectPoint()) CURSORMANAGER->render(); 
	
	ZORDER->render();			 //ZORDER
	//_playerManager->render();  //PLAYER 

	ITEMMANAGER->render();		 //ITEM

	EFFECTMANAGER->render(CAMERAMANAGER->getWorldDC());  // EFFECT

	_objectManager->render();	 //OBJECT���� ������ �׸��� ���� 

	if (!UIMANAGER->getLand()->getLand()) CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->getWorldCamera().cameraX, CAMERAMANAGER->getWorldCamera().cameraY, WINSIZEX, WINSIZEY);

	//_weather->render(getMemDC());

	UIMANAGER->render();		// UI
}

//���� �Ա� 
void stageScene::templeEntranceMouseCollision()
{
	//���� �Ա��� �Ÿ��� ������
	if (180 >= getDistance(_objectManager->get_puzzleManager()->getFireTempleEntrance()->getPuzzle()->x, _objectManager->get_puzzleManager()->getFireTempleEntrance()->getPuzzle()->y, _playerManager->get_player()->get_PlayerAddress()->x, _playerManager->get_player()->get_PlayerAddress()->y))
	{
		if (PtInRect(&_objectManager->get_puzzleManager()->getFireTempleEntrance()->getPuzzle()->rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			 _objectManager->get_puzzleManager()->getFireTempleEntrance()->getPuzzle()->isClick = true;
		}
		else _objectManager->get_puzzleManager()->getFireTempleEntrance()->getPuzzle()->isClick = false;
	}
	else _objectManager->get_puzzleManager()->getFireTempleEntrance()->getPuzzle()->isClick = false;
}

//�������� �� ����� (��������)
void stageScene::enterStageScene()
{
	_playerManager = GAMEDATA->getPlayerManager();
	_objectManager = GAMEDATA->getObjectManager();
	_objectManager->get_enemyManager()->AutoEnemySet(true);
	//_playerManager->set_CropsManager(_objectManager->get_CropsManager());
	//_playerManager->set_BuildManager(_objectManager->get_buildManager());
	//_playerManager->set_EnemyManager(_objectManager->get_enemyManager());
	//_playerManager->set_puzzleManager(_objectManager->get_puzzleManager());
	//_objectManager->get_enemyManager()->setPlayer(_playerManager->get_player());  // �÷��̾� ��ũ 
	//_objectManager->get_CropsManager()->setPlayer(_playerManager->get_player());
	MAPMANAGER->setObjectManager(_objectManager);
	UIMANAGER->getEquipment()->setSkillPount(&_playerManager->get_player()->get_PlayerAddress()->skillPount);
	UIMANAGER->playerAdressLink(_playerManager->get_player()->get_PlayerAddress());
	_playerManager->get_player()->setPlayerXY(36, 29);
}

void stageScene::setAlphaImage()
{
	//����̵� Ʈ�� ���ĺ��� ó��
	RECT temp;
	if (_playerManager->get_player()->get_PlayerAddress()->y - 30 <= _objectManager->get_puzzleManager()->getDruidTree()->getPuzzle()->y  && IntersectRect(&temp, &_objectManager->get_puzzleManager()->getDruidTree()->getRect(), &_playerManager->get_player()->get_playerRect()))
	{
		_objectManager->get_puzzleManager()->getDruidTree()->setAlpha(150);
	}
	else _objectManager->get_puzzleManager()->getDruidTree()->setAlpha(0);

	//���� �Ա� ���ĺ��� ó��
	RECT temp2;
	if (_playerManager->get_player()->get_PlayerAddress()->y - 30<= _objectManager->get_puzzleManager()->getFireTempleEntrance()->getPuzzle()->y  && IntersectRect(&temp2, &_objectManager->get_puzzleManager()->getFireTempleEntrance()->getRect(), &_playerManager->get_player()->get_playerRect()))
	{
		_objectManager->get_puzzleManager()->getFireTempleEntrance()->setAlpha(150);
	}
	else _objectManager->get_puzzleManager()->getFireTempleEntrance()->setAlpha(0);
}

