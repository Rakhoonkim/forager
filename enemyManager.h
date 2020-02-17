#pragma once
#include "gameNode.h"
#include "enemy.h"

class enemyManager : public gameNode
{
private:
	vector<enemy*>				_vEnemy;
	vector<enemy*>::iterator	_viEnemy;
	
	enemy* _enemy;

public:
	enemyManager();
	~enemyManager();
	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();
};

