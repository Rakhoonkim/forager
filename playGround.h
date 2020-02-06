#pragma once
#include "gameNode.h"
#include "mapToolScene.h"
#include "stageScene.h"

class playGround : public gameNode
{
private:
	stageScene*		_stageScene;
	mapToolScene* _mapToolScene;
		

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	playGround();
	~playGround();
};

