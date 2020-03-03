#pragma once
#include "stdafx.h"
#include "gameNode.h"
#include "building.h"

class buildManager: public gameNode
{
private: 
	vector<building*>				_vBuilding;
	vector<building*>::iterator    _viBuilding;

	bool _isUsed;
public:
	buildManager();
	~buildManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();   // 이미지 세팅
	
	void createImageBuilding(BUILDING build,int idx, int idy);
	void createFrameBuilding(BUILDING build, int idx, int idy);
	
	//접근자 
	vector<building*>				 getVBuild() { return _vBuilding; }
	vector<building*>::iterator     getViBuild() { return _viBuilding; }

	bool usedCheck();       //사용중인지를 판단하기 위한 Bool
	void removeBuilding();  // 건축물 삭제
};

