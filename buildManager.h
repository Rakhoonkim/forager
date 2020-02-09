#pragma once
#include "gameNode.h"
class buildManager :public gameNode
{
public:
	buildManager();
	~buildManager();
	HRESULT init();
	void release();
	void update();
	void render();
};

