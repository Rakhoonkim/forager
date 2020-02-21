#include "stdafx.h"
#include "playerManager.h"
#include "cropsManager.h"
#include "buildManager.h"
#include "enemyManager.h"

HRESULT playerManager::init()
{
	imageSetting();
	_player = new player();
	_player->init();

	_cropsManager = new cropsManager;		//CROPS
	_cropsManager->init();

	_buildManager = new buildManager;		//BUILD
	_buildManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init();

	//�ɼ�
	_isOption = false;

	//UI ����
	UIMANAGER->playerAdressLink(_player->get_PlayerAddress()); // ����ü ����
	UIMANAGER->getInven()->setPlayer(_player->get_PlayerAddress());

	_alphaEffect = new alphaEffect;
	_alphaEffect->init();
	
	return S_OK;
}

void playerManager::release()
{
	_player->release();
	_alphaEffect->release();			// ���� �����
}

void playerManager::update()
{

	_player->update();
	if(!UIMANAGER->getOption()) objectCollisionMouse();   // ���콺 �����͸� �����ֱ� ���� 
	itemCollisionPlayer();    // �������� �Ա� ����.
	itemCollisionMouse();	  // �������� �Ա� ����.
	optionControl();		  // �ɼ�â ��Ʈ�� 
	_alphaEffect->update();	  // UI ����ġ 
	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		cout << "���ǳ�?" << endl;
		_alphaEffect->play("expNum",15,_player->get_PlayerAddress()->x - 15, _player->get_PlayerAddress()->y - 15);
	}
}

void playerManager::render()
{
	// �ǹ�������̸� ���带 ����
	if(!_buildManager->usedCheck()) _player->render();  
	_alphaEffect->render();
}

