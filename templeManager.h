#pragma once
#include "stdafx.h"
#include "temple.h"
#include "bulletManager.h"

struct tagBlind
{
	RECT rc;
	float width, height;
	bool isOpen;
};

class templeManager
{
private:
	vector<temple*>			   _vTemple;
	vector<temple*>::iterator _viTemple;

	temple*				  _temple;  // 던전 오브젝트

	bulletManager* _bulletManager;	// 총알 매니저

	tagBlind		_room[8];  // 8개의 칸막이
	tagPlayer*		 _player;

public:
	templeManager();
	~templeManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void blindRoomSetting();
	void blindRoomCollision();

	void imageSetting();

	//던전 오브젝트 생성
	void CreateCannon(int idx, int idy, int frameX);
	void CreateLantern(int idx, int idy);
	void CreateDoor(int idx, int idy, int frameX);

	void setBulletManager(bulletManager* bullet)		 { _bulletManager = bullet; }
	void setPlayer(tagPlayer* player)					 { _player = player; }

	bool getBossAttack()								 { return _room[0].isOpen; }
};

