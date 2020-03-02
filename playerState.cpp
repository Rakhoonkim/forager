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
	_width = _player->playerImage->getFrameWidth();
	_height = _player->playerImage->getFrameHeight();
	return S_OK;
}

void playerState::update()
{
	//cout << "나 상태야 " << endl;
}

void playerState::changeImage(int right)
{
}

void playerState::setAngleKeyCollision()
{
}

void playerState::setWeaponXY()
{
}

void playerState::shadow()
{
}

void playerState::direction()
{

}

playerIdle::playerIdle(tagPlayer* player)
{
	playerState::init(player);
}

void playerIdle::update()
{
	//cout << "나 기본 상태야 " << endl;
}

void playerIdle::changeImage(int right)
{
	if (right == 1)
	{
		_player->playerImage = IMAGEMANAGER->findImage("playerIdle");
		_player->playerAni = KEYANIMANAGER->findAnimation("playerIdle_R");
		_player->weaponImage = IMAGEMANAGER->findImage("playerPick");
		_player->weaponAni = KEYANIMANAGER->findAnimation("playerPick_R");
		_player->playerAni->start();
	}
	else
	{
		_player->playerImage = IMAGEMANAGER->findImage("playerIdle");
		_player->playerAni = KEYANIMANAGER->findAnimation("playerIdle_L");
		_player->weaponImage = IMAGEMANAGER->findImage("playerPick");
		_player->weaponAni = KEYANIMANAGER->findAnimation("playerPick_L");
		_player->playerAni->start();
	}
}

void playerIdle::setWeaponXY()
{
}

playerMove::playerMove(tagPlayer* player)
{
	playerState::init(player);
}

void playerMove::update()
{
	//cout << "나 이동상태야 " << endl;
	_player->x += cosf(_angle) * _speed * TIMEMANAGER->getElapsedTime() * 50 * _player->accel;
	_player->y += -sinf(_angle) * _speed * TIMEMANAGER->getElapsedTime() * 50 * _player->accel;


	setWeaponXY();
	setAngleKeyCollision();
	shadow();
}

void playerMove::changeImage(int right)
{
	if (right == 1)  // 오른쪽 
	{
		_player->playerImage = IMAGEMANAGER->findImage("playerWalk");
		_player->playerAni = KEYANIMANAGER->findAnimation("playerWalk_R");
		_player->weaponImage = IMAGEMANAGER->findImage("playerPick");
		_player->weaponAni = KEYANIMANAGER->findAnimation("playerPick_R");
		_player->playerAni->start();
		_speed = 5;
		_angle = 0;
		_direction = 1;
	}
	else  // 왼쪽 
	{
		_player->playerImage = IMAGEMANAGER->findImage("playerWalk");
		_player->playerAni = KEYANIMANAGER->findAnimation("playerWalk_L");
		_player->weaponImage = IMAGEMANAGER->findImage("playerPick");
		_player->weaponAni = KEYANIMANAGER->findAnimation("playerPick_L");
		_player->playerAni->start();
		_speed = 5;
		_angle = 3.14;
		_direction = 0;
	}
	
}

// 2개 눌렀을 시 예외처리
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

void playerMove::setWeaponXY()
{
	if (_player->imageDirection == 1) // 오른쪽
	{
		_player->weaponX = _player->x - 20;
		_player->weaponY = _player->y - 5;
	}
	else
	{
		_player->weaponX = _player->x - 25;
		_player->weaponY = _player->y - 5;
	}
}

void playerMove::shadow()
{
	if (_player->direc == DIRECTION::UP) // 위
	{
		if (RND->getInt(2) == 1)
		{
			EFFECTMANAGER->play("shadow", _player->x + (_width / 2) - RND->getFromFloatTo(-5.0f, 5.0f), _player->y + _height - RND->getFromFloatTo(-5.0f, 5.0f));
		}
	}
	else if(_player->direc == DIRECTION::DOWN) // 아래  
	{
		if (RND->getInt(3) == 1)
		{
			EFFECTMANAGER->play("shadow", _player->x + (_width / 2) - RND->getFromFloatTo(-5.0f,5.0f), _player->y + (_height / 5) - RND->getFromFloatTo(-5.0f, 5.0f));
		}
	}
	else if (_player->direc == DIRECTION::LEFT) // 오른쪽 
	{
		if (RND->getInt(2) == 1)
		{
			EFFECTMANAGER->play("shadow", _player->x + _width - RND->getFromFloatTo(-5.0f, 5.0f), _player->y + _height - RND->getFromFloatTo(-5.0f, 5.0f));
		}
	}
	else if (_player->direc == DIRECTION::RIGHT) // 아래  
	{
		if (RND->getInt(2) == 1)
		{
			EFFECTMANAGER->play("shadow", _player->x - RND->getFromFloatTo(-5.0f, 5.0f), _player->y + _height - RND->getFromFloatTo(-5.0f, 5.0f));
		}
	}
}

