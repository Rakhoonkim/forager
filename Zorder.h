#pragma once
#include "stdafx.h"
#include "singletonBase.h"

class cropsManager;
class playerManager;
class buildManager;
class enemyManager;
class puzzleManager;

class crops;
class building;
class enemy;
class player;
class puzzle;

enum class STAGEOBJECT
{
	CROPS,
	PLAYER,
	ENEMY,
	BUILDING,
	PUZZLE,
};

struct ZorderStageClass
{
	player* player;
	crops* crops;
	building* build;
	enemy* enemy;
	puzzle* puzzle;
};


struct ZorderObject
{
	ZorderStageClass* zOrder;
	float* y;

	ZorderObject(float* y, ZorderStageClass* object)
	{
		this->y = y;
		this->zOrder = object;
	};
	ZorderObject() { ; }
};

class Zorder : public singletonBase<Zorder>
{

private:
	vector<ZorderObject*> _vZOrder;

public:
	Zorder();
	~Zorder();
	HRESULT init();
	void release();
	void update();
	void render();

	void addZorder(STAGEOBJECT obj, ZorderStageClass* object);
	void addZorder(STAGEOBJECT obj, player* player, crops* crop,building* build,enemy* enemy,puzzle* puzzle);

	vector<ZorderObject*> ZOrderUpdate(vector<ZorderObject*> num);

	void removeObject();

	vector<ZorderObject*> getZorder() { return _vZOrder; }
	void setZorder(vector<ZorderObject*> zorder) { _vZOrder = zorder; }
};

