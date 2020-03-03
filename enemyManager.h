#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "buildManager.h"
#include "alphaEffect.h"

class player;

class enemyManager : public gameNode
{
private:
	vector<enemy*>				 _vEnemy;
	vector<enemy*>::iterator	_viEnemy;
	
	player*						 _player;
	bulletManager*		  _bulletManager;

	alphaEffect*				 _effect;

	//ENEMY 자동 소환 변수
	float	 _slimeTimer;
	float	  _boarTimer;
	int		   _maxEnemy;

	bool		 _isBoss;   // 보스가 있는지 없는지 확인하는 
public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();		 // 이미지 세팅

	void enemyRemove();			 // 몬스터 삭제

	void setPlayer(player* player)			{ _player = player;} // PLAYER 

	void CreateEnemy(ENEMY enemyType, int idx, int idy);		 // CREATE ENEMY 

	vector<enemy*> getVEnemy()				{ return _vEnemy;}   // ENEMY Vector
	vector<enemy*>::iterator getViEnemy()	{ return _viEnemy;}	 // ENEMY Iterator
	bulletManager* getBulletManager()		{ return _bulletManager; }

	void AutoEnemyCreate();         // 몬스터 자동 소환
	void BossAttack();				// 보스 공격

	void AutoEnemySet(bool value)	{ _isBoss = value; } // 스테이지 씬에서 사용함
	bool AutoEnemyget()			    { return _isBoss; }
};

