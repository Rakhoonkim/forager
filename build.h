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


	int _listHeight; // ����Ʈ�� ���� 
	int _listWidth;  // ����Ʈ�� ���� 

	int _direction;  // ����Ű�� �ִ� ��ư 
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

	void setDirection() { _direction = 5; }//������ NULL�� 
};

