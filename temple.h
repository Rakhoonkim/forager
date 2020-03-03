#pragma once
#include "stdafx.h"
#include "bulletManager.h"

class temple
{
protected:
	tagTempleObject		    _temple;  //TEMPLE

	bulletManager*   _bulletManager;  //BULLETMANAGER
public:
	temple();
	~temple();

	virtual	HRESULT init(const char* imageName, int idx, int idy);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setFrameX(int frameX)				     { _temple.frameX = frameX; }   //프레임X 
	virtual void setBulletManager(bulletManager* bullet) { _bulletManager = bullet; }   //총알매니저
	virtual RECT getRect()								 { return _temple.rc; }         //RECT
};

//랜턴
class lantern : public temple
{
public:
	lantern() {}
	~lantern() {}

	HRESULT init(const char* imageName, int idx, int idy);
	void render();
};

//캐논
class cannon : public temple
{
public:
	cannon() {}
	~cannon() {}

	void update();
	void setFrameX(int frameX);
	void render();
};

//문 
class door : public temple
{
public:
	door() {}
	~door() {}

	HRESULT init(const char* imageName, int idx, int idy);
	void render();
};