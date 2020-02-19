#pragma once
#include "stdafx.h"
#include "bullet.h"

class bulletManager
{
private:
	bullet*		_bullet;

public:
	bulletManager();
	~bulletManager();

	HRESULT init();
	void update();
	void release();
	void render();

	bullet* getBullet() { return _bullet; }
};

