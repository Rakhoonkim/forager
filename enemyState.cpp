#include "stdafx.h"
#include "enemyState.h"
#include "enemyStateManager.h"

enemyState::enemyState()
{
}

enemyState::~enemyState()
{
}

HRESULT enemyState::init()
{
	return S_OK;
}

HRESULT enemyState::init(tagObject* enemy)
{
	_enemy = enemy;
	return S_OK;
}

void enemyState::update()
{
}

void enemyState::release()
{
}

void enemyState::ChangeImage()
{
}

void enemyState::Enter()
{
}

void enemyState::direction()
{
}

void enemyState::Jump()
{
}

//RENDER
void enemyState::render()
{
	IMAGEMANAGER->findImage(_enemy->imageName)->aniRender(CAMERAMANAGER->getWorldDC(), _enemy->x, _enemy->y, _enemy->ani);
	//Rectangle(CAMERAMANAGER->getWorldDC(), _enemy->rc);
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■ enemyIdle ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

void enemyIdle::Enter()
{
	_enemy->time = TIMEMANAGER->getWorldTime();
	_enemy->angle = RND->getFromFloatTo(0, 6.28f);
	_enemy->AttackTerm = true;
}

void enemyIdle::update()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		if (_enemy->isJump)
		{
			if (_enemy->time + 1 < TIMEMANAGER->getWorldTime()) _enemy->isJump = false;
		}
		if (_enemy->time + 10 <= TIMEMANAGER->getWorldTime()) // 어느정도 시간이 지나면 MOVE 상태로
		{
			_enemyStateManager->chanageState("MOVE");  // 이동상태로 전환 
		}
	}
	else if (_enemy->enemy == ENEMY::BOAR)
	{
		_enemy->AttackTerm = false;
		if (_enemy->time + RND->getFromIntTo(3,10) <= TIMEMANAGER->getWorldTime()) // 어느정도 시간이 지나면 MOVE 상태로
		{
			_enemyStateManager->chanageState("MOVE");  // 이동상태로 전환 
		}
	}
	else if (_enemy->enemy == ENEMY::DEMON)
	{
		if (_enemy->time + 3 <= TIMEMANAGER->getWorldTime())
		{
			_enemy->AttackTerm = false;
		}
		if (_enemy->time + RND->getFromIntTo(5, 10) <= TIMEMANAGER->getWorldTime()) // 어느정도 시간이 지나면 MOVE 상태로
		{
			_enemyStateManager->chanageState("MOVE");  // 이동상태로 전환 
			_enemy->isAttack = false;
		}
	}
	else if (_enemy->enemy == ENEMY::SKULL)
	{
		if (_enemy->time + RND->getInt(5) <= TIMEMANAGER->getWorldTime())
		{
			_enemyStateManager->chanageState("MOVE");  // 이동상태로 전환 
		}
	}
}

void enemyIdle::ChangeImage()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		if (_enemy->imageDirection == DIRECTION::LEFT) // 왼쪽 
		{
			_enemy->ani = KEYANIMANAGER->findAnimation("slimeIdleLeft");
			_enemy->ani->start();
		}
		else
		{
			_enemy->ani = KEYANIMANAGER->findAnimation("slimeIdleRight");
			_enemy->ani->start();
		}
	}
	else if (_enemy->enemy == ENEMY::BOAR)
	{
		if (_enemy->imageDirection == DIRECTION::LEFT) // 왼쪽 
		{
			_enemy->imageName = "boarIdle";
			_enemy->ani = KEYANIMANAGER->findAnimation("boarIdleLeft");
			_enemy->ani->start();
		}
		else
		{
			_enemy->imageName = "boarIdle";
			_enemy->ani = KEYANIMANAGER->findAnimation("boarIdleRight");
			_enemy->ani->start();
		}
	}
	else if (_enemy->enemy == ENEMY::DEMON)
	{
		if (_enemy->imageDirection == DIRECTION::LEFT) // 왼쪽 
		{
			_enemy->imageName = "demonWalk";
			_enemy->ani = KEYANIMANAGER->findAnimation("demonIdleLeft");
			_enemy->ani->start();
		}
		else
		{
			_enemy->imageName = "demonWalk";
			_enemy->ani = KEYANIMANAGER->findAnimation("demonIdleRight");
			_enemy->ani->start();
		}
	}
	else if (_enemy->enemy == ENEMY::SKULL)
	{
		if (_enemy->imageDirection == DIRECTION::LEFT) // 왼쪽 
		{
			_enemy->ani = KEYANIMANAGER->findAnimation("skullLeft");
			_enemy->ani->start();
		}
		else
		{
			_enemy->ani = KEYANIMANAGER->findAnimation("skullRight");
			_enemy->ani->start();
		}
	}
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■ enemyMove ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

