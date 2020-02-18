#pragma once
#include "gameNode.h"
#include "cropsManager.h"
#include "buildManager.h"
#include "enemyManager.h"

class playerManager;

class objectManager : public gameNode
{

private:
	cropsManager* _cropsManager;  //cropsManager   
	buildManager* _buildManager;  //buildManager
	enemyManager* _enemyManager;  //enemyManager

public:
	objectManager();
	~objectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	cropsManager* get_CropsManager() { return _cropsManager; }
	buildManager* get_buildManager() { return _buildManager; }
	enemyManager* get_enemyManager() { return _enemyManager; }

};

