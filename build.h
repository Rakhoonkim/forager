#pragma once
#include "stdafx.h"

#define MAXLIST 4
#define MAXINDUSTRY 3
#define MAXFARMING 2

class build
{
private:
	tagButton _buildList[MAXLIST];

	tagButton _industryList[MAXINDUSTRY];
	tagButton _farmingList[MAXFARMING];


	int _listHeight; // 리스트의 세로 
	int _listWidth;  // 리스트의 가로 

	int _direction;  // 가리키고 있는 버튼 
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

	void setDirection() { _direction = 5; }//임의의 NULL값 
};

