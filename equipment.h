#pragma once
#include "stdafx.h"

class equipment
{

public:
	equipment();
	~equipment();

	HRESULT init();
	void release();
	void update();
	void render();
};

