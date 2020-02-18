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

	_enemy.angle = 0;
	_enemy.x = idx * 60;
	_enemy.y = idy * 60;
	_enemy.centerX = _enemy.x + 30;
	_enemy.centerY = _enemy.y + 30;

	_StateAttack = false;
	_StateTurn = false;

	//새로 세팅해야 하는 값		
	_enemy.maxHp = 0;			// 최대 HP
	_enemy.hp = 0;				// HP
	_enemy.damage = 0;			// 데미지

	_enemy.time = TIMEMANAGER->getWorldTime();
	
	//상태정의
	_enemyState = new enemyStateManager;
	_enemyState->init();

	_enemyState->addState("IDLE", new enemyIdle(_enemyState , &_enemy));
	_enemyState->addState("MOVE", new enemyMove(_enemyState , &_enemy));
	_enemyState->addState("ATTACK", new enemyAttack(_enemyState ,&_enemy));
	_enemyState->addState("JUMP", new enemyJump(_enemyState , &_enemy));

	_enemyState->chanageState("IDLE");




	


	////상태정의
	//_enemyState = new enemyState();
	//_enemyState->init(&_enemy);

	//_enemyIdle = new enemyIdle(&_enemy);
	//_enemyMove = new enemyMove(&_enemy);
	//_enemyAttack = new enemyAttack(&_enemy);
	//_enemyJump = new enemyJump(&_enemy);
	//_enemyState = _enemyIdle;

	_enemy.rc = RectMake(_enemy.x, _enemy.y, IMAGEMANAGER->findImage(_enemy.imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_enemy.imageName)->getFrameHeight());
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
	//RECT idx, idy
	_enemy.rc = RectMake(_enemy.x, _enemy.y, IMAGEMANAGER->findImage(_enemy.imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_enemy.imageName)->getFrameHeight());
	_enemy.idx = _enemy.x / 60;
	_enemy.idy = _enemy.y / 60;

	//이미지방향값 정의
	if (_enemy.angle >= 0 && _enemy.angle <= 1.57)
	{
		_enemy.imageDirection = DIRECTION::RIGHT;
	}
	else if (_enemy.angle <= 3.14 && _enemy.angle > 1.57)
	{
		_enemy.imageDirection = DIRECTION::LEFT;
	}
	else if (_enemy.angle <= 4.71 && _enemy.angle > 3.14)
	{
		_enemy.imageDirection = DIRECTION::LEFT;
	}
	else
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
	//cout << "나지금 슬라임 update" << endl;
 //	if (!_enemyState->getAttack() && !_enemyState->getJump())
	//{
	//	cout << " if 안으로 들어왔음 " << endl;
	//	if (_enemy.time + 10 <= TIMEMANAGER->getWorldTime())
	//	{
	//		_enemy.time = TIMEMANAGER->getWorldTime();
	//		// 상태 정의 
	//		if (RND->getInt(2) == 0)  //  1/2 
	//		{
	//			_enemyState = _enemyIdle;
	//			cout << "Idle 상태로" << endl;
	//		}
	//		else
	//		{
	//			_enemyState = _enemyMove;
	//			_enemyState->setMove(true);
	//			cout << "Move 상태로" << endl;
	//		}
	//	}
	//}

	//if (getDistance(_player->x,_player->y,_enemy.x,_enemy.y) <= 60 && !_enemyState->getJump())
	//{
	//	_enemyState = _enemyJump;
	//	_enemyState->ChangeImage();
	//	_enemyState->JumpInit();
	//	_enemyState->setMove(true);
	//	_enemy.sourX = _enemy.centerX;
	//	_enemy.sourY = _enemy.centerY;
	//	_enemy.dstX = _player->x;
	//	_enemy.dstY = _player->y;
	//}
	//else if (!_enemyState->getMove() && !_enemyState->getJump())
	//{
	//	_enemyState = _enemyAttack;
	//	_enemyState->ChangeImage();
	//}



	_enemyState->update();
	IndexUpdate();
	_enemy.rc = RectMake(_enemy.x, _enemy.y, IMAGEMANAGER->findImage(_enemy.imageName)->getFrameWidth(), IMAGEMANAGER->findImage(_enemy.imageName)->getFrameHeight());
}
