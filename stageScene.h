#pragma once
#include "playerManager.h"
#include "objectManager.h"
#include "buildManager.h"

#include "gameNode.h"

class stageScene : public gameNode
{
private:
	playerManager* _playerManager;
	objectManager* _objectManager;
	buildManager* _buildManager;
public:
	stageScene() {}
	~stageScene() {}

	HRESULT init();
	void release();
	void update();
	void render();
};

