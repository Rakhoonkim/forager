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
}

void enemyIdle::update()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		if (_enemy->time + 10 <= TIMEMANAGER->getWorldTime()) // 어느정도 시간이 지나면 MOVE 상태로
		{
			_enemyStateManager->chanageState("MOVE");  // 이동상태로 전환 
			_enemyStateManager->getState()->Enter();   // 이동 초기값 적용
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
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■ enemyMove ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

void enemyMove::Enter()
{
	_enemy->angle = RND->getFromFloatTo(0, 6.28f);
	_enemy->time = TIMEMANAGER->getWorldTime();
}

void enemyMove::update()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		_enemy->x += cosf(_enemy->angle) * 3 * TIMEMANAGER->getElapsedTime();
		_enemy->y += -sinf(_enemy->angle) * 3 * TIMEMANAGER->getElapsedTime();
		
		if (_enemy->time + 10 <= TIMEMANAGER->getWorldTime())
		{
			_enemyStateManager->chanageState("IDLE");
			_enemyStateManager->getState()->Enter();
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
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■ enemyAttack ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

void enemyAttack::Enter()
{
	_enemy->time = TIMEMANAGER->getWorldTime();
}

void enemyAttack::update()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		/*if (!_isAttack)
		{
			if (_enemy->ani->getMaxFrame() == 2)
			{
				_isAttack = true;
			}
		}*/
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
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■ enemyAttack ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

void enemyJump::Enter()
{
}

void enemyJump::update()
{
	//if (!_isMove) return;
	//direction(); // 방향 정의 
	//Jump();

	//float elapsedTime = TIMEMANAGER->getElapsedTime();

	////200정도의 거리를 2초에 걸쳐서 도달해야한다면 속도값을 구해줌
	//float moveSpeed = (elapsedTime / 1.0f) * getDistance(_enemy->sourX, _enemy->sourY, _enemy->dstX, _enemy->dstY);

	//_enemy->x += cosf(_enemy->angle) * moveSpeed;
	//_enemy->y += -sinf(_enemy->angle) * moveSpeed;

	//if (_enemy->time + 1 <= TIMEMANAGER->getWorldTime())
	//{
	//	_enemy->centerX = _enemy->x;
	//	_enemy->centerY = _enemy->y;
	//	_isMove = false;
	//}
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

void enemyJump::JumpInit()
{

}

void enemyJump::Jump()
{
	/*if (!_isJump)  return;

	_enemy->y -= _jumpPower;
	_jumpPower -= _gravity;


	if (_direction == DIRECTION::DOWN)
	{
		if (_enemy->dstY <= _enemy->y)
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
	}*/
}
