#pragma once
#include "stdafx.h"

class equipment
{
private:
	tagButton _skillButton;		// 스킬버튼
	tagButton _featButton;		// 위업버튼 

	tagButton _weaponButton[11]; // 도구 및 무기
	tagButton _equipButton[6];  // 장신구
	tagButton _sealButton[9];
	tagButton _treasureButton[15];


public:
	equipment();
	~equipment();

	HRESULT init();
	void release();
	void update();
	void render();
	void render(HDC hdc);

	void buttonSetting();
};

