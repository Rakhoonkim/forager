#pragma once
#include "gameNode.h"
#include "cropsManager.h"



class objectManager : public gameNode
{

private:
	cropsManager* _cropsManager;  //cropsManager   

public:
	objectManager();
	~objectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	cropsManager* get_CropsManager() { return _cropsManager; }
};

