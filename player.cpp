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
	_tempDirection = DIRECTION::RIGHT;
	_player.angle = 0;
	_player.idx = 22;
	_player.idy = 18;
	_player.x = _player.idx * 60 + 30;
	_player.y = _player.idy * 60 + 30;
	_player.weaponX = _player.x -15;
	_player.weaponY = _player.y -5;
	_player.imageDirection = 0;     // 0 왼쪽 1 오른쪽 
	_player.speed = 5;
	_player.acel = 1.1;
	_player.hp = 3;
	_player.maxHp = 3;
	_player.health = 100;
	_player.damage = 1;
	_player.level = 1;
	_player.expMax = 30;
	_player.exp = 0;
	_player.skillPount = 0;
	_player.isHit = false;
	_player.hitCount = 0;
	_player.alpha = 0;
	_state = new playerState();
	_state->init(&_player);

	_playerMove = new playerMove(&_player);
	_playerIdle = new playerIdle(&_player);
	_player.isAttack = false;
	_state = _playerIdle;
	_stateChange = false;
	_keyCount = 0;

	_player.rc = RectMake(_player.x, _player.y, _player.playerImage->getFrameWidth(), _player.playerImage->getFrameHeight());


	CAMERAMANAGER->setCameraInit(_player.x, _player.y);


	MAPMANAGER->setPlayerAddress(&_player);
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
	//setDirection();
	playerHitCount();
	MAPMANAGER->setPlayerAddress(&_player);
	MAPMANAGER->setPlayerStageTileColision(_player.idx, _player.idy);  // 충돌처리 

	_player.rc = RectMake(_player.x, _player.y, _player.playerImage->getFrameWidth(), _player.playerImage->getFrameHeight());
}

void player::render()
{

	if (_player.alpha <= 0)
	{
		_player.playerImage->aniRender(CAMERAMANAGER->getWorldDC(), _player.x, _player.y, _player.playerAni);
		_player.weaponImage->aniRender(CAMERAMANAGER->getWorldDC(), _player.weaponX, _player.weaponY, _player.weaponAni);
	}
	else
	{
		_player.playerImage->aniAlphaRender(CAMERAMANAGER->getWorldDC(), _player.x, _player.y, _player.playerAni, 100);
		_player.weaponImage->aniAlphaRender(CAMERAMANAGER->getWorldDC(), _player.weaponX, _player.weaponY, _player.weaponAni, 100);
	}
	
	//_player.playerImage->aniRender(CAMERAMANAGER->getWorldDC(), _player.x, _player.y, _player.playerAni);
	//_player.weaponImage->aniRender(CAMERAMANAGER->getWorldDC(), _player.weaponX, _player.weaponY, _player.weaponAni);



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

void player::setDirection()
{
	if (WINSIZEX / 2 < _ptMouse.x)
	{
		_tempDirection = DIRECTION::RIGHT;
	}
	else if (WINSIZEX / 2 >= _ptMouse.x)
	{
		_tempDirection = DIRECTION::LEFT;
	}

	if (_tempDirection != _player.direc)
	{
		if (_tempDirection == DIRECTION::LEFT)
		{
			_player.imageDirection = 0;
			_player.direc = _tempDirection;
			_state->changeImage(_player.imageDirection);
			
		}
		else
		{
			_player.imageDirection = 1;
			_player.direc = _tempDirection;
			_state->changeImage(_player.imageDirection);
		}
	}
}

void player::KeyControl()
{
	if (_player.weaponAni->getNowPlayNum() == _player.weaponAni->getFrameMaxFrame()-1) _player.isAttack = false;
	//공격키
	if (!_player.isAttack)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !UIMANAGER->getOption())
		{
			_player.weaponAni->start();
	/*		ITEMMANAGER->Dropitem(OBJECT::IRON, _player.x, _player.y);
			ITEMMANAGER->DropForgeItem(FORGERECIPE::KEY, _player.x, _player.y,1);*/
			ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::GOLD, _player.x, _player.y, 1);
			ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::IRON, _player.x, _player.y, 1);

			KEYMANAGER->setKeyDown(VK_LBUTTON, false);
			cout << "player health: " << _player.health << endl;
		

		}
	}

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

	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		this->playerHit();
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
	//가속도
	if (_player.acel >= 2) return;
	_player.acel += 0.05;
}

void player::setPlayerXY(int idx, int idy)
{
	_player.x = idx * 60 + 30;
	_player.y = idy * 60 + 30;
	_player.weaponX = _player.x - 15;
	_player.weaponY = _player.y - 5;
	CAMERAMANAGER->setCameraInit(_player.x, _player.y);
	_player.rc = RectMake(_player.x, _player.y, _player.playerImage->getFrameWidth(), _player.playerImage->getFrameHeight());


}

void player::setPlayerExpMax(int level)
{
	_player.level++;
	_player.exp = _player.exp - _player.expMax;
	_player.expMax = _player.level * 30;
}

void player::playerExp(int exp)
{
	_player.exp += exp;

	//만약 획득한 경험치가 MAX값에 도달하면 
	if (_player.exp >= _player.expMax)
	{
		//레벨 증가 시킨다.
		_player.skillPount++;
		this->setPlayerExpMax(_player.level);
	}
}

void player::playerHealth(int health)
{
	//체력을 감소시킨다.
	_player.health -= health;
	// 체력은 0보다 작으면 0으로 고정 
	if (_player.health <= 0)
	{
		_player.health = 0;
	}
}

void player::playerHitCount()
{
	if (!_player.isHit) return;

	_player.hitCount++;
	if (_player.hitCount % 5 == 0 )
	{
		if (_player.alpha > 0)
		{
			_player.alpha = 0;
		}
		else
		{
			_player.alpha = 100;
		}
	}

	if (_player.hitCount >=50)
	{
		_player.isHit = false;
		_player.hitCount = 0;
	}
}

void player::playerHit()
{
	if (_player.isHit)	return;
		
	_player.isHit = true;		
	_player.hp--;

}



