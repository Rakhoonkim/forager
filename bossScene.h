#pragma once
#include "stdafx.h"
#include "gameNode.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "templeManager.h"
#include "objectManager.h"

class bossScene : public gameNode
{
private:
	playerManager* _playerManager;
	enemyManager*   _enemyManager;
	templeManager* _templeManager;
	objectManager* _objectManager;

	tagBlind		_room1;

	bool	   _bossAttack; //������ ����

	RECT	   _exitScene;  //�� ������
public:
	bossScene();
	~bossScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void enterBossScene();
	void exitTemple();
};

