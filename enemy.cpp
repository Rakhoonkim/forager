#include "stdafx.h"
#include "enemy.h"
#include "enemyState.h"


enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init(ENEMY enemy,const char* imageName,int idx,int idy)
{
	_enemy.imageName = imageName;

	_enemy.building = BUILDING::NONE;
	_enemy.object = OBJECT::NONE;
	_enemy.tree = TREE::NONE;
	_enemy.enemy = enemy;
	
	_enemy.direc = DIRECTION::LEFT;
	// INDEX
	_enemy.idx = idx;
	_enemy.idy = idy;

	_enemy.frameX = 0;
	_enemy.frameY = 0;

	_enemy.isClick = false;

	_enemy.angle = 0;
	_enemy.x = idx * 60;
	_enemy.y = idy * 60;
	_enemy.centerX = _enemy.x + 30;
	_enemy.centerY = _enemy.y + 30;

	//새로 세팅해야 하는 값		
	_enemy.maxHp = 0;			// 최대 HP
	_enemy.hp = 0;				// HP
	_enemy.damage = 0;			// 데미지

	_StateAttack = false;
	_StateTurn = false;

	//상태정의
	_enemyState = new enemyState();
	_enemyState->init(&_enemy);

	_enemyIdle = new enemyIdle(&_enemy);

	_enemyMove = new enemyMove(&_enemy);

	_enemyAttack = new enemyAttack(&_enemy);

	_enemyState = _enemyIdle;
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	_enemyState->update();
}

void enemy::render()
{
	//IMAGEMANAGER->findImage(_enemy.imageName)->aniRender(CAMERAMANAGER->getWorldDC(), _enemy.x, _enemy.y, _enemy.ani);
	_enemyState->render();
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■ slime ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

slime::slime()
{
}

slime::~slime()
{
}
