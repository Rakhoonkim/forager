#include "stdafx.h"
#include "enemy.h"
#include "enemyState.h"
#include "player.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init(ENEMY enemy,const char* imageName,int idx,int idy)
{
	_player = new tagPlayer;
	
	_enemy.imageName = imageName;

	_enemy.building = BUILDING::NONE;
	_enemy.object = OBJECT::NONE;
	_enemy.tree = TREE::NONE;
	_enemy.enemy = enemy;
	
	_enemy.imageDirection = DIRECTION::LEFT;
	_previousDirection = _enemy.imageDirection;
	// INDEX
	_enemy.idx = idx;
	_enemy.idy = idy;

	_enemy.dstX = 0;
	_enemy.dstY = 0;

	_enemy.frameX = 0;
	_enemy.frameY = 0;

	_enemy.isClick = false;

	_enemy.acel = 1.0f;
	_enemy.angle = 0;
	_enemy.x = idx * 60;
	_enemy.y = idy * 60;

	_enemy.width = IMAGEMANAGER->findImage(_enemy.imageName)->getFrameWidth();
	_enemy.height = IMAGEMANAGER->findImage(_enemy.imageName)->getFrameHeight();

	_enemy.centerX = _enemy.x + 30;
	_enemy.centerY = _enemy.y + 30;

	_enemy.isEffect = false;
	_enemy.AttackTerm = false;
	_enemy.isJump = false;
	_enemy.isAttack = false;
	//새로 세팅해야 하는 값		
	_enemy.maxHp = 3;			// 최대 HP
	_enemy.hp = 3;				// HP
	_enemy.damage = 0;			// 데미지

	_enemy.time = TIMEMANAGER->getWorldTime();
	
	_enemy.hpBar = 0;
	_enemy.isPlayerAttack = false;
	//상태정의
	_enemyState = new enemyStateManager;
	_enemyState->init();

	_enemyState->addState("IDLE", new enemyIdle(_enemyState , &_enemy));
	_enemyState->addState("MOVE", new enemyMove(_enemyState , &_enemy));
	_enemyState->addState("JUMP", new enemyJump(_enemyState , &_enemy));
	_enemyState->addState("ATTACK", new enemyAttack(_enemyState ,&_enemy));

	_enemyState->chanageState("IDLE");

	_enemy.rc = RectMake(_enemy.x, _enemy.y, IMAGEMANAGER->findImage(_enemy.imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_enemy.imageName)->getFrameHeight());
	
	_bulletManager = new bulletManager;
	_bulletManager->init();
	
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	_enemyState->update();
	IndexUpdate();
}

void enemy::render()
{
	_enemyState->render();
}

