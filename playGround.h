#pragma once
#include "gameNode.h"
#include "mapToolScene.h"
#include "stageScene.h"
#include "mainMenuScene.h"
#include "bossScene.h"

class playGround : public gameNode
{
private:
	stageScene*		_stageScene;		// STAGE
	mapToolScene* _mapToolScene;		// MAP
	mainMenuScene* _mainMenuScene;		// MAINMENU
	bossScene* _bossScene;
public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

