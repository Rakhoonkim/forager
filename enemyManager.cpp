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
		//CreateEnemy(ENEMY::SLIME, 24, 19);
		//CreateEnemy(ENEMY::BOAR, 24, 20);
		CreateEnemy(ENEMY::DEMON, 24, 21);
		CreateEnemy(ENEMY::SKULL, 24, 21);
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

	IMAGEMANAGER->addFrameImage("boarIdle", "./image/enemy/boarIdle.bmp", 405, 126, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boarWalk", "./image/enemy/boarWalk.bmp", 567, 126, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boarCharge", "./image/enemy/boarCharge.bmp", 405, 138, 5, 2, true, RGB(255, 0, 255));
	
	KEYANIMANAGER->addCoordinateFrameAnimation("boarIdleRight", "boarIdle", 0, 5, 5, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("boarIdleLeft", "boarIdle", 6, 10, 5, false, true);
	
	KEYANIMANAGER->addCoordinateFrameAnimation("boarWalkRight", "boarWalk", 0, 7, 5, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("boarWalkLeft", "boarWalk", 8, 14, 5, false, true);

	KEYANIMANAGER->addCoordinateFrameAnimation("boarChargeRight", "boarCharge", 0, 5, 5, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("boarChargeLeft", "boarCharge", 6, 10, 5, false, true);


	// demon
	IMAGEMANAGER->addFrameImage("demonWalk", "./image/enemy/demonWalk.bmp", 378, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("demonAttack", "./image/enemy/demonAttack.bmp", 759, 132, 11, 2, true, RGB(255, 0, 255));

	int demonIdleRight[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("demonIdleRight", "demonWalk", demonIdleRight, 1, 10, true);
	int demonIdleLeft[] = { 11 };
	KEYANIMANAGER->addArrayFrameAnimation("demonIdleLeft", "demonWalk", demonIdleLeft, 1, 10, true);

	KEYANIMANAGER->addCoordinateFrameAnimation("demonWalkRight", "demonWalk", 0, 5, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("demonWalkLeft", "demonWalk", 6, 11, 10, false, true);

	KEYANIMANAGER->addCoordinateFrameAnimation("demonAttackRight", "demonAttack", 0, 10, 10, false,true);
	KEYANIMANAGER->addCoordinateFrameAnimation("demonAttackLeft", "demonAttack", 11, 21, 10, false, true);


	// skull
	IMAGEMANAGER->addFrameImage("skull", "./image/enemy/skull.bmp", 375, 234, 5, 2, true, RGB(255, 0, 255));
	KEYANIMANAGER->addCoordinateFrameAnimation("skullRight", "skull", 0, 4, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("skullLeft", "skull",5, 9, 8, false, true);

	//bullet

	IMAGEMANAGER->addFrameImage("fireBall", "./image/enemy/fireBall.bmp", 195, 39, 5, 1, true, RGB(255, 0, 255));
	KEYANIMANAGER->addDefaultFrameAnimation("fireBall", "fireBall", 10, false, true);
	IMAGEMANAGER->addFrameImage("effectFireBall", "./image/enemy/effectFireBall.bmp", 2760, 176, 15, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("fireBall", "effectFireBall", 2760, 176, 184, 176, 1, 0.35f, 10);
}

void enemyManager::CreateEnemy(ENEMY enemyType, float x, float y)
{
	if (enemyType == ENEMY::SLIME)
	{
		enemy* temp;
		temp = new slime;
		temp->init(enemyType, "slime", x, y);
		temp->setAni("slimeIdleLeft");
		temp->Set_PlayerLink(_player->get_PlayerAddress());
		_vEnemy.push_back(temp);
	}
	else if (enemyType == ENEMY::BOAR)
	{
		enemy* temp;
		temp = new boar;
		temp->init(enemyType, "boarIdle", x, y);
		temp->setAni("boarIdleLeft");
		temp->Set_PlayerLink(_player->get_PlayerAddress());
		_vEnemy.push_back(temp);
	}
	else if (enemyType == ENEMY::DEMON)
	{
		enemy* temp;
		temp = new demon;
		temp->init(enemyType, "demonWalk", x, y);
		temp->setAni("demonIdleLeft");
		temp->Set_PlayerLink(_player->get_PlayerAddress());
		_vEnemy.push_back(temp);
	}
	else if (enemyType == ENEMY::SKULL)
	{
		enemy* temp;
		temp = new skull;
		temp->init(enemyType, "skull", x, y);
		temp->setAni("skullLeft");
		temp->Set_PlayerLink(_player->get_PlayerAddress());
		_vEnemy.push_back(temp);
	}

}
