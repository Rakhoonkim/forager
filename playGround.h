#pragma once
#include "gameNode.h"
#include "mapToolScene.h"

class playGround : public gameNode
{
private:
	mapToolScene* _mapToolScene;
	

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	playGround();
	~playGround();
};

