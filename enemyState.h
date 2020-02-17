#pragma once
#include "stdafx.h"

class enemyState
{
private:
	tagObject* _enemy;
public:
	enemyState(tagObject* enemy);
	~enemyState();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();
};

