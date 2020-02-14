#pragma once
#include "gameNode.h"
#include "cropsManager.h"
#include "buildManager.h"


class objectManager : public gameNode
{

private:
	cropsManager* _cropsManager;  //cropsManager   
	buildManager* _buildManager;  //buildManager
public:
	objectManager();
	~objectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	cropsManager* get_CropsManager() { return _cropsManager; }
	buildManager* get_buildManager() { return _buildManager; }
};

