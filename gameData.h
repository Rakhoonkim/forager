#pragma once
#include "stdafx.h"
#include "singletonBase.h"
#include "Zorder.h"
class playerManager;
class objectManager;
class enemyManager;
class templeManager;
class Zoder;

class gameData : public singletonBase<gameData>
{
private:
	playerManager*		 _playerManager; //STAGE PLAYER
	objectManager*		 _objectManager; //STAGE OBJECT
	templeManager*		 _templeManager; //STAGE
	enemyManager*         _enemyManager; //º¸½º ¾À ENEMY

	vector<ZorderObject*>      _vZOrder; //ZORDER STAGE->BOSS °¥¶§ ÀúÀå
										 //		   BOSS->STAGE ¹Þ¾Æ¿È

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

	void setZorder(vector<ZorderObject*> vZorder) { _vZOrder = vZorder; }
	vector<ZorderObject*> getZorder() { return _vZOrder; }
};

