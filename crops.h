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
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setHp(int maxHp, int hp);
	virtual void cropsHit(int damege) { _crops.hp -= damege; }
	virtual tagObject* getCrops() { return &_crops; }
};

class imageCrops : public crops
{

public:
	imageCrops() {}
	~imageCrops() {}
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




