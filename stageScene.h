#pragma once
#include "playerManager.h"
#include "objectManager.h"

#include "gameNode.h"

class stageScene : public gameNode
{
private:
	playerManager* _playerManager;		//PLAYER
	objectManager* _objectManager;		//OBJECT
	//ENEMYMANAGER ¿¹Á¤
public:
	stageScene() {}
	~stageScene() {}

	HRESULT init();
	void release();
	void update();
	void render();
};

