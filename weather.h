#pragma once
#include "stdafx.h"

class weather
{
private:
	float _time;
	int _alpha;


	bool _night;
public:
	weather();
	~weather();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
};

