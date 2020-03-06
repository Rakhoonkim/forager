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
	_stateChange = false;

	_player.playerImage = IMAGEMANAGER->findImage("playerIdle");
	_player.playerAni = KEYANIMANAGER->findAnimation("playerIdle_R");

	_player.weaponImage = IMAGEMANAGER->findImage("playerPick");
	_player.weaponAni = KEYANIMANAGER->findAnimation("playerPick_R");

	_player.playerAni->start();

	_keyCount = 0;   // 입력 가능한 키

	_tempDirection = DIRECTION::RIGHT;

	_player.direc = DIRECTION::RIGHT;
	_player.angle = 0;

	_player.idx = 22;
	_player.idy = 18;

	_player.x = _player.idx * 60 + (_player.playerImage->getFrameWidth() / 2);
	_player.y = _player.idy * 60 + (_player.playerImage->getFrameHeight() / 2);

	_player.weaponX = _player.x -15;
	_player.weaponY = _player.y -5;

	_player.imageDirection = 0;				 //(0 : 왼쪽, 1: 오른쪽)

	_player.speed = 5;		 // 속도
	_player.accel = 1.1;	 // 가속도(1.1~2)(최소값~최대값)
	_player.hp = 3;			 // 생명력 3
	_player.maxHp = 3;		 // 최대생명력 3
	_player.health = 100;    // 체력
	_player.damage = 1;		 // 공격력
	_player.level = 1;		 // 레벨
	_player.expMax = 30;	 // 경험치 최대값
	_player.exp = 0;		 // 현재 경험치
	_player.skillPount = 0;  // 스킬포인트
	_player.alpha = 0;		 // 알파값
	_player.hitCount = 0;	 // 맞을 때 카운터 
	_player.isHit = false;	 // 맞을 떄
	_player.isAttack = false;// 공격
	_player.rc = RectMake(_player.x, _player.y, _player.playerImage->getFrameWidth(), _player.playerImage->getFrameHeight());  // RECT 초기화

	//상태
	_state = new playerState();
	_state->init(&_player);
	_playerMove = new playerMove(&_player);		// 이동
	_playerIdle = new playerIdle(&_player);     // 대기
	_state = _playerIdle;			 // 현재 상태는 대기

	_healthTime = TIMEMANAGER->getWorldTime();	// 체력 재생 시간 

	CAMERAMANAGER->setCameraInit(_player.x, _player.y);  // 카메라 세팅
	MAPMANAGER->setPlayerAddress(&_player);				 // MAP 충돌 플레이어 셋팅
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_state->update();  // 상태 
	KeyControl();	   // KEY
	IndexUpdate();	   // INDEX
	//setDirection();
	playerHitCount();  // 맞을 때 
	playerHealth();    // 체력 재생

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
	
	//디비깅용
	//Rectangle(CAMERAMANAGER->getWorldDC(), _player.rc);
	//각도 인덱스
	//char str[100];
	//sprintf_s(str, "%f", _state->getAngle());
	//TextOut(CAMERAMANAGER->getWorldDC(), _player.x, _player.y+50, str, strlen(str));
	//char strIdx[100];
	//sprintf_s(strIdx, "idx : %d", _player.idx);
	//TextOut(CAMERAMANAGER->getWorldDC(), _player.x, _player.y, strIdx, strlen(strIdx));
	//char strIdy[100];
	//sprintf_s(strIdy, "idy : %d", _player.idy);
	//TextOut(CAMERAMANAGER->getWorldDC(), _player.x+ 100, _player.y, strIdy, strlen(strIdy));
}

//(현재 사용안함)
//마우스의 위치에 따라 케릭터의 방향을 바꾸기 위한 함수 
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

