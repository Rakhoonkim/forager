#pragma once
#include "stdafx.h"

#define MAXLIST 4
#define MAXINDUSTRY 3
#define MAXFARMING 2
class buildManager;

class build
{
private:
	tagButton _buildList[MAXLIST];

	tagButton _industryList[MAXINDUSTRY];
	tagButton _farmingList[MAXFARMING];


	int _listHeight; // 리스트의 세로 
	int _listWidth;  // 리스트의 가로 

	int _direction;  // 리스트 가리키고 있는 버튼 
	int _buildingDirection;  // 지을 건물을 가리키고 있는 버튼 
	int _farmingDirection;

	buildManager* _buildManager;  // 건축하기 위한 
	bool _isBuilding;

public:
	build();
	~build();

	HRESULT init();
	void release();
	void update();
	void render();
	void render(HDC hdc);

	void buttonClick();
	void listOpen();

	void industryCheck();
	void farmingCheck();
	void buildingCheck();

	bool getisBuilding() { return _isBuilding; }
	void setisBuilding() { _isBuilding = false; }
	void setClickInit();		//산업 농경 클릭을 초기화 

	void setDirection() { _direction = 5; }//임의의 NULL값 

	void isClickBuild();
	void setBuildManager(buildManager* buildManager) { _buildManager = buildManager; }
};