void enemy::IndexUpdate()
{
	_enemy.width = IMAGEMANAGER->findImage(_enemy.imageName)->getFrameWidth();
	_enemy.height = IMAGEMANAGER->findImage(_enemy.imageName)->getFrameHeight();

	//RECT idx, idy
	_enemy.rc = RectMake(_enemy.x, _enemy.y, IMAGEMANAGER->findImage(_enemy.imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_enemy.imageName)->getFrameHeight());
	_enemy.idx = _enemy.x / 60;
	_enemy.idy = _enemy.y / 60;
	_enemy.centerX = _enemy.x + (_enemy.width / 2);
	_enemy.centerY = _enemy.y + (_enemy.height / 2);

	//이미지방향값 정의
	cout << "enemy angle: " << _enemy.angle << endl;
	cout << "enemy Driection(2: left , 3 : right) : " << (int)_enemy.imageDirection << endl;
	if (_enemy.angle >= 0 && _enemy.angle <= 1.57)
	{
		_enemy.imageDirection = DIRECTION::RIGHT;
	}
	else if (_enemy.angle <= 3.14 && _enemy.angle > 1.57)
	{
		_enemy.imageDirection = DIRECTION::LEFT;
	}
	else if ((_enemy.angle <= 4.71 && _enemy.angle > 3.14) || (_enemy.angle > -3.14 && _enemy.angle <= -1.57))
	{
		_enemy.imageDirection = DIRECTION::LEFT;
	}
	else if(_enemy.angle <= 6.28 && _enemy.angle > 4.71 || (_enemy.angle < 0 && _enemy.angle >= -1.57) )
	{
		_enemy.imageDirection = DIRECTION::RIGHT;
	}

	//방향이 달라지면 이미지 변화를 호출한다.
	if (_previousDirection != _enemy.imageDirection)
	{
		_previousDirection = _enemy.imageDirection;
		_enemyState->getState()->ChangeImage();
	}
	//cout << "enemy idx : " << _enemy.idx << "enemy idy : " << _enemy.idy << endl;
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■ slime ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

slime::slime()
{
}

slime::~slime()
{
}

void slime::update()
{
	//cout << _player->x << endl;
	//cout << _player->y << endl;
	//거리가 가까워지면 공격 상태로 바꾼다
	if (getDistance(_player->x, _player->y, _enemy.x, _enemy.y) <= 150)
	{
		if (!_enemy.isJump)
		{
			_enemyState->chanageState("JUMP");
			_enemy.sourX = _enemy.centerX;
			_enemy.sourY = _enemy.centerY;
			_enemy.dstX = _player->x;
			_enemy.dstY = _player->y;
			_enemy.angle = getAngle(_enemy.sourX, _enemy.sourY, _enemy.dstX, _enemy.dstY);
			_enemy.isJump = true;
		}
	}
	IndexUpdate();

	_enemyState->update();
	_enemy.rc = RectMake(_enemy.x, _enemy.y, IMAGEMANAGER->findImage(_enemy.imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_enemy.imageName)->getFrameHeight());
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■ boar ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

boar::boar()
{
}

boar::~boar()
{
}

void boar::update()
{
	if (getDistance(_player->x, _player->y, _enemy.x, _enemy.y) <= 150 && !_enemy.AttackTerm)
	{
		_enemyState->chanageState("ATTACK");
		_enemy.angle = getAngle(_enemy.x, _enemy.y, _player->x, _player->y);
	}

	if (_enemy.isAttack)
	{
		_enemy.angle = getAngle(_enemy.x, _enemy.y, _player->x, _player->y);
		RECT temp;
		if (IntersectRect(&temp, &_enemy.rc, &_player->rc))
		{
			_enemy.isAttack= false;
		}
	}
	IndexUpdate();
	_enemyState->update();
	_enemy.rc = RectMake(_enemy.x, _enemy.y, IMAGEMANAGER->findImage(_enemy.imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_enemy.imageName)->getFrameHeight());
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■ Demon ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

demon::demon()
{
}

demon::~demon()
{
}

void demon::update()
{
	//도망가는 코드 만들 예정 
	if (getDistance(_enemy.x, _enemy.y,_player->x, _player->y) <= 50)
	{
		if(!_enemy.isAttack) _enemyState->chanageState("ATTACK");
		RECT temp;
	}
	if(getDistance(_enemy.x, _enemy.y, _player->x, _player->y) <= 150)
	{
		_enemy.angle = getAngle(_enemy.x, _enemy.y, _player->x, _player->y);
	}
	IndexUpdate();
	_enemyState->update();
	_enemy.rc = RectMake(_enemy.x, _enemy.y, IMAGEMANAGER->findImage(_enemy.imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_enemy.imageName)->getFrameHeight());
}


//■■■■■■■■■■■■■■■■■■■■■■■■■■■■ SKULL ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

skull::skull()
{
	firetime = TIMEMANAGER->getWorldTime();
}

skull::~skull()
{
}

void skull::update()
{
	if (firetime + RND->getFromIntTo(5,10) <= TIMEMANAGER->getWorldTime())
	{
		_bulletManager->getBullet()->fire(_enemy.x + IMAGEMANAGER->findImage(_enemy.imageName)->getFrameWidth() / 2, _enemy.y + IMAGEMANAGER->findImage(_enemy.imageName)->getFrameHeight() / 2, 0, 6);	
		_bulletManager->getBullet()->fire( _enemy.x + IMAGEMANAGER->findImage(_enemy.imageName)->getFrameWidth() / 2, _enemy.y + IMAGEMANAGER->findImage(_enemy.imageName)->getFrameHeight() / 2, 1.57, 6);
		_bulletManager->getBullet()->fire( _enemy.x + IMAGEMANAGER->findImage(_enemy.imageName)->getFrameWidth() / 2, _enemy.y + IMAGEMANAGER->findImage(_enemy.imageName)->getFrameHeight() / 2, 3.14, 6);
		_bulletManager->getBullet()->fire( _enemy.x + IMAGEMANAGER->findImage(_enemy.imageName)->getFrameWidth() / 2, _enemy.y + IMAGEMANAGER->findImage(_enemy.imageName)->getFrameHeight() / 2, 4.71, 6);
		firetime = TIMEMANAGER->getWorldTime();
	}
	IndexUpdate();
	_enemyState->update();
	_enemy.rc = RectMake(_enemy.x, _enemy.y, IMAGEMANAGER->findImage(_enemy.imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_enemy.imageName)->getFrameHeight());
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■ DemonBoss ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

demonBoss::demonBoss()
{
}

demonBoss::~demonBoss()
{
}

void demonBoss::update()
{
	IndexUpdate();
	_enemyState->update();
	_enemy.rc = RectMake(_enemy.x, _enemy.y, IMAGEMANAGER->findImage(_enemy.imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_enemy.imageName)->getFrameHeight());
}
