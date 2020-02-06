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

	//if (KEYMANAGER->isStayKeyDown('W'))
	//{
	//	cout << "�� �����̵����¾� " << endl;
	//	if (_direction) // ������ 
	//	{
	//		if(_angle < 0.785f)	_angle += 2 * PI / 90;
	//	}
	//	else // ���� 
	//	{
	//		if (_angle > 2.355f)	_angle -= 2 * PI / 90;
	//	}
	//}
	//if (KEYMANAGER->isStayKeyDown('S'))
	//{
	//	cout << "�� �Ʒ����̵����¾� " << endl;
	//	if (_direction) // ������ 
	//	{
	//		if (_angle > -0.785f) _angle -= 2 * PI / 90;
	//	}
	//	else // ���� 
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
