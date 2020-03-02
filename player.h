#pragma once
#include "gameNode.h"
#include "animation.h"
#include "playerState.h"

class player : public gameNode
{
private:
	//플레이어 상태
	playerState*	 _state;		// 상태 
	playerIdle* _playerIdle;		// 대기
	playerMove* _playerMove;		// 이동
	tagPlayer	    _player;		// 플레이어


	DIRECTION	_tempDirection;	 //이전 방향을 확인하기 위한  
	float		   _healthTime;  //체력 재생 회복
	int	             _keyCount;  //KEY 2개 눌리지않기 위한 
	bool		  _stateChange;	 //상태변경 BOOL값
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	void setDirection();    // 사용안함

	void KeyControl();		// KEY
	void accelControl();	// ACEL
	void IndexUpdate();		// PLAYER INDEX 업데이트

	void setPlayerXY(int idx, int idy);		// 플레이어 XY 세팅
	void setPlayerExpMax(int expMax);	    // 최대 경험치 세팅
	void setPlayerExp(int exp);			    // 경험치 추가
	void setPlayerHealth(int health);		// 체력 

	void playerHit();
	void playerHitCount();
	void playerHealth();

	RECT get_playerRect()				 { return _player.rc; }
	tagPlayer get_PlayerAddressLinK()	 { return _player; }
	tagPlayer* get_PlayerAddress()		 { return &_player; }
};


