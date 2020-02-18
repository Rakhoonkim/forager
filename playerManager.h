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
	buildManager* _buildManager;
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
	void objectCollisionMouse();	  // ���콺 Ŀ�� ���̱� 
	
	void optionControl();

	void objectAttack(int num);		  // �����ϱ� 
	void set_CropsManager(cropsManager* cropsManager) { _cropsManager = cropsManager; }
	void set_BuildManager(buildManager* buildManager) { _buildManager = buildManager; }

	player* get_player() { return _player; }
};

