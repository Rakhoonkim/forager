#pragma once
#include "stdafx.h"
#include "gameNode.h"
#include "building.h"

class buildManager: public gameNode
{
private: 
	vector<building*>				_vBuilding;
	vector<building*>::iterator   _viBuilding;

public:
	buildManager();
	~buildManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();
	
	void createImageBuilding(BUILDING build,int idx, int idy);
	void createFrameBuilding(BUILDING build, int idx, int idy);


	vector<building*>				 getVBuild() { return _vBuilding; }
	vector<building*>::iterator   getViBuild() { return _viBuilding; }

	void removeBuilding();
};

