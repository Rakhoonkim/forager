#pragma once
#include "stdafx.h"

class equipment
{
private:
	tagButton _skillButton;		// ��ų��ư
	tagButton _featButton;		// ������ư 

	tagButton _weaponButton[11]; // ���� �� ����
	tagButton _equipButton[6];  // ��ű�
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

