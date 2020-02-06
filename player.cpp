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
	_player.image = IMAGEMANAGER->findImage("playerIdle");
	_player.ani = KEYANIMANAGER->findAnimation("playerIdle_R");

	//_player.image = IMAGEMANAGER->findImage("playerWalk");
	//_player.ani = KEYANIMANAGER->findAnimation("playerWalk_R");
	_player.ani->start();
	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;
	_player.direction = 0;     // 0 ¿ÞÂÊ 1 ¿À¸¥ÂÊ 
	_state = new playerState();
	_state->init(&_player);

	_playerMove = new playerMove(&_player);

	_playerIdle = new playerIdle(&_player);


	_state = _playerIdle;
	_stateChange = false;
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_state->update();
	KeyControl();
}

void player::render()
{
	_player.image->aniRender(getMemDC(), _player.x, _player.y, _player.ani);
	char str[100];
	sprintf_s(str, "%f", _state->getAngle());
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, str, strlen(str));
}

void player::KeyControl()
{
	// UP
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (!_stateChange)
		{
			_state = _playerMove;
			_state->changeImage(_player.direction);
			_stateChange = true;
			_state->setAngle(1.57f);
			_state->setSpeed(5);
		}
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		_state = _playerIdle;
		_state->changeImage(_player.direction);
		_stateChange = false;
	}
	//DOWN
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (!_stateChange)
		{
			_state = _playerMove;
			_state->changeImage(_player.direction);
			_stateChange = true;
			_state->setAngle(4.71f);
			_state->setSpeed(5);
		}
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		_state = _playerIdle;
		_state->changeImage(_player.direction);
		_stateChange = false;
	}
	// LEFT
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (!_stateChange)
		{
			_player.direction = 0;
			_state = _playerMove;
			_state->changeImage(_player.direction);
			_stateChange = true;
		}
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_state = _playerIdle;
		_state->changeImage(_player.direction);
		_stateChange = false;

	}
	// RIGHT
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (!_stateChange)
		{
			_player.direction = 1;
			_state = _playerMove;
			_state->changeImage(_player.direction);
			_stateChange = true;
		}
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_state = _playerIdle;
		_state->changeImage(true);
		_stateChange = false;
	}
}


