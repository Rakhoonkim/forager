#pragma once
#include "stdafx.h"
#include "enemy.h"
#include "enemyStateManager.h"
#include "bulletManager.h"

class player;

class enemy
{
protected:
	enemyStateManager* _enemyState;
	bulletManager*	 _bulletManager;
	tagObject	_enemy;		// enemy
	tagPlayer* _player;		// player

	bool _bossAttack;
	bool _isJump;
	//임시 
	DIRECTION _previousDirection;
	

public:
	enemy();
	~enemy();

	virtual HRESULT init(ENEMY enemy,const char* imageName,int x, int y);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void IndexUpdate();

	tagObject* getEnemy()					{ return &_enemy; }		 // enemy 참조 

	void Set_PlayerLink(tagPlayer* player)  { _player = player; }

	void set_skullEnemyXY() { _enemy.x += 30;_enemy.y += 30;}
	// 세팅 함수 
	virtual void setImage(const char* imageName)	 { _enemy.imageName = imageName; } 			//이미지 
	virtual void setHp(int MaxHp, int hp)			 { _enemy.maxHp = MaxHp; _enemy.hp = hp; }  // 체력 
	virtual void setAni(const char* imageName)		 { _enemy.ani = KEYANIMANAGER->findAnimation(imageName); _enemy.ani->start(); }
	virtual void enemyHit(int damege)				 { _enemy.hp -= damege; }
	
	virtual bool getBossAttack() { return _enemy.isAttack; }
	virtual void SetBossAttack(bool value) { _enemy.isAttack = value; }
	bulletManager* getBulletManager() {	return _bulletManager;	}

	virtual void setEnemyBullet(bulletManager* bulletManager) { _bulletManager = bulletManager; }
	
};

class slime : public enemy
{
public:
	slime();
	~slime();
	void update();
};

class boar : public enemy
{
public:
	boar();
	~boar();
	void update();
};

class demon : public enemy
{
public:
	demon();
	~demon();
	void update();
};

class skull : public enemy
{
private:
	float firetime;
public:
	skull();
	~skull();

	void update();
};

class demonBoss : public enemy
{
public:
	demonBoss();
	~demonBoss();

	void update();

};