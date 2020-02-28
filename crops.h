#pragma once
#include "gameNode.h"

class crops 
{
protected:
	tagObject _crops;

public:
	crops();
	~crops();

	virtual	HRESULT init(OBJECT object,const char* imageName,int idx, int idy);		// 오브젝트
	virtual	HRESULT init(TREE tree, const char* imageName, int idx, int idy);		// 나무 

	virtual void release();
	virtual void update();
	virtual void render();
	//오브젝트 셋팅
	virtual void setHp(int maxHp, int hp);
	virtual void setSpeed(int speed)		{ _crops.speed = speed; }
	virtual void setFrameX(int frameX)		{ _crops.frameX = frameX; }
	virtual void setTime(float time)		{ _crops.time = time; }
	virtual void setIsClick()				{ _crops.isClick = true; }
	virtual void setTime()					{ _crops.time = TIMEMANAGER->getWorldTime(); }
	virtual void cropsHit(int damege)		{ _crops.hp -= damege; }
	virtual void setExpCrops(int exp)		{ _crops.exp = exp; }
	virtual void setCropsEffect(bool value)		{ _crops.isEffect = value; }
	virtual void setCropsIsHit(bool value) { _crops.isHit = value; }
	virtual bool getCropsIsHit() { return _crops.isHit; }
	virtual float getCropsY()			{ return _crops.y; }
	virtual tagObject* getCrops()		{ return &_crops; }
};

// 1장 이미지 
class imageCrops : public crops
{

public:
	imageCrops();
	~imageCrops();
	virtual void update();
	virtual void render();
};

// 3장 프레임
class frameCrops : public crops
{
public:
	frameCrops() {} 
	~frameCrops() {}
	virtual void update();
	virtual void render();
};

//여러장 있는 
class imageFrameCrops : public crops
{
public:
	imageFrameCrops() {}
	~imageFrameCrops() {}
	virtual void update();
	virtual void render();
};

// bush flower
class multiImageCrops : public crops
{
public:
	multiImageCrops() {}
	~multiImageCrops() {}
	
	virtual void update();
	virtual void render();
};
// 나무 
class treeCrops : public crops
{
public:
	treeCrops() {}
	~treeCrops() {}

	virtual void update();
	virtual void render();
};