void playerManager::imageSetting()
{
	IMAGEMANAGER->addFrameImage("playerIdle", "./image/player/playerIdle.bmp", 198, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerWalk", "./image/player/playerWalk.bmp", 198, 108, 6, 2, true, RGB(255, 0, 255));

	KEYANIMANAGER->addCoordinateFrameAnimation("playerIdle_R", "playerIdle", 0, 5, 15, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("playerIdle_L", "playerIdle", 6, 11, 15, false, true);

	KEYANIMANAGER->addCoordinateFrameAnimation("playerWalk_R", "playerWalk", 0, 5, 15, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("playerWalk_L", "playerWalk", 6, 11, 15, false, true);

	//���
	IMAGEMANAGER->addFrameImage("playerPick", "./image/player/playerPickaxe.bmp", 532, 106, 7, 2, true, RGB(255, 0, 255));

	KEYANIMANAGER->addCoordinateFrameAnimation("playerPick_R", "playerPick", 0, 7, 20, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("playerPick_L", "playerPick", 7, 14, 20, false, false);

	// image
	IMAGEMANAGER->addFrameImage("shadow", "./image/player/shadow.bmp", 80, 16, 5, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("shadow", "shadow", 80, 16, 16, 16, 1, 0.3f, 20);

}

//������ �浹
void playerManager::itemCollisionPlayer()
{
	for (int i = 0; i < ITEMMANAGER->getVItem().size(); i++)
	{
		//�ѹ��� Ȯ���ϱ� ���� BOOL�� Ȯ��
		if (!ITEMMANAGER->getVItem()[i]->getItem()->drop) continue;
		RECT temp;
		//�������̶� ���̶� �浹 
		if ((IntersectRect(&temp, &ITEMMANAGER->getVItem()[i]->getItem()->rc, &_player->get_PlayerAddress()->rc)))
		{
			ITEMMANAGER->getVItem()[i]->setGain();
			break;
		}
	}
}
// ������ �浹 
void playerManager::itemCollisionMouse()
{
	for (int i = 0; i < ITEMMANAGER->getVItem().size(); i++)
	{
		//�ѹ��� Ȯ���ϱ� ���� BOOL�� Ȯ��
		if (!ITEMMANAGER->getVItem()[i]->getItem()->drop) continue;
		// ���콺�� ������ �浹 
		if ((PtInRect(&ITEMMANAGER->getVItem()[i]->getItem()->rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y))))
		{
			ITEMMANAGER->getVItem()[i]->setGain(_player->get_PlayerAddress()->x, _player->get_PlayerAddress()->y);
			break;
		}
	}
}
//������Ʈ�� ���콺 �浹
void playerManager::objectCollisionMouse()
{
	//����������������������� CropsCollision �����������������������
	for (int i = 0; i < _cropsManager->getVCrops().size(); ++i)
	{
		if (_cropsManager->getVCrops()[i]->getCrops()->isClick && PtInRect(&_cropsManager->getVCrops()[i]->getCrops()->rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			//Ŀ�� �Ŵ��� ����
			CURSORMANAGER->setCropsPoint();
			CURSORMANAGER->getCursor()->setCursorXY(_cropsManager->getVCrops()[i]->getCrops()->centerX - CAMERAMANAGER->getWorldCamera().cameraX, _cropsManager->getVCrops()[i]->getCrops()->centerY - CAMERAMANAGER->getWorldCamera().cameraY);

			if(_player->get_PlayerAddress()->health > 0) objectAttack(i);
			return;
		}
	}

	//����������������������� buildAttackCollision �����������������������
	for (int i = 0; i < _buildManager->getVBuild().size(); ++i)
	{
		if (180 >= getDistance(_buildManager->getVBuild()[i]->getBuilding()->centerX, _buildManager->getVBuild()[i]->getBuilding()->centerY, _player->get_PlayerAddress()->x, _player->get_PlayerAddress()->y))
		{
			// �ǹ� USED â ����� �ʰ� and ���콺�� �浹 ���� 
			if (!_buildManager->getVBuild()[i]->getUsed() && PtInRect(&_buildManager->getVBuild()[i]->getBuilding()->rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
			{
				//Ŭ�� ������ ����
				_buildManager->getVBuild()[i]->getBuilding()->isClick = true;
				// �ǹ����� ���콺 Ŀ���� �޶� ������ �� 
				if (_buildManager->getVBuild()[i]->getBuilding()->building == BUILDING::BRIDGE || _buildManager->getVBuild()[i]->getBuilding()->building == BUILDING::FISHTRAP)
				{
					CURSORMANAGER->setBridgePoint();
					CURSORMANAGER->getCursor()->setCursorXY(_buildManager->getVBuild()[i]->getBuilding()->x - CAMERAMANAGER->getWorldCamera().cameraX, _buildManager->getVBuild()[i]->getBuilding()->y - CAMERAMANAGER->getWorldCamera().cameraY - 15);
				}
				else if (_buildManager->getVBuild()[i]->getBuilding()->building == BUILDING::FURNACE || _buildManager->getVBuild()[i]->getBuilding()->building == BUILDING::FORGE || _buildManager->getVBuild()[i]->getBuilding()->building == BUILDING::SEWING_STATION)
				{
					CURSORMANAGER->setBuildPoint();
					CURSORMANAGER->getCursor()->setCursorXY(_buildManager->getVBuild()[i]->getBuilding()->centerX - CAMERAMANAGER->getWorldCamera().cameraX, _buildManager->getVBuild()[i]->getBuilding()->centerY - CAMERAMANAGER->getWorldCamera().cameraY);
				}
				return;
			}
			else
			{
				_buildManager->getVBuild()[i]->getBuilding()->isClick = false;
			}
		}
		else
		{
			//BOOL�� �ʱ�ȭ
			_buildManager->getVBuild()[i]->getBuilding()->isClick = false;
			_buildManager->getVBuild()[i]->setUsed();
		}
	}
	
	//����������������������� EnemyCollision �����������������������
	for (int i = 0; i < _enemyManager->getVEnemy().size(); ++i)
	{
		if (PtInRect(&_enemyManager->getVEnemy()[i]->getEnemy()->rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			if (_enemyManager->getVEnemy()[i]->getEnemy()->enemy == ENEMY::SLIME)
			{
				CURSORMANAGER->setCropsPoint();
				CURSORMANAGER->getCursor()->setCursorXY(_enemyManager->getVEnemy()[i]->getEnemy()->centerX - CAMERAMANAGER->getWorldCamera().cameraX, _enemyManager->getVEnemy()[i]->getEnemy()->centerY - CAMERAMANAGER->getWorldCamera().cameraY);
			}
			else if(_enemyManager->getVEnemy()[i]->getEnemy()->enemy == ENEMY::DEMON ||
				_enemyManager->getVEnemy()[i]->getEnemy()->enemy == ENEMY::BOAR)
			{
				CURSORMANAGER->setBridgePoint();
				CURSORMANAGER->getCursor()->setCursorXY(_enemyManager->getVEnemy()[i]->getEnemy()->centerX - CAMERAMANAGER->getWorldCamera().cameraX, _enemyManager->getVEnemy()[i]->getEnemy()->centerY - CAMERAMANAGER->getWorldCamera().cameraY);
			}
			else if (_enemyManager->getVEnemy()[i]->getEnemy()->enemy == ENEMY::SKULL)
			{
				CURSORMANAGER->setBridgePoint();
				CURSORMANAGER->getCursor()->setCursorXY(_enemyManager->getVEnemy()[i]->getEnemy()->centerX - CAMERAMANAGER->getWorldCamera().cameraX, _enemyManager->getVEnemy()[i]->getEnemy()->centerY - CAMERAMANAGER->getWorldCamera().cameraY + 25);
			}
			else if (_enemyManager->getVEnemy()[i]->getEnemy()->enemy == ENEMY::DEMON_BOSS)
			{
				CURSORMANAGER->setBossPoint();
				CURSORMANAGER->getCursor()->setCursorXY(_enemyManager->getVEnemy()[i]->getEnemy()->centerX - CAMERAMANAGER->getWorldCamera().cameraX, _enemyManager->getVEnemy()[i]->getEnemy()->centerY - CAMERAMANAGER->getWorldCamera().cameraY + 25);

			}
			if (_player->get_PlayerAddress()->health > 0) enemyAttack(i);
			return;
		}
	}
	CURSORMANAGER->setCursor();
	CURSORMANAGER->getCursor()->setCursorChange();
}

//�ɼ�â ����� 
void playerManager::optionControl()
{
	//�ɼ�â ��Ʈ��
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE) && !UIMANAGER->getBuild()->getisBuilding() && !_buildManager->usedCheck())
	{
		UIMANAGER->setOption();
	}
}

void playerManager::objectAttack(int num)
{
	//TYPE���� ������ ������ �߰��� ���� 
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//�Ÿ��� �������� �������� ������.
		if (getDistance(_player->get_PlayerAddress()->x, _player->get_PlayerAddress()->y, _cropsManager->getVCrops()[num]->getCrops()->centerX, _cropsManager->getVCrops()[num]->getCrops()->centerY) <= 120)
		{
			_player->playerHealth(3);
			_cropsManager->getVCrops()[num]->setCropsEffect(true);
			_cropsManager->getVCrops()[num]->setCropsIsHit(true);
			_cropsManager->getVCrops()[num]->cropsHit(_player->get_PlayerAddress()->damage);
		}
		//KEYMANAGER->setKeyDown(VK_LBUTTON, false);
	}
}

void playerManager::enemyAttack(int num)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//�Ÿ��� �������� �������� ������.
		if (getDistance(_player->get_PlayerAddress()->x, _player->get_PlayerAddress()->y, _enemyManager->getVEnemy()[num]->getEnemy()->centerX, _enemyManager->getVEnemy()[num]->getEnemy()->centerY) <= 80)
		{
			_enemyManager->getVEnemy()[num]->enemyHit(_player->get_PlayerAddress()->damage);
		}
		//KEYMANAGER->setKeyDown(VK_LBUTTON, false);
	}
}

