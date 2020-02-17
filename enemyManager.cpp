#include "stdafx.h"
#include "enemyManager.h"

enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	imageSetting();

	_enemy = new enemy;
	_enemy->init(ENEMY::SLIME,"slime",25,19);
	_enemy->setAni("slimeIdleLeft");
	
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
}

void enemyManager::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		(*_viEnemy)->render();
	}
	_enemy->render();
}

void enemyManager::imageSetting()
{
	IMAGEMANAGER->addFrameImage("slime", "./image/enemy/slime.bmp", 240, 90, 5, 2, true, RGB(255, 0, 255));

	int IdleLeft[] = {0, 1};
	KEYANIMANAGER->addArrayFrameAnimation("slimeIdleLeft", "slime", IdleLeft, 2, 10, true);
	int IdleRight[] = { 8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("slimeIdleRight", "slime", IdleRight, 2, 10, true);

	int JumpLeft[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("slimeJumpLeft", "slime", JumpLeft, 2, 10, true);
	int JumpRight[] = { 7 };
	KEYANIMANAGER->addArrayFrameAnimation("slimeJumpRight", "slime", JumpRight, 2, 10, true);

	int AttackLeft[] = { 3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("slimeAttackLeft", "slime", AttackLeft, 2, 10, true);
	int AttackRight[] = { 5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("slimeAttackLeft", "slime", AttackRight, 2, 10, true);

}
