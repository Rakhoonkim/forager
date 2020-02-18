#pragma once
#include "gameNode.h"
#include "animation.h"
#include "playerState.h"

class player : public gameNode
{
private:
	//�÷��̾� ����
	playerState* _state;
	playerIdle* _playerIdle;
	playerMove* _playerMove;

	tagPlayer _player;

	int		_keyCount;  // KEY 2�� �������ʱ�
	bool _stateChange;	// ���º��� BOOL��
public:

	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	void KeyControl();		// KEY
	void IndexUpdate();		// PLAYER INDEX ������Ʈ
	void acelPlus();
	tagPlayer get_PlayerAddressLinK() { return _player; }
	tagPlayer* get_PlayerAddress() { return &_player; }
	RECT get_playerRect() { return _player.rc; }
};


