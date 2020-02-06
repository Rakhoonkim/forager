#include "stdafx.h"
#include "playerState.h"
#include "player.h"

playerState::playerState()
{
}

playerState::~playerState()
{
}

HRESULT playerState::init(tagPlayer* player)
{
	_player = player;
	_angle = 0;
	_speed = 0;
	_direction = false;
	return S_OK;
}

void playerState::update()
{
	cout << "나 상태야 " << endl;
}

void playerState::changeImage(int right)
{
}

void playerState::setAngleKeyCollision()
{
}

playerIdle::playerIdle(tagPlayer* player)
{
	playerState::init(player);
}

void playerIdle::update()
{
	cout << "나 기본 상태야 " << endl;
}

void playerIdle::changeImage(int right)
{
	if (right == 1)
	{
		_player->image = IMAGEMANAGER->findImage("playerIdle");
		_player->ani = KEYANIMANAGER->findAnimation("playerIdle_R");
		_player->ani->start();
	}
	else
	{
		_player->image = IMAGEMANAGER->findImage("playerIdle");
		_player->ani = KEYANIMANAGER->findAnimation("playerIdle_L");
		_player->ani->start();
	}
}

playerMove::playerMove(tagPlayer* player)
{
	playerState::init(player);
}

void playerMove::update()
{
	cout << "나 이동상태야 " << endl;
	_player->x += cosf(_angle) * _speed;
	_player->y += -sinf(_angle) * _speed;
	setAngleKeyCollision();
}

void playerMove::changeImage(int right)
{
	if (right == 1)
	{
		_player->image = IMAGEMANAGER->findImage("playerWalk");
		_player->ani = KEYANIMANAGER->findAnimation("playerWalk_R");
		_player->ani->start();
		_speed = 5;
		_angle = 0;
		_direction = 1;
	}
	else
	{
		_player->image = IMAGEMANAGER->findImage("playerWalk");
		_player->ani = KEYANIMANAGER->findAnimation("playerWalk_L");
		_player->ani->start();
		_speed = 5;
		_angle = 3.14;
		_direction = 0;
	}
	
}

void playerMove::setAngleKeyCollision()
{
	// 대각 좌 2.355      우  0.785 
	// 아래 좌 3.925		 우  5.46  -0.785 

	// << 3.14    0 >> 
	// 위 1.57     1/2 = 0.785 
	// 아래 4.71

	// 3개 눌리는거 예외처리??
	if (KEYMANAGER->isStayTwoDown('W', 'A'))
	{
		if (_angle < UP_LEFTANGLE)
		{
			_angle += ANGLESPEED;
		}
		else if (_angle > UP_LEFTANGLE)
		{
			_angle -= ANGLESPEED;
		}
		else _angle = UP_LEFTANGLE;
		
	}
	else if (KEYMANAGER->isStayTwoDown('W', 'D'))
	{
		if (_angle < UP_RIGHTANGLE)
		{
			_angle += ANGLESPEED;
		}
		else if (_angle > UP_RIGHTANGLE)
		{
			_angle -= ANGLESPEED;
		}
		else _angle = UP_RIGHTANGLE;
		
	}
	else if (KEYMANAGER->isStayTwoDown('S', 'A'))
	{
		if (_angle < DOWN_LEFTANGLE)
		{
			_angle += ANGLESPEED;
		}
		else if (_angle > DOWN_LEFTANGLE)
		{
			_angle -= ANGLESPEED;
		}
		else _angle = DOWN_LEFTANGLE;
		
	}
	else if (KEYMANAGER->isStayTwoDown('S', 'D'))
	{
		if (_angle == 0) _angle = 2 * PI;
		if (_angle < DOWN_RIGHTANGLE)
		{
			_angle += ANGLESPEED;
		}
		else if (_angle > DOWN_RIGHTANGLE)
		{
			_angle -= ANGLESPEED;
		}
		else _angle = DOWN_RIGHTANGLE;
	}
}
