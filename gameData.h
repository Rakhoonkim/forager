#pragma once
#include "stdafx.h"
#include "singletonBase.h"

class playerManager;
class objectManager;

class gameData : public singletonBase<gameData>
{
private:
	playerManager* _playerManager;
	objectManager* _objectManager;

public:
	gameData();
	~gameData();

	HRESULT init();
	void release();
	void update();
	void render();

	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	playerManager* getPlayerManager() { return _playerManager; }

	void setObjectManager(objectManager* objectManager) { _objectManager = objectManager; }
	objectManager* getObjectManager() { return _objectManager; }
};

