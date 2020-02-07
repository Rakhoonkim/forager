#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init()
{
	imageSetting();
	_player = new player();
	_player->init();
	return S_OK;
}

void playerManager::release()
{
	_player->release();
}

void playerManager::update()
{
	_player->update();
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

	//°î±ªÀÌ
	IMAGEMANAGER->addFrameImage("playerPick","./image/player/playerPickaxe.bmp", 532, 106, 7, 2, true, RGB(255, 0, 255));

	KEYANIMANAGER->addCoordinateFrameAnimation("playerPick_R", "playerPick", 0, 7, 20, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("playerPick_L", "playerPick", 7, 14, 20, false, false);

}

