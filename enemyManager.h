#pragma once
#include "gameNode.h"
#include "enemy.h"

class player;

class enemyManager : public gameNode
{
private:
	vector<enemy*>				_vEnemy;
	vector<enemy*>::iterator	_viEnemy;
	
	float _timer;   

	enemy* _enemy;
	player* _player;
public:
	enemyManager();
	~enemyManager();
	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();

	enemy* getEnemy() { return _enemy; }
	void setPlayer(player* player) { _player = player;}
};