//방향키 
void player::KeyControl()
{
	//공격 모션이 끝나면
	if (_player.weaponAni->getNowPlayNum() == _player.weaponAni->getFrameMaxFrame() - 1)
	{
		_player.isAttack = false;
	}

	//공격키
	if (!_player.isAttack)
	{
		//옵션 창이 아니면
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !UIMANAGER->getOption())
		{
			_player.weaponAni->start();  // 공격 모션 	

			_player.isAttack = true;
			KEYMANAGER->setKeyDown(VK_LBUTTON, false);
		}
	}

	//아이템 키 
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		ITEMMANAGER->Dropitem(OBJECT::GOLD, _player.x, _player.y);
		ITEMMANAGER->Dropitem(OBJECT::COAL, _player.x, _player.y);
		ITEMMANAGER->Dropitem(OBJECT::IRON, _player.x, _player.y);
		ITEMMANAGER->Dropitem(OBJECT::ROCK, _player.x, _player.y);
		ITEMMANAGER->Dropitem(OBJECT::ROCK, _player.x, _player.y);
		ITEMMANAGER->Dropitem(OBJECT::COTTON, _player.x, _player.y);
		ITEMMANAGER->Dropitem(OBJECT::COTTON, _player.x, _player.y);
		ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::BRICK, _player.x, _player.y,1);
		ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::GOLD, _player.x, _player.y, 1);
		ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::BRICK, _player.x, _player.y, 1);
		ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::BRICK, _player.x, _player.y, 1);
		ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::IRON, _player.x, _player.y, 1);
		ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::BRICK, _player.x, _player.y, 1);
		ITEMMANAGER->Dropitem(OBJECT::ROCK, _player.x, _player.y);
		ITEMMANAGER->Dropitem(TREE::BASIC, _player.x, _player.y);
		ITEMMANAGER->Dropitem(TREE::BASIC, _player.x, _player.y);
		ITEMMANAGER->Dropitem(TREE::BASIC, _player.x, _player.y);
		ITEMMANAGER->Dropitem(OBJECT::BUSH, _player.x, _player.y);
		ITEMMANAGER->DropForgeItem(FORGERECIPE::COIN, _player.x, _player.y,1);
		ITEMMANAGER->DropForgeItem(FORGERECIPE::COIN, _player.x, _player.y, 1);
		ITEMMANAGER->DropForgeItem(FORGERECIPE::COIN, _player.x, _player.y, 1);
		ITEMMANAGER->DropForgeItem(FORGERECIPE::COIN, _player.x, _player.y, 1);
		ITEMMANAGER->DropForgeItem(FORGERECIPE::COIN, _player.x, _player.y, 1);
		ITEMMANAGER->DropForgeItem(FORGERECIPE::COIN, _player.x, _player.y, 1);
		ITEMMANAGER->DropForgeItem(FORGERECIPE::COIN, _player.x, _player.y, 1);
	/*	ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::COAL, _player.x, _player.y, 1);
		ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::GOLD, _player.x, _player.y, 1);
		ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::IRON, _player.x, _player.y, 1);
		ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::IRON, _player.x, _player.y, 1);
		ITEMMANAGER->DropFurnaceItem(FURNACERECIPE::IRON, _player.x, _player.y, 1);*/
	}

	//키가 두개 눌리면 리턴
	if (_keyCount > 2) return;

	//위 
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
			_player.accel = 1;
		}
		accelControl();
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
			_player.accel = 1;
		}
		accelControl();
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
			_player.accel = 1;
		}
		accelControl();
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
			_player.accel = 1;
		}
		accelControl();
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

//인덱스 업데이트
void player::IndexUpdate()
{
	CAMERAMANAGER->setCameraXY(_player.x, _player.y);
	_player.idx = (int)(_player.x + 30) / 60;
	_player.idy = (int)(_player.y + 30) / 60;	
}

//가속도
void player::accelControl()
{
	//가속도
	if (_player.accel >= 2) return;
	_player.accel += 0.05;
}

//플레이어의 위치를 갱신
void player::setPlayerXY(int idx, int idy)
{
	//플레이어
	_player.x = idx * 60 + _player.playerImage->getFrameWidth() / 2;
	_player.y = idy * 60 + _player.playerImage->getFrameHeight() / 2;
	//무기
	_player.weaponX = _player.x - 15;
	_player.weaponY = _player.y - 5;
	//RECT
	_player.rc = RectMake(_player.x, _player.y, _player.playerImage->getFrameWidth(), _player.playerImage->getFrameHeight());
	//카메라
	CAMERAMANAGER->setCameraInit(_player.x, _player.y);
}

//레벨 갱신
void player::setPlayerExpMax(int level)
{
	_player.level++;
	_player.exp = _player.exp - _player.expMax;
	_player.expMax = _player.level * 30;
}
//경험치 증가
void player::setPlayerExp(int exp)
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
//체력 재생
void player::setPlayerHealth(int health)
{
	//체력을 감소시킨다.
	_player.health -= health;  
	// 체력은 0보다 작으면 0으로 고정 
	if (_player.health <= 0)
	{
		_player.health = 0;
	}
}

//맞을 때 시간 
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
		else _player.alpha = 100;
	}

	//count가 50이 넘으면 false
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
	_player.hp--;			// 맞으면 체력을 감소
}

//체력 재생
void player::playerHealth()
{
	if (_healthTime + 10 <= TIMEMANAGER->getWorldTime())
	{
		//시간 갱신
		_healthTime = TIMEMANAGER->getWorldTime();
		//체력이 낮으면 회복
		if (_player.health <= 50)
		{
			_player.health += 10;
		}
	}
}
