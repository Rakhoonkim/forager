#pragma once
#include "stdafx.h"

class bullet
{
private:
	vector<tagBullet*>			   _vBullet;
	vector<tagBullet*>::iterator  _viBullet;

	const char* _imageName;
public:
	bullet();
	~bullet();

	HRESULT init(const char* imageName);
	void release();
	void update();
	void render();

	void move();    //이동
	void remove();  //삭제

	void fire(float x, float y, float angle, float speed);
	void fire(float x, float y, float angle, float speed ,float distance);

	vector<tagBullet*> getVBullet()				{ return _vBullet; }
	vector<tagBullet*>::iterator getViBullet() { return _viBullet; }
};

