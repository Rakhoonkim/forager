#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "buildManager.h"
#include "alphaEffect.h"

class player;

class enemyManager : public gameNode
{
private:
	vector<enemy*>				_vEnemy;
	vector<enemy*>::iterator	_viEnemy;
	
	player* _player;
	bulletManager* _bulletManager;

	alphaEffect* _effect;

	//ActoEnemy
	float _slimeTimer;
	float _boarTimer;
	int _maxEnemy;

	bool _isBoss;
public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();
	void imageSetting();		 // 이미지 셋팅

	void enemyRemove();			 // 몬스터 삭제

	void setPlayer(player* player)	{ _player = player;}		 // SET PLAYER 
	void CreateEnemy(ENEMY enemyType, int idx, int idy);		 // CREATE ENEMY 

	vector<enemy*> getVEnemy()			  { return _vEnemy;}     // ENEMY Vector
	vector<enemy*>::iterator getViEnemy() { return _viEnemy;}	 // ENEMY Iterator

	bulletManager* getBulletManager() { return _bulletManager; }

	void AutoEnemyCreate();
	void AutoEnemySet(bool value) { _isBoss = value; }
	bool AutoEnemyget() { return _isBoss; }
	void BossAttack();
};

