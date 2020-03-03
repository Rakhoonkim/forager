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

	temple*				  _temple;  // ���� ������Ʈ

	bulletManager* _bulletManager;	// �Ѿ� �Ŵ���

	tagBlind		_room[8];  // 8���� ĭ����
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

	//���� ������Ʈ ����
	void CreateCannon(int idx, int idy, int frameX);
	void CreateLantern(int idx, int idy);
	void CreateDoor(int idx, int idy, int frameX);

	void setBulletManager(bulletManager* bullet)		 { _bulletManager = bullet; }
	void setPlayer(tagPlayer* player)					 { _player = player; }

	bool getBossAttack()								 { return _room[0].isOpen; }
};

