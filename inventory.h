#pragma once
#include "stdafx.h"

#define INVENX 8
#define INVENY 3
class inventory 
{
private:
	map<string, tagInven>			 _mInven;
	map<string, tagInven>::iterator  _miInven;

	tagInven _inven[INVENX * INVENY];
	int _invenSize;

public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();
	void render(HDC hdc);

	void addInven(string imageName,int frameX, int frameY);

	void invenSetting();
};

