#pragma once
#include "playerManager.h"
#include "gameNode.h"

class stageScene : public gameNode
{
private:
	playerManager* _playerManager;
public:
	stageScene() {}
	~stageScene() {}

	HRESULT init();
	void release();
	void update();
	void render();
};

