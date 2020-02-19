#pragma once
#include "stdafx.h"
#include "bullet.h"

class bulletManager
{
private:
	vector<bullet*>				_vBullet;
	vector<bullet*>::iterator  _viBullet;

public:
	bulletManager();
	~bulletManager();

	HRESULT init();
	void update();
	void release();
	void render();

	void remove();
	void fire(const char* imageName, float x, float y, float angle, float speed);
};

