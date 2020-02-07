#include "stdafx.h"
#include "player.h"

player::player()
{
}

player::~player()
{
}

HRESULT player::init()
{
	_player.playerImage = IMAGEMANAGER->findImage("playerIdle");
	_player.playerAni = KEYANIMANAGER->findAnimation("playerIdle_R");
	_player.weaponImage = IMAGEMANAGER->findImage("playerPick");
	_player.weaponAni = KEYANIMANAGER->findAnimation("playerPick_R");
	_player.playerAni->start();
	_player.idx = 22;
	_player.idy = 18;
	_player.x = _player.idx * 60 + 30;
	_player.y = _player.idy * 60 + 30;
	_player.weaponX = _player.x -15;
	_player.weaponY = _player.y -5;
	_player.direction = 0;     // 0 왼쪽 1 오른쪽 
	_state = new playerState();
	_state->init(&_player);

	_playerMove = new playerMove(&_player);
	_playerIdle = new playerIdle(&_player);

	_state = _playerIdle;
	_stateChange = false;
	_keyCount = 0;
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_state->update();
	KeyControl();
	CAMERAMANAGER->setCameraXY(_player.x, _player.y);
	// 무기 위치 고정 
}

void player::render()
{
	_player.playerImage->aniRender(CAMERAMANAGER->getWorldDC(), _player.x, _player.y, _player.playerAni);
	_player.weaponImage->aniRender(CAMERAMANAGER->getWorldDC(), _player.weaponX, _player.weaponY, _player.weaponAni);
	char str[100];
	sprintf_s(str, "%f", _state->getAngle());
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, str, strlen(str));
}

void player::KeyControl()
{
	if (_keyCount > 2) return;
	// UP
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (!_stateChange)
		{
			_keyCount++;
			_state = _playerMove;
			_state->changeImage(_player.direction);
			_stateChange = true;
			_state->setAngle(1.57f);
			_state->setSpeed(5);
		}
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		_keyCount--;
		_state = _playerIdle;
		_state->changeImage(_player.direction);
		_stateChange = false;
	}
	//DOWN
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (!_stateChange)
		{
			_keyCount++;
			_state = _playerMove;
			_state->changeImage(_player.direction);
			_stateChange = true;
			_state->setAngle(4.71f);
			_state->setSpeed(5);
		}
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		_keyCount--;
		_state = _playerIdle;
		_state->changeImage(_player.direction);
		_stateChange = false;
	}
	// LEFT
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (!_stateChange)
		{
			_keyCount++;
			_player.direction = 0;
			_state = _playerMove;
			_state->changeImage(_player.direction);
			_stateChange = true;
		}
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_keyCount--;
		_state = _playerIdle;
		_state->changeImage(_player.direction);
		_stateChange = false;

	}
	// RIGHT
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (!_stateChange)
		{
			_keyCount++;
			_player.direction = 1;
			_state = _playerMove;
			_state->changeImage(_player.direction);
			_stateChange = true;
		}
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_keyCount--;
		_state = _playerIdle;
		_state->changeImage(true);
		_stateChange = false;
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_player.weaponAni->start();
	}
}


