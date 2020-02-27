#pragma once
#include "stdafx.h"
#include "gameNode.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "templeManager.h"

class bossScene : public gameNode
{
private:
	playerManager* _playerManager;
	enemyManager* _enemyManager;
	templeManager* _templeManager;

	tagBlind _room1;

	bool temp;
public:
	bossScene();
	~bossScene();

	HRESULT init();
	void release();
	void update();
	void render();

};

