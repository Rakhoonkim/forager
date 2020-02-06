#pragma once
#include "gameNode.h"
#include "animation.h"
#include "playerState.h"
// 플레이어의 상태를 나누자 
// IDLE
// MOVE
// JUMP
// ATTACK

class player : public gameNode
{
private:
	playerState* _state;

	playerIdle* _playerIdle;
	playerMove* _playerMove;


	tagPlayer _player;

	bool _stateChange;
public:

	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	void KeyControl();
	tagPlayer* get_PlayerAddress() { return &_player; }
};


