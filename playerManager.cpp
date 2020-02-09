#include "stdafx.h"
#include "playerManager.h"
#include "cropsManager.h"

HRESULT playerManager::init()
{
	imageSetting();
	_player = new player();
	_player->init();

	_cropsManager = new cropsManager;
	_cropsManager->init();
	return S_OK;
}

void playerManager::release()
{
	_player->release();
}

void playerManager::update()
{
	_player->update();
	objectCollisionMouse();   // 마우스 포인터를 보여주기 위한 
}

void playerManager::render()
{
	_player->render();
}

void playerManager::imageSetting()
{
	IMAGEMANAGER->addFrameImage("playerIdle", "./image/player/playerIdle.bmp", 198, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerWalk", "./image/player/playerWalk.bmp", 198, 108, 6, 2, true, RGB(255, 0, 255));

	KEYANIMANAGER->addCoordinateFrameAnimation("playerIdle_R", "playerIdle", 0, 5, 15, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("playerIdle_L", "playerIdle", 6, 11, 15, false, true);

	KEYANIMANAGER->addCoordinateFrameAnimation("playerWalk_R", "playerWalk", 0, 5, 15, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("playerWalk_L", "playerWalk", 6, 11, 15, false, true);

	//곡괭이
	IMAGEMANAGER->addFrameImage("playerPick","./image/player/playerPickaxe.bmp", 532, 106, 7, 2, true, RGB(255, 0, 255));

	KEYANIMANAGER->addCoordinateFrameAnimation("playerPick_R", "playerPick", 0, 7, 20, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("playerPick_L", "playerPick", 7, 14, 20, false, false);

}

void playerManager::objectCollisionMouse()
{
	//■■■■■■■■■■■■■■■■■■■■■■ CropsCollision ■■■■■■■■■■■■■■■■■■■■■■
	for (int i = 0; i < _cropsManager->getVCrops().size(); ++i)
	{
		if (PtInRect(&_cropsManager->getVCrops()[i]->getCrops()->rc, PointMake(CAMERAMANAGER->getWorldCamera().cameraX + _ptMouse.x, CAMERAMANAGER->getWorldCamera().cameraY + _ptMouse.y)))
		{
			//커서 매니져 
			CURSORMANAGER->setPoint();
			CURSORMANAGER->getCursor()->setCursorXY(_cropsManager->getVCrops()[i]->getCrops()->centerX - CAMERAMANAGER->getWorldCamera().cameraX, _cropsManager->getVCrops()[i]->getCrops()->centerY - CAMERAMANAGER->getWorldCamera().cameraY);
			cout << "충돌 x: " << _ptMouse.x << " y :" << _ptMouse.y << endl;

			objectAttack(i);
			// 1 . 케릭터 거리만큼 
			// 2 . 오브젝트 데미지 입히기 
		}
		else
		{
			CURSORMANAGER->setCursor();
			CURSORMANAGER->getCursor()->setCursorChange();
		}
	}
}

void playerManager::objectAttack(int num)
{
	//TYPE마다 데미지 입히기 추가할 예정 
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//거리가 좁혀지면 데미지를 입힌다.
		if (getDistance(_player->get_PlayerAddress()->x, _player->get_PlayerAddress()->y, _cropsManager->getVCrops()[num]->getCrops()->x, _cropsManager->getVCrops()[num]->getCrops()->y) <= 120)
		{
			_cropsManager->getVCrops()[num]->cropsHit(_player->get_PlayerAddress()->damage);
		}
		KEYMANAGER->setKeyDown(VK_LBUTTON, false);
	}
}

