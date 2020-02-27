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


	DIRECTION _tempDirection;		// 이전 방향을 확인 
	float _healthTime;
	int		_keyCount;  // KEY 2개 눌리지않기
	bool _stateChange;	// 상태변경 BOOL값
public:

	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	void setDirection();
	void KeyControl();		// KEY
	void IndexUpdate();		// PLAYER INDEX 업데이트
	void acelPlus();

	void setPlayerXY(int idx, int idy);		// 보스씬 들어갈때

	void setPlayerExpMax(int expMax);
	void playerExp(int exp);
	void playerHealth(int health);

	void playerHitCount();
	void playerHit();
	void playerHealth();
	tagPlayer get_PlayerAddressLinK() { return _player; }
	tagPlayer* get_PlayerAddress() { return &_player; }
	RECT get_playerRect() { return _player.rc; }
};


