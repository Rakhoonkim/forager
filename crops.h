#pragma once
#include "gameNode.h"

class crops 
{
protected:
	tagObject _crops;

public:
	crops();
	~crops();

	virtual	HRESULT init(OBJECT object,const char* imageName,int idx, int idy);
	virtual	HRESULT init(TREE tree, const char* imageName, int idx, int idy);

	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setHp(int maxHp, int hp);
	virtual void setSpeed(int speed)		{ _crops.speed = speed; }
	virtual void setFrameX(int frameX)		{ _crops.frameX = frameX; }
	virtual void setTime(float time)		{ _crops.time = time; }
	virtual void setIsClick()				{ _crops.isClick = true; }
	virtual void setTime()					{ _crops.time = TIMEMANAGER->getWorldTime(); }

	virtual void cropsHit(int damege)		{ _crops.hp -= damege; }
	virtual tagObject* getCrops()		{ return &_crops; }
};

class imageCrops : public crops
{

public:
	imageCrops();
	~imageCrops();
	virtual void update();
	virtual void render();
};

class frameCrops : public crops
{
public:
	frameCrops() {} 
	~frameCrops() {}
	virtual void update();
	virtual void render();
};

class imageFrameCrops : public crops
{
public:
	imageFrameCrops() {}
	~imageFrameCrops() {}

	virtual void update();
	virtual void render();
};

class treeCrops : public crops
{
public:
	treeCrops() {}
	~treeCrops() {}

	virtual void update();
	virtual void render();
};