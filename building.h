#pragma once
#include "stdafx.h"

#define MAXFURNACELIST 9 
#define MAXFORGELIST 5
#define MAXSEWINGLIST 3

class building 
{
protected:
	tagObject _building;
	tagButton _furnaceButton[MAXFURNACELIST];
	tagButton _forgeButton[MAXFORGELIST];
	tagButton _sewingButton[MAXSEWINGLIST];

	tagButton _craftButton;
	tagButton _addButton[2];
	FURNACERECIPE _furnace;
	int _direction; // 현재 버튼을 어딜 가리키는지 
	float _timer;
	bool _craftPage;

	bool _isWork;
	int _itemCount;

	int _backPack;
	int _wallet;

	bool _isUse;
public:
	building();
	~building();

	virtual HRESULT init(BUILDING building, const char* imageName,int idx, int idy, bool farming = FALSE);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void EffectRender();
	virtual void buttonEffect();
	virtual void buttonClick();
	virtual void craftButton();
	virtual void isWorking();
	virtual void setHp(int maxHp, int hp);
	virtual void buttonInit();
	virtual void setAni() { _building.ani = KEYANIMANAGER->findAnimation("furnace"); }
	virtual bool getUsed() { return _isUse; }
	virtual void setUsed() { _isUse = false; }
	virtual tagObject* getBuilding() { return &_building; }
};

// furnace
class furnace : public building
{
public:
	furnace();
	~furnace();

	virtual void update();
	virtual void render();
	virtual void EffectRender();
	//제어함수 
	virtual void buttonEffect();
	virtual void buttonClick();
	virtual void buttonInit();
	virtual void isWorking();
	virtual void craftButton();  
};

// forge
class forge : public building
{
public:
	forge() {}
	~forge() {}

	virtual void update();
	virtual void render();
	virtual void EffectRender();
	//제어함수 
	virtual void buttonEffect();
	virtual void buttonClick();
};

// forge SEWING_STATION
class sewingStation : public building
{

public:
	sewingStation() {}
	~sewingStation() {}

	virtual void update();
	virtual void render();
	virtual void EffectRender();
	//제어함수 
	virtual void buttonEffect();
	virtual void buttonClick();
};

//FISHTRAP
class fishTrap : public building
{
public:
	fishTrap() {}
	~fishTrap() {}

	virtual void update();
	virtual void render();	
	virtual void EffectRender();

};

class bridge : public building
{
public:
	bridge() {}
	~bridge() {}

	virtual void update();
	virtual void render();
	virtual void EffectRender();
};