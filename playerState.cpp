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

	//if (KEYMANAGER->isStayKeyDown('W'))
	//{
	//	cout << "나 위로이동상태야 " << endl;
	//	if (_direction) // 오른쪽 
	//	{
	//		if(_angle < 0.785f)	_angle += 2 * PI / 90;
	//	}
	//	else // 왼쪽 
	//	{
	//		if (_angle > 2.355f)	_angle -= 2 * PI / 90;
	//	}
	//}
	//if (KEYMANAGER->isStayKeyDown('S'))
	//{
	//	cout << "나 아래로이동상태야 " << endl;
	//	if (_direction) // 오른쪽 
	//	{
	//		if (_angle > -0.785f) _angle -= 2 * PI / 90;
	//	}
	//	else // 왼쪽 
	//	{
	//		if (_angle < 3.925f) _angle += 2 * PI / 90;
	//	}
	//}
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
