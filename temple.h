#pragma once
#include "stdafx.h"
#include "bulletManager.h"

class temple
{
protected:
	tagTempleObject _temp;
	bulletManager* _bulletManager;
public:
	temple();
	~temple();

	virtual	HRESULT init(const char* imageName, int idx, int idy);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setFrameX(int frameX) { _temp.frameX = frameX; }
	virtual void setBulletManager(bulletManager* bullet) { _bulletManager = bullet; }
};


class lantern : public temple
{

public:
	lantern() {}
	~lantern() {}

	HRESULT init(const char* imageName, int idx, int idy);
	void render();
};


class cannon : public temple
{
public:
	cannon() {}
	~cannon() {}
	void update();
	void setFrameX(int frameX);
	void render();
};

class door : public temple
{
public:
	door() {}
	~door() {}
	void render();
};