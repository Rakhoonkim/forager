#include "stdafx.h"
#include "playerManager.h"
#include "cropsManager.h"
#include "buildManager.h"

HRESULT playerManager::init()
{
	imageSetting();
	_player = new player();
	_player->init();

	_cropsManager = new cropsManager;
	_cropsManager->init();

	_buildManager = new buildManager;
	_buildManager->init();

	//�ɼ�
	_isOption = false;
	return S_OK;
}

void playerManager::release()
{
	_player->release();
}

void playerManager::update()
{

	_player->update();
	objectCollisionMouse();   // ���콺 �����͸� �����ֱ� ���� 
	itemCollisionPlayer();    // �������� �Ա� ����.
	itemCollisionMouse();	  // �������� �Ա� ����.
	optionControl();		  //�ɼ�â ��Ʈ�� 
}

void playerManager::render()
{
	if(!_buildManager->usedCheck()) _player->render();
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
}

void playerManager::itemCollisionPlayer()
{
	for (int i = 0; i < ITEMMANAGER->getVItem().size(); i++)
	{
		if (!ITEMMANAGER->getVItem()[i]->getItem()->drop) continue;
		RECT temp;
		//�������̶� ���̶� �浹 
		if ((IntersectRect(&temp, &ITEMMANAGER->getVItem()[i]->getItem()->rc, &_player->get_playerRect())))
		{
			ITEMMANAGER->getVItem()[i]->setGain();
			break;
		}

	}

}

void playerManager::itemCollisionMouse()
{
	// ������ �浹 
	for (int i = 0; i < ITEMMANAGER->getVItem().size(); i++)
	{
		if (!ITEMMANAGER->getVItem()[i]->getItem()->drop) continue;
		// ���콺�� ������ �浹 
		if ((PtInRect(&ITEMMANAGER->getVItem()[i]->getItem()->rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y))))
		{
			ITEMMANAGER->getVItem()[i]->setGain(_player->get_PlayerAddress()->x, _player->get_PlayerAddress()->y);
			break;
		}
	}
}

void playerManager::objectCollisionMouse()
{
	//����������������������� CropsCollision �����������������������
	for (int i = 0; i < _cropsManager->getVCrops().size(); ++i)
	{
		if (_cropsManager->getVCrops()[i]->getCrops()->isClick && PtInRect(&_cropsManager->getVCrops()[i]->getCrops()->rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			//Ŀ�� �Ŵ��� 
			CURSORMANAGER->setCropsPoint();
			CURSORMANAGER->getCursor()->setCursorXY(_cropsManager->getVCrops()[i]->getCrops()->centerX - CAMERAMANAGER->getWorldCamera().cameraX, _cropsManager->getVCrops()[i]->getCrops()->centerY - CAMERAMANAGER->getWorldCamera().cameraY);


			objectAttack(i);
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
				_buildManager->getVBuild()[i]->getBuilding()->isClick = true;
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

				cout << "�浹 x: " << _ptMouse.x << " y :" << _ptMouse.y << endl;
				return;
			}
			else
			{
				_buildManager->getVBuild()[i]->getBuilding()->isClick = false;
			}
		}
		else
		{
			_buildManager->getVBuild()[i]->getBuilding()->isClick = false;
			_buildManager->getVBuild()[i]->setUsed();
		}
	}

	CURSORMANAGER->setCursor();
	CURSORMANAGER->getCursor()->setCursorChange();

}

void playerManager::optionControl()
{
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
			_cropsManager->getVCrops()[num]->cropsHit(_player->get_PlayerAddress()->damage);
		}
		//KEYMANAGER->setKeyDown(VK_LBUTTON, false);
	}
}

