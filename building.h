#pragma once
#include "stdafx.h"

class building 
{
protected:
	tagObject _building;

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

class imageBuilding : public building
{
public:
	imageBuilding() {}
	~imageBuilding() {}
	
	virtual void update();
	virtual void render();
};

class frameBuilding : public building
{
public:
	frameBuilding() {}
	~frameBuilding() {}

	virtual void update();
	virtual void render();
};

