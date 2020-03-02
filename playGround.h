#pragma once
#include "gameNode.h"
#include "mainMenuScene.h"
#include "mapToolScene.h"
#include "stageScene.h"
#include "bossScene.h"

class playGround : public gameNode
{
private:
	mainMenuScene*	_mainMenuScene;		// MAINMENU
	mapToolScene*	 _mapToolScene;		// MAPTOOL
	stageScene*	       _stageScene;		// STAGE
	bossScene*			_bossScene;		// BOSS

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

