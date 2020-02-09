#pragma once
#include "gameNode.h"
#include "player.h"


class cropsManager;
class buildManager;


class playerManager: public gameNode
{
private:
	player* _player;
	cropsManager* _cropsManager;

public:
	playerManager() {}
	~playerManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();

	void objectCollisionMouse();  // ���콺 Ŀ�� ���̱� 
	void objectAttack(int num);		  // �����ϱ� 
	void set_CropsManager(cropsManager* cropsManager) { _cropsManager = cropsManager; }
};

