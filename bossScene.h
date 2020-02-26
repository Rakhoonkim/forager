#pragma once
#include "stdafx.h"
#include "gameNode.h"
#include "playerManager.h"

class bossScene : public gameNode
{
private:
	playerManager* _playerManager;

public:
	bossScene();
	~bossScene();

	HRESULT init();
	void release();
	void update();
	void render();

};

