#include "stdafx.h"
#include "enemyManager.h"
#include "playerManager.h"

enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	imageSetting();
	_player = new player;
	_player->init();
	//몬스터 init에서 해주면 안됨 

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		(*_viEnemy)->update();
	}

	if (KEYMANAGER->isOnceKeyDown('U'))
	{
		CreateEnemy(ENEMY::SLIME, 24, 19);
	}
}

void enemyManager::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		(*_viEnemy)->render();
	}


}

void enemyManager::imageSetting()
{
	IMAGEMANAGER->addFrameImage("slime", "./image/enemy/slime.bmp", 240, 90, 5, 2, true, RGB(255, 0, 255));

	int IdleLeft[] = {0, 1};
	KEYANIMANAGER->addArrayFrameAnimation("slimeIdleLeft", "slime", IdleLeft, 2, 1, true);
	int IdleRight[] = { 8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("slimeIdleRight", "slime", IdleRight, 2, 1, true);

	int JumpLeft[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("slimeJumpLeft", "slime", JumpLeft, 1, 5, true);
	int JumpRight[] = { 7 };
	KEYANIMANAGER->addArrayFrameAnimation("slimeJumpRight", "slime", JumpRight, 1, 5, true);

	int AttackLeft[] = { 3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("slimeAttackLeft", "slime", AttackLeft, 2, 2, true);
	int AttackRight[] = { 5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("slimeAttackRight", "slime", AttackRight, 2, 2, true);


	//BOAR

	IMAGEMANAGER->addFrameImage("boarIdle", "./image/enemy/boarIdle.bmp", 405, 63, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boarWalk", "./image/enemy/boarWalk.bmp", 567, 63, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boarCharge", "./image/enemy/boarCharge.bmp", 405, 69, 5, 1, true, RGB(255, 0, 255));

	KEYANIMANAGER->addDefaultFrameAnimation("boarIdle", "boarIdle", 10, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("boarWalk", "boarWalk", 10, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("boarCharge", "boarCharge", 10, false, true);

}

void enemyManager::CreateEnemy(ENEMY enemyType, float x, float y)
{
	enemy* temp;
	temp = new slime;
	temp->init(enemyType, "slime", x, y);
	temp->setAni("slimeIdleLeft");
	temp->Set_PlayerLink(_player->get_PlayerAddress());
	_vEnemy.push_back(temp);

}
