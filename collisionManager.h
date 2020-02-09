#pragma once
#include "stdafx.h"
#include "singletonBase.h"

class collisionManager: public singletonBase<collisionManager>
{
private:


public:
	collisionManager();
	~collisionManager();

	HRESULT init();
	void release();
	void update();
	void render();

};

