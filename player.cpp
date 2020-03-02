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

	_keyCount = 0;   // �Է� ������ Ű

	_tempDirection = DIRECTION::RIGHT;

	_player.direc = DIRECTION::RIGHT;
	_player.angle = 0;

	_player.idx = 22;
	_player.idy = 18;

	_player.x = _player.idx * 60 + (_player.playerImage->getFrameWidth() / 2);
	_player.y = _player.idy * 60 + (_player.playerImage->getFrameHeight() / 2);

	_player.weaponX = _player.x -15;
	_player.weaponY = _player.y -5;

	_player.imageDirection = 0;				 //(0 : ����, 1: ������)

	_player.speed = 5;		 // �ӵ�
	_player.accel = 1.1;	 // ���ӵ�(1.1~4)(�ּҰ�~�ִ밪)
	_player.hp = 3;			 // ����� 3
	_player.maxHp = 3;		 // �ִ����� 3
	_player.health = 100;    // ü��
	_player.damage = 1;		 // ���ݷ�
	_player.level = 1;		 // ����
	_player.expMax = 30;	 // ����ġ �ִ밪
	_player.exp = 0;		 // ���� ����ġ
	_player.skillPount = 0;  // ��ų����Ʈ
	_player.alpha = 0;		 // ���İ�
	_player.hitCount = 0;	 // ���� �� ī���� 
	_player.isHit = false;	 // ���� ��
	_player.isAttack = false;// ����

	//����
	_state = new playerState();
	_state->init(&_player);
	_playerMove = new playerMove(&_player);		// �̵�
	_playerIdle = new playerIdle(&_player);     // ���

	_state = _playerIdle;		// ���� ���´� ���
	_stateChange = false;

	_player.rc = RectMake(_player.x, _player.y, _player.playerImage->getFrameWidth(), _player.playerImage->getFrameHeight());

	_healthTime = TIMEMANAGER->getWorldTime();	// ü�� ��� �ð� 

	CAMERAMANAGER->setCameraInit(_player.x, _player.y);  // ī�޶� ����
	MAPMANAGER->setPlayerAddress(&_player);				 // MAP �浹 �÷��̾� ����
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_state->update();  // ���� 
	KeyControl();	   // KEY
	IndexUpdate();	   // INDEX
	//setDirection();
	playerHitCount();  // ���� �� 
	playerHealth();    // ü�� ���

	MAPMANAGER->setPlayerAddress(&_player);
	MAPMANAGER->setPlayerStageTileColision(_player.idx, _player.idy);  // �浹ó�� 
	
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
	
	//�����
	//Rectangle(CAMERAMANAGER->getWorldDC(), _player.rc);
	//���� �ε���
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

//���� ������
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

//����Ű 
void player::KeyControl()
{
	//���� ����� ������
	if (_player.weaponAni->getNowPlayNum() == _player.weaponAni->getFrameMaxFrame() - 1)
	{
		_player.isAttack = false;
	}

	//����Ű
	if (!_player.isAttack)
	{
		//�ɼ� â�� �ƴϸ�
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !UIMANAGER->getOption())
		{
			_player.weaponAni->start();  // ���� ��� 	

			_player.isAttack = true;
			KEYMANAGER->setKeyDown(VK_LBUTTON, false);
		}
	}

	//������ Ű 
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		/*ITEMMANAGER->Dropitem(OBJECT::GOLD, _player.x, _player.y);
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
		ITEMMANAGER->Dropitem(OBJECT::BUSH, _player.x, _player.y);*/
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


	//Ű�� �ΰ� ������ 
	if (_keyCount > 2) return;

	//�� 
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

void player::IndexUpdate()
{
	CAMERAMANAGER->setCameraXY(_player.x, _player.y);
	_player.idx = (int)(_player.x + 30) / 60;
	_player.idy = (int)(_player.y + 30) / 60;	
}

void player::accelControl()
{
	//���ӵ�
	if (_player.accel >= 2) return;
	_player.accel += 0.05;
}

void player::setPlayerXY(int idx, int idy)
{
	_player.x = idx * 60 + _player.playerImage->getFrameWidth() / 2;
	_player.y = idy * 60 + _player.playerImage->getFrameHeight() / 2;
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

void player::setPlayerExp(int exp)
{
	_player.exp += exp;

	//���� ȹ���� ����ġ�� MAX���� �����ϸ� 
	if (_player.exp >= _player.expMax)
	{
		//���� ���� ��Ų��.
		_player.skillPount++;
		this->setPlayerExpMax(_player.level);
	}
}

void player::setPlayerHealth(int health)
{
	//ü���� ���ҽ�Ų��.
	_player.health -= health;  // �ӽ�
	// ü���� 0���� ������ 0���� ���� 
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

void player::playerHealth()
{
	if (_healthTime + 10 <= TIMEMANAGER->getWorldTime())
	{
		_healthTime = TIMEMANAGER->getWorldTime();
		if (_player.health <= 50)
		{
			_player.health += 10;
		}
	}
}



