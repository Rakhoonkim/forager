#pragma once
#include "gameNode.h"

class crops 
{
protected:
	tagObject _crops;

public:
	crops();
	~crops();

	virtual	HRESULT init(OBJECT object,const char* imageName,int idx, int idy);		// ������Ʈ
	virtual	HRESULT init(TREE tree, const char* imageName, int idx, int idy);		// ���� 

	virtual void release();
	virtual void update();
	virtual void render();
	//������Ʈ ����
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

// 1�� �̹��� 
class imageCrops : public crops
{

public:
	imageCrops();
	~imageCrops();
	virtual void update();
	virtual void render();
};

// 3�� ������
class frameCrops : public crops
{
public:
	frameCrops() {} 
	~frameCrops() {}
	virtual void update();
	virtual void render();
};

//������ �ִ� 
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
// ���� 
class treeCrops : public crops
{
public:
	treeCrops() {}
	~treeCrops() {}

	virtual void update();
	virtual void render();
};