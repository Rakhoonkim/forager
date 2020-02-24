#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "buildManager.h"

class player;

class enemyManager : public gameNode
{
private:
	vector<enemy*>				_vEnemy;
	vector<enemy*>::iterator	_viEnemy;
	
	player* _player;
	bulletManager* _bulletManager;

	float _timer;   
public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();
	void imageSetting();		 // �̹��� ����

	void enemyRemove();			 // ���� ����

	void bossAttack();			 //���� ���� ���� �����ҿ��� 

	void setPlayer(player* player)	{ _player = player;}		 // SET PLAYER 
	void CreateEnemy(ENEMY enemyType, float x, float y);		 // CREATE ENEMY 

	vector<enemy*> getVEnemy()			  { return _vEnemy;}     // ENEMY Vector
	vector<enemy*>::iterator getViEnemy() { return _viEnemy;}	 // ENEMY Iterator

	bulletManager* getBulletManager() { return _bulletManager; }
};

