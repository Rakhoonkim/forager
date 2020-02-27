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

	_bulletManager = new bulletManager;
	_bulletManager->init();

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	for (int i = 0;i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->update();
		if (_vEnemy[i]->getEnemy()->enemy != ENEMY::DEMON_BOSS)
		{
			if (_vEnemy[i]->getEnemy()->isPlayerAttack)
			{
				RECT temp;
				if (IntersectRect(&temp, &_vEnemy[i]->getEnemy()->rc, &_player->get_PlayerAddress()->rc))
				{
					_player->playerHit();
					_vEnemy[i]->getEnemy()->isPlayerAttack = false;
					break;
				}
			}
		}
	}
	//for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	//{
	//	(*_viEnemy)->update();
	//}

	if (KEYMANAGER->isOnceKeyDown('U'))
	{
		CreateEnemy(ENEMY::SLIME, 24, 19);
		CreateEnemy(ENEMY::BOAR, 24, 20);
		CreateEnemy(ENEMY::DEMON, 24, 21);
		CreateEnemy(ENEMY::SKULL, 24, 21);
		CreateEnemy(ENEMY::DEMON_BOSS, 24, 21);
	}
	

	_bulletManager->update();
	enemyRemove();
}

void enemyManager::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		(*_viEnemy)->render();
	}
	_bulletManager->render();
}

void enemyManager::imageSetting()
{
	IMAGEMANAGER->addFrameImage("slime", "./image/enemy/slime.bmp", 240, 90, 5, 2, true, RGB(255, 0, 255));

	int IdleLeft[] = {0, 1};
	KEYANIMANAGER->addArrayFrameAnimation("slimeIdleLeft", "slime", IdleLeft, 2, 1, true);
	int IdleRight[] = { 8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("slimeIdleRight", "slime", IdleRight, 2, 1, true);

	int JumpLeft[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("slimeJumpLeft", "slime", JumpLeft, 1, 10, true);
	int JumpRight[] = { 7 };
	KEYANIMANAGER->addArrayFrameAnimation("slimeJumpRight", "slime", JumpRight, 1, 10, true);

	int AttackLeft[] = { 3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("slimeAttackLeft", "slime", AttackLeft, 2, 5, true);
	int AttackRight[] = { 5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("slimeAttackRight", "slime", AttackRight, 2, 5, true);


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
	EFFECTMANAGER->addEffect("fireBall", "effectFireBall", 2760, 176, 184, 176, 1, 0.35f, 100);

	// boss
	IMAGEMANAGER->addFrameImage("bossWalk", "./image/enemy/damonBossWalk.bmp", 1728, 312, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossAttack", "./image/enemy/damonBossAttack.bmp", 1728, 360, 9, 2, true, RGB(255, 0, 255));

	int idleRight[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("bossIdleRight", "bossWalk", idleRight, 1, 10, true);
	int idleLeft[] = { 17 };
	KEYANIMANAGER->addArrayFrameAnimation("bossIdleLeft", "bossWalk", idleLeft, 1, 10, true);

	int walkRight[] = { 0,1,2,3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("bossWalkRight", "bossWalk", walkRight, 9, 5, true);
	int walkLeft[] = { 17,16,15,14,13,12,11,10,9 };
	KEYANIMANAGER->addArrayFrameAnimation("bossWalkLeft", "bossWalk", walkLeft, 9, 5, true);

	//공격
	KEYANIMANAGER->addCoordinateFrameAnimation("bossAttackRight", "bossAttack", 0, 8, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("bossAttackLeft", "bossAttack", 9, 17, 10, false, true);

}

void enemyManager::enemyRemove()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		if ((*_viEnemy)->getEnemy()->hp <= 0)
		{
			// Enemey 삭제  
			ITEMMANAGER->DropEnemyItem((*_viEnemy)->getEnemy()->enemy, (*_viEnemy)->getEnemy()->centerX, (*_viEnemy)->getEnemy()->centerY);
			_vEnemy.erase(_viEnemy);
			break;
		}
	}
}

void enemyManager::CreateEnemy(ENEMY enemyType, int idx, int idy)
{
	if (enemyType == ENEMY::SLIME)
	{
		enemy* temp;
		temp = new slime;
		temp->init(enemyType, "slime", idx, idy);
		temp->setAni("slimeIdleLeft");
		temp->setHp(5, 5);
		temp->Set_PlayerLink(_player->get_PlayerAddress());
		_vEnemy.push_back(temp);
	}
	else if (enemyType == ENEMY::BOAR)
	{
		enemy* temp;
		temp = new boar;
		temp->init(enemyType, "boarIdle", idx, idy);
		temp->setAni("boarIdleLeft");
		temp->Set_PlayerLink(_player->get_PlayerAddress());
		_vEnemy.push_back(temp);
	}
	else if (enemyType == ENEMY::DEMON)
	{
		enemy* temp;
		temp = new demon;
		temp->init(enemyType, "demonWalk", idx, idy);
		temp->setAni("demonIdleLeft");
		temp->Set_PlayerLink(_player->get_PlayerAddress());
		_vEnemy.push_back(temp);
	}
	else if (enemyType == ENEMY::SKULL)
	{
		enemy* temp;
		temp = new skull;
		temp->init(enemyType, "skull", idx, idy);
		temp->setAni("skullLeft");
		temp->set_skullEnemyXY();
		temp->Set_PlayerLink(_player->get_PlayerAddress());
		temp->setEnemyBullet(_bulletManager);
		_vEnemy.push_back(temp);
	}
	else if (enemyType == ENEMY::DEMON_BOSS)
	{
		enemy* temp;
		temp = new demonBoss;
		temp->init(enemyType, "bossWalk", idx, idy);
		temp->setAni("bossIdleLeft");
		temp->Set_PlayerLink(_player->get_PlayerAddress());
		_vEnemy.push_back(temp);
	}

}

void enemyManager::BossAttack()
{
	for (int i = 0;i < _vEnemy.size(); i++)
	{
	
		if (_vEnemy[i]->getEnemy()->enemy == ENEMY::DEMON_BOSS)
		{
			if (_vEnemy[i]->getBossAttack())
			{
				this->CreateEnemy(ENEMY::SKULL, _vEnemy[i]->getEnemy()->idx + 1, _vEnemy[i]->getEnemy()->idy);
				this->CreateEnemy(ENEMY::SKULL, _vEnemy[i]->getEnemy()->idx + 1, _vEnemy[i]->getEnemy()->idy);
				this->CreateEnemy(ENEMY::SKULL, _vEnemy[i]->getEnemy()->idx + 1, _vEnemy[i]->getEnemy()->idy);
				_vEnemy[i]->SetBossAttack(false);
			}
		}
	}
}
