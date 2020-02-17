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
	_player.direc = DIRECTION::RIGHT;
	_player.idx = 22;
	_player.idy = 18;
	_player.x = _player.idx * 60 + 30;
	_player.y = _player.idy * 60 + 30;
	_player.weaponX = _player.x -15;
	_player.weaponY = _player.y -5;
	_player.imageDirection = 0;     // 0 哭率 1 坷弗率 
	_player.speed = 5;
	_player.acel = 1.1;
	_player.hp = 3;
	_player.maxHp = 3;
	_player.health = 100;
	_player.damage = 1;

	_state = new playerState();
	_state->init(&_player);

	_playerMove = new playerMove(&_player);
	_playerIdle = new playerIdle(&_player);

	_state = _playerIdle;
	_stateChange = false;
	_keyCount = 0;

	_player.rc = RectMake(_player.x, _player.y, _player.playerImage->getFrameWidth(), _player.playerImage->getFrameHeight());


	CAMERAMANAGER->setCameraInit(_player.x, _player.y);
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_state->update();
	KeyControl();
	IndexUpdate();
	MAPMANAGER->setPlayerAddress(&_player);
	MAPMANAGER->setPlayerTileColision(_player.idx, _player.idy);  // 面倒贸府 
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !UIMANAGER->getOption())
	{
		_player.weaponAni->start();
		//ITEMMANAGER->Dropitem("woodDrop", _player.x, _player.y);
		KEYMANAGER->setKeyDown(VK_LBUTTON, false);
	}
	_player.rc = RectMake(_player.x, _player.y, _player.playerImage->getFrameWidth(), _player.playerImage->getFrameHeight());
	cout << "付快胶 : x" <<  _ptMouse.x << endl;
}

void player::render()
{
	_player.playerImage->aniRender(CAMERAMANAGER->getWorldDC(), _player.x, _player.y, _player.playerAni);
	_player.weaponImage->aniRender(CAMERAMANAGER->getWorldDC(), _player.weaponX, _player.weaponY, _player.weaponAni);

	//Rectangle(CAMERAMANAGER->getWorldDC(), _player.rc);
	char str[100];
	sprintf_s(str, "%f", _state->getAngle());
	TextOut(CAMERAMANAGER->getWorldDC(), _player.x, _player.y+50, str, strlen(str));
	char strIdx[100];
	sprintf_s(strIdx, "idx : %d", _player.idx);
	TextOut(CAMERAMANAGER->getWorldDC(), _player.x, _player.y, strIdx, strlen(strIdx));
	char strIdy[100];
	sprintf_s(strIdy, "idy : %d", _player.idy);
	TextOut(CAMERAMANAGER->getWorldDC(), _player.x+ 100, _player.y, strIdy, strlen(strIdy));
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
			_state->changeImage(_player.imageDirection);
			_stateChange = true;
			_state->setAngle(1.57f);
			_state->setSpeed(5);
			_player.direc = DIRECTION::UP;
			_player.acel = 1;
		}
		acelPlus();
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		_keyCount--;
		_state = _playerIdle;
		_state->changeImage(_player.imageDirection);
		_stateChange = false;
	}
	//DOWN
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (!_stateChange)
		{
			_keyCount++;
			_state = _playerMove;
			_state->changeImage(_player.imageDirection);
			_stateChange = true;
			_state->setAngle(4.71f);
			_state->setSpeed(5);
			_player.direc = DIRECTION::DOWN;
			_player.acel = 1;
		}
		acelPlus();
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		_keyCount--;
		_state = _playerIdle;
		_state->changeImage(_player.imageDirection);
		_stateChange = false;
	}
	// LEFT
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (!_stateChange)
		{
			_keyCount++;
			_player.imageDirection = 0;
			_state = _playerMove;
			_state->changeImage(_player.imageDirection);
			_stateChange = true;
			_player.direc = DIRECTION::LEFT;
			_player.acel = 1;
		}
		acelPlus();
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_keyCount--;
		_state = _playerIdle;
		_state->changeImage(_player.imageDirection);
		_stateChange = false;
	}
	// RIGHT
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (!_stateChange)
		{
			_keyCount++;
			_player.imageDirection = 1;
			_state = _playerMove;
			_state->changeImage(_player.imageDirection);
			_stateChange = true;
			_player.direc = DIRECTION::RIGHT;
			_player.acel = 1;
		}
		acelPlus();
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_keyCount--;
		_state = _playerIdle;
		_state->changeImage(true);
		_stateChange = false;
	}
}

void player::IndexUpdate()
{
	CAMERAMANAGER->setCameraXY(_player.x, _player.y);
	_player.idx = (int)(_player.x + 30) / 60;
	_player.idy = (int)(_player.y + 30) / 60;
}

void player::acelPlus()
{
	if (_player.acel >= 2) return;
	_player.acel += 0.05;
}



