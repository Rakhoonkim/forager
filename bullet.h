#pragma once
#include "stdafx.h"

class bullet
{
private:
	const char* _imageName;
	tagBullet _bullet;
	int _count;
	float _angle;
public:
	bullet();
	~bullet();

	HRESULT init(const char* imageName, float x, float y, float angle, float speed);
	void release();
	void update();
	void render();
	void move();

	tagBullet* getBullet()  { return &_bullet;}
};

