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

	//설정자
	virtual void setHp(int maxHp, int hp);	// 체력 설정
	virtual void setTime()					{ _crops.time = TIMEMANAGER->getWorldTime(); } //시간설정
	virtual void setSpeed(int speed)		{ _crops.speed = speed; }					   //성장속도 
	virtual void setFrameX(int frameX)		{ _crops.frameX = frameX; }					   //그림 
	virtual void setTime(float time)		{ _crops.time = time; }						   //시간
	virtual void setIsClick()				{ _crops.isClick = true; }					   //수확가능
	virtual void setExpCrops(int exp)		{ _crops.exp = exp; }						   //경험치 설정
	virtual void setCropsEffect(bool value)	{ _crops.isEffect = value; }				   //효과
	virtual void setCropsHit(int damege)	{ _crops.hp -= damege; }					   //데미지
	virtual void setCropsIsHit(bool value)  { _crops.isHit = value; }					   //피격모션
	//접근자
	virtual bool getCropsIsHit()		{ return _crops.isHit; }
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