void enemyMove::Enter()
{
	//보어일때
	if (_enemy->enemy == ENEMY::BOAR)
	{
		if (_enemy->imageDirection == DIRECTION::LEFT)
		{
			_enemy->angle = RND->getFromFloatTo(1.57, 4.81f);
		}
		else
		{
			_enemy->angle = RND->getFromFloatTo(-1.57, 1.57f);
		}
	}
	_enemy->time = TIMEMANAGER->getWorldTime();
	_enemy->AttackTerm = true;
	//스컬
	if (_enemy->enemy == ENEMY::SKULL)
	{
		if (RND->getInt(2) == 0)
		{
			_move = 0.1f;
		}
		else
		{
			_move = -0.1f;
		}
		_movePattern = RND->getInt(2);
	}
}

void enemyMove::update()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		if (_enemy->isJump)
		{
			if (_enemy->time +1 < TIMEMANAGER->getWorldTime()) _enemy->isJump = false;
		}

		_enemy->x += cosf(_enemy->angle) * 3 * TIMEMANAGER->getElapsedTime();
		_enemy->y += -sinf(_enemy->angle) * 3 * TIMEMANAGER->getElapsedTime();
		

		if (_enemy->time + 10 <= TIMEMANAGER->getWorldTime())
		{
			_enemyStateManager->chanageState("IDLE");
		}
	}
	else if (_enemy->enemy == ENEMY::BOAR)
	{
		_enemy->x += cosf(_enemy->angle) * 10 * TIMEMANAGER->getElapsedTime();
		_enemy->y += -sinf(_enemy->angle) * 10 * TIMEMANAGER->getElapsedTime();

		if (_enemy->time + RND->getFromIntTo(3,10) <= TIMEMANAGER->getWorldTime())
		{
			_enemyStateManager->chanageState("IDLE");
		}
	}
	else if (_enemy->enemy == ENEMY::DEMON)
	{
		_enemy->x += cosf(_enemy->angle) * 20 * TIMEMANAGER->getElapsedTime();
		_enemy->y += -sinf(_enemy->angle) * 20 * TIMEMANAGER->getElapsedTime();

		if (_enemy->time + RND->getFromIntTo(5, 10) <= TIMEMANAGER->getWorldTime())
		{
			_enemyStateManager->chanageState("IDLE");
		}
	}
	else if (_enemy->enemy == ENEMY::SKULL)
	{
		if (_movePattern == 0)_enemy->angle += _move;
		_enemy->x += cosf(_enemy->angle) * 100 * TIMEMANAGER->getElapsedTime();
		_enemy->y += -sinf(_enemy->angle) * 100 * TIMEMANAGER->getElapsedTime();
		if (_enemy->time + 3 <= TIMEMANAGER->getWorldTime())
		{
			_enemyStateManager->chanageState("IDLE");  // 이동상태로 전환 
		}
	}

}

void enemyMove::ChangeImage()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		if (_enemy->imageDirection == DIRECTION::LEFT) // 왼쪽 
		{
			_enemy->ani = KEYANIMANAGER->findAnimation("slimeIdleLeft");
			_enemy->ani->start();
		}
		else
		{
			_enemy->ani = KEYANIMANAGER->findAnimation("slimeIdleRight");
			_enemy->ani->start();
		}
	}
	else if (_enemy->enemy == ENEMY::BOAR)
	{
		if (_enemy->imageDirection == DIRECTION::LEFT) // 왼쪽 
		{
			_enemy->imageName = "boarWalk";
			_enemy->ani = KEYANIMANAGER->findAnimation("boarWalkLeft");
			_enemy->ani->start();
		}
		else
		{
			_enemy->imageName = "boarWalk";
			_enemy->ani = KEYANIMANAGER->findAnimation("boarWalkRight");
			_enemy->ani->start();
		}
	}
	else if (_enemy->enemy == ENEMY::DEMON)
	{
		if (_enemy->imageDirection == DIRECTION::LEFT) // 왼쪽 
		{
			_enemy->imageName = "demonWalk";
			_enemy->ani = KEYANIMANAGER->findAnimation("demonWalkLeft");
			_enemy->ani->start();
		}
		else
		{
			_enemy->imageName = "demonWalk";
			_enemy->ani = KEYANIMANAGER->findAnimation("demonWalkRight");
			_enemy->ani->start();
		}
	}
	else if (_enemy->enemy == ENEMY::SKULL)
	{
		if (_enemy->imageDirection == DIRECTION::LEFT) // 왼쪽 
		{
			_enemy->ani = KEYANIMANAGER->findAnimation("skullLeft");
			_enemy->ani->start();
		}
		else
		{
			_enemy->ani = KEYANIMANAGER->findAnimation("skullRight");
			_enemy->ani->start();
		}
	}
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■ enemyAttack ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

void enemyAttack::Enter()
{
	_enemy->time = TIMEMANAGER->getWorldTime();
	_enemy->isAttack = true;
	_enemy->AttackTerm = false;
	_enemy->acel = 1.0f;
}

void enemyAttack::update()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		if (_enemy->ani->getNowPlayNum() == _enemy->ani->getFrameMaxFrame() - 1)
		{
			_enemyStateManager->chanageState("MOVE");
		}
	}
	else if (_enemy->enemy == ENEMY::BOAR)
	{
		_enemy->x += cosf(_enemy->angle) * 20 * TIMEMANAGER->getElapsedTime() * _enemy->acel;
		_enemy->y += -sinf(_enemy->angle) * 20 * TIMEMANAGER->getElapsedTime() * _enemy->acel;
		if(_enemy->acel <= 8.0f ) _enemy->acel += 0.40f;

		if (!_enemy->isAttack)
		{
			_enemyStateManager->chanageState("MOVE");
		}
	}
	else if (_enemy->enemy == ENEMY::DEMON)
	{
		if (_enemy->ani->getNowPlayNum() == _enemy->ani->getFrameMaxFrame() - 1)
		{
			_enemyStateManager->chanageState("IDLE");  //ATTAC-> idle 넘어가는거 
		}
	}
}

void enemyAttack::ChangeImage()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		if (_enemy->imageDirection == DIRECTION::LEFT) // 왼쪽 
		{
			_enemy->ani = KEYANIMANAGER->findAnimation("slimeAttackLeft");
			_enemy->ani->start();
		}
		else
		{
			_enemy->ani = KEYANIMANAGER->findAnimation("slimeAttackRight");
			_enemy->ani->start();
		}
	}
	else if (_enemy->enemy == ENEMY::BOAR)
	{
		if (_enemy->imageDirection == DIRECTION::LEFT) // 왼쪽 
		{
			_enemy->imageName = "boarCharge";
			_enemy->ani = KEYANIMANAGER->findAnimation("boarChargeLeft");
			_enemy->ani->start();
		}
		else
		{
			_enemy->imageName = "boarCharge";
			_enemy->ani = KEYANIMANAGER->findAnimation("boarChargeRight");
			_enemy->ani->start();
		}
	}
	else if (_enemy->enemy == ENEMY::DEMON)
	{
		if (_enemy->imageDirection == DIRECTION::LEFT) // 왼쪽 
		{
			_enemy->imageName = "demonAttack";
			_enemy->ani = KEYANIMANAGER->findAnimation("demonAttackLeft");
			_enemy->ani->start();
		}
		else
		{
			_enemy->imageName = "demonAttack";
			_enemy->ani = KEYANIMANAGER->findAnimation("demonAttackRight");
			_enemy->ani->start();
		}
	}
	else if (_enemy->enemy == ENEMY::SKULL)
	{
		if (_enemy->imageDirection == DIRECTION::LEFT) // 왼쪽 
		{
			_enemy->ani = KEYANIMANAGER->findAnimation("skullLeft");
			_enemy->ani->start();
		}
		else
		{
			_enemy->ani = KEYANIMANAGER->findAnimation("skullRight");
			_enemy->ani->start();
		}
	}
}

void enemyAttack::render()
{
	if (_enemy->enemy == ENEMY::DEMON)
	{
		IMAGEMANAGER->findImage(_enemy->imageName)->aniRender(CAMERAMANAGER->getWorldDC(), _enemy->x, _enemy->y - 18, _enemy->ani);
	}
	else
	{
		IMAGEMANAGER->findImage(_enemy->imageName)->aniRender(CAMERAMANAGER->getWorldDC(), _enemy->x, _enemy->y, _enemy->ani);
	}
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■ enemyJUMP ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

enemyJump::enemyJump(enemyStateManager* enemyStateManager, tagObject* enemy)
{
	this->Set_enemyStateManager(enemyStateManager); 
	_enemy = enemy;
	_direction = DIRECTION::RIGHT;
	_jumpPower = 15;
	_gravity = 0.9;
	_isJump = true;
	_isMove = true;
}

void enemyJump::Enter()
{
	_enemy->time = TIMEMANAGER->getWorldTime();
	_jumpPower = 15;
	_gravity = 0.9;
	_isJump = true;
	_isMove = true;
}

void enemyJump::update()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		if (!_isMove) return;
		direction(); // 방향 정의 
		Jump();

		float elapsedTime = TIMEMANAGER->getElapsedTime();

		//200정도의 거리를 2초에 걸쳐서 도달해야한다면 속도값을 구해줌
		float moveSpeed = (elapsedTime / 1.0f) * getDistance(_enemy->sourX, _enemy->sourY, _enemy->dstX, _enemy->dstY);
		if (_isJump)
		{
			_enemy->x += cosf(_enemy->angle) * moveSpeed;
			_enemy->y += -sinf(_enemy->angle) * moveSpeed;
		}
		if (_enemy->time + 1 <= TIMEMANAGER->getWorldTime())
		{
			_enemy->centerX = _enemy->x;
			_enemy->centerY = _enemy->y;
			_isMove = false;
			_enemyStateManager->chanageState("ATTACK");
		}
	}
}

void enemyJump::ChangeImage()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		if (_enemy->imageDirection == DIRECTION::LEFT) // 왼쪽 
		{
			_enemy->ani = KEYANIMANAGER->findAnimation("slimeJumpLeft");
			_enemy->ani->start();
		}
		else
		{
			_enemy->ani = KEYANIMANAGER->findAnimation("slimeJumpRight");
			_enemy->ani->start();
		}
	}
}

void enemyJump::direction()
{
	//공격 방향을 정의 
	if (_enemy->angle > 0.758f && _enemy->angle <= 2.382)
	{
		_direction = DIRECTION::UP;
	}
	else if (_enemy->angle <= 3.952f && _enemy->angle > 2.382)
	{
		_direction = DIRECTION::LEFT;
	}
	else if (_enemy->angle <= 5.522 && _enemy->angle > 3.952) // 아래 방향 
	{
		_direction = DIRECTION::DOWN;
	}
	else if ((_enemy->angle <= 6.28 && _enemy->angle > 5.522) || (_enemy->angle < 0.758 && _enemy->angle >= 0))
	{
		_direction = DIRECTION::RIGHT;
	}
}

void enemyJump::Jump()
{
	if (!_isJump)  return;

	_enemy->y -= _jumpPower;
	_jumpPower -= _gravity;


	if (_direction == DIRECTION::DOWN)
	{
		if (_enemy->dstY + 10 <= _enemy->y)
		{
			_isJump = false;
		}
	}
	else if (_direction == DIRECTION::UP)
	{
		if (_jumpPower < 0 && _enemy->dstY <= _enemy->y)
		{
			_isJump = false;
		}
	}
	else
	{
		if (_enemy->sourY <= _enemy->y)
		{
			_isJump = false;
		}
	}
}
