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

	bool _isOption;
public:
	playerManager() {}
	~playerManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();

	void itemCollisionPlayer();
	void itemCollisionMouse();
	void objectCollisionMouse();	  // 마우스 커서 보이기 
	
	void optionControl();

	void objectAttack(int num);		  // 공격하기 
	void set_CropsManager(cropsManager* cropsManager) { _cropsManager = cropsManager; }
};

