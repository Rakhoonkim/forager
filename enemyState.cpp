#include "stdafx.h"
#include "enemyState.h"

enemyState::enemyState()
{
}

enemyState::~enemyState()
{
}

HRESULT enemyState::init(tagObject* enemy)
{
	_enemy = enemy;
	_isMove = false;
	return S_OK;
}

void enemyState::update()
{
}

void enemyState::release()
{
}

void enemyState::IdleImage()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		if (_enemy->direc == DIRECTION::LEFT) // 哭率 
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

void enemyState::MoveImage()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		if (_enemy->direc == DIRECTION::LEFT) // 哭率 
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

void enemyState::AttackImage()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		if (_enemy->direc == DIRECTION::LEFT) // 哭率 
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

void enemyState::JumpImage()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		if (_enemy->direc == DIRECTION::LEFT) // 哭率 
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
//RENDER
void enemyState::render()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		IMAGEMANAGER->findImage(_enemy->imageName)->aniRender(CAMERAMANAGER->getWorldDC(), _enemy->x, _enemy->y, _enemy->ani);
	}
}

//♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂ enemyIdle ♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂
void enemyIdle::update()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		if (!_isMove)
		{
			_enemy->time = TIMEMANAGER->getWorldTime();
			_enemy->angle = RND->getFromFloatTo(0, 6.28f);
			_isMove = true;
		}
		else
		{
			_enemy->x += cosf(_enemy->angle) * 3 * TIMEMANAGER->getElapsedTime();
			_enemy->y += -sinf(_enemy->angle) * 3 * TIMEMANAGER->getElapsedTime();


			if (_enemy->time + 5 < TIMEMANAGER->getWorldTime())
			{
				_isMove = false;
			}
		}
	}
}

//♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂ enemyMove ♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂
void enemyMove::update()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{
		
	}
}

//♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂ enemyAttack ♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂
void enemyAttack::update()
{
	if (_enemy->enemy == ENEMY::SLIME)
	{

	}
}
