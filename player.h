#pragma once
#include "gameNode.h"
#include "animation.h"
#include "playerState.h"

class player : public gameNode
{
private:
	//�÷��̾� ����
	playerState*	 _state;		// ���� 
	playerIdle* _playerIdle;		// ���
	playerMove* _playerMove;		// �̵�
	tagPlayer	    _player;		// �÷��̾�


	DIRECTION	_tempDirection;	 //���� ������ Ȯ���ϱ� ����  
	float		   _healthTime;  //ü�� ��� ȸ��
	int	             _keyCount;  //KEY 2�� �������ʱ� ���� 
	bool		  _stateChange;	 //���º��� BOOL��
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	void setDirection();    // ������

	void KeyControl();		// KEY
	void accelControl();	// ACEL
	void IndexUpdate();		// PLAYER INDEX ������Ʈ

	void setPlayerXY(int idx, int idy);		// �÷��̾� XY ����
	void setPlayerExpMax(int expMax);	    // �ִ� ����ġ ����
	void setPlayerExp(int exp);			    // ����ġ �߰�
	void setPlayerHealth(int health);		// ü�� 

	void playerHit();
	void playerHitCount();
	void playerHealth();

	RECT get_playerRect()				 { return _player.rc; }
	tagPlayer get_PlayerAddressLinK()	 { return _player; }
	tagPlayer* get_PlayerAddress()		 { return &_player; }
};


