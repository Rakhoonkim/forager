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
	cout << "�� ���¾� " << endl;
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
	cout << "�� �⺻ ���¾� " << endl;
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
	cout << "�� �̵����¾� " << endl;
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
	// �밢 �� 2.355      ��  0.785 
	// �Ʒ� �� 3.925		 ��  5.46  -0.785 

	// << 3.14    0 >> 
	// �� 1.57     1/2 = 0.785 
	// �Ʒ� 4.71

	// 3�� �����°� ����ó��??
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
