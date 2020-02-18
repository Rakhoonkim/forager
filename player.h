#pragma once
#include "gameNode.h"
#include "animation.h"
#include "playerState.h"

class player : public gameNode
{
private:
	//플레이어 상태
	playerState* _state;
	playerIdle* _playerIdle;
	playerMove* _playerMove;

	tagPlayer _player;

	int		_keyCount;  // KEY 2개 눌리지않기
	bool _stateChange;	// 상태변경 BOOL값
public:

	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	void KeyControl();		// KEY
	void IndexUpdate();		// PLAYER INDEX 업데이트
	void acelPlus();
	tagPlayer get_PlayerAddressLinK() { return _player; }
	tagPlayer* get_PlayerAddress() { return &_player; }
	RECT get_playerRect() { return _player.rc; }
};


