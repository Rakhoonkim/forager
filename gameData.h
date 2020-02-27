#pragma once
#include "stdafx.h"
#include "singletonBase.h"

class playerManager;
class objectManager;
class enemyManager;
class templeManager;

class gameData : public singletonBase<gameData>
{
private:
	playerManager* _playerManager;
	objectManager* _objectManager;
	templeManager* _templeManager;
	enemyManager* _enemyManager; //  보스 씬에 있는 
public:
	gameData();
	~gameData();

	HRESULT init();
	void release();
	void update();
	void render();

	void save();
	void load();

	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	playerManager* getPlayerManager() { return _playerManager; }

	void setObjectManager(objectManager* objectManager) { _objectManager = objectManager; }
	objectManager* getObjectManager() { return _objectManager; }

	void setEnemyManager(enemyManager* enemyManager) { _enemyManager = enemyManager; }
	enemyManager* getEnemyManager() { return _enemyManager; }

	void setTempleManager(templeManager* templeManager) { _templeManager = templeManager; }
	templeManager* getTempleManager() { return _templeManager; }
};

