#pragma once
#include "stdafx.h"

class building 
{
protected:
	tagObject _building;
	bool _isUse;
public:
	building();
	~building();

	virtual HRESULT init(BUILDING building, const char* imageName,int idx, int idy, bool farming = FALSE);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void setHp(int maxHp, int hp);

	virtual tagObject getBuilding() { return _building; }
};

// furnace
class furnace : public building
{
public:
	furnace() {}
	~furnace() {}

	virtual void update();
	virtual void render();
};

// forge
class forge : public building
{
public:
	forge() {}
	~forge() {}

	virtual void update();
	virtual void render();
};

// forge SEWING_STATION
class sewingStation : public building
{
public:
	sewingStation() {}
	~sewingStation() {}

	virtual void update();
	virtual void render();
};

//FISHTRAP
class fishTrap : public building
{
public:
	fishTrap() {}
	~fishTrap() {}

	virtual void update();
	virtual void render();
};

class bridge : public building
{
public:
	bridge() {}
	~bridge() {}

	virtual void update();
	virtual void render();
};