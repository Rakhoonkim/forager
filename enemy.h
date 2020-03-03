#pragma once
#include "stdafx.h"
#include "enemy.h"
#include "enemyStateManager.h"
#include "bulletManager.h"

class player;

class enemy
{
protected:
	enemyStateManager*  _enemyState;    //ENEMY STATE
	bulletManager*	 _bulletManager;	//BULLET MANAGER
	tagObject				 _enemy;	//ENEMY
	tagPlayer*				_player;	//PLAYER

	bool _bossAttack;			// 보스 공격
	bool _isJump;               // 슬라임 점프

	DIRECTION _previousDirection;  // 방향을 확인
public:
	enemy();
	~enemy();

	virtual HRESULT init(ENEMY enemy,const char* imageName,int x, int y);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void IndexUpdate();

	virtual void Set_PlayerLink(tagPlayer* player)	 { _player = player; }				     	//PLAYER
	virtual void Set_skullEnemyXY()					 { _enemy.x += 30;_enemy.y += 30;}		    //ENEMY XY
	virtual void setImage(const char* imageName)	 { _enemy.imageName = imageName; }			//이미지 
	virtual void setHp(int MaxHp, int hp)			 { _enemy.maxHp = MaxHp; _enemy.hp = hp; }  //체력 
	virtual void setEnemyHit(int damege)			 { _enemy.hp -= damege; }					//데미지
	virtual void SetBossAttack(bool value)		     { _enemy.isAttack = value; }			    //공격
	virtual void setAni(const char* imageName)		 { _enemy.ani = KEYANIMANAGER->findAnimation(imageName); _enemy.ani->start(); }  //이미지 셋팅 및 시작
	
	virtual void setEnemyBullet(bulletManager* bulletManager) { _bulletManager = bulletManager; } //링크 셋팅

	virtual int	   getEnemyExp()				{ return _enemy.exp; }		 //경험치
	virtual bool   getBossAttack()				{ return _enemy.isAttack; }  //보스공격인지 아닌지
	bulletManager* getBulletManager()			{ return _bulletManager; }   //총알 매니저
	tagObject*	   getEnemy()					{ return &_enemy; }			 // enemy 참조 

};

//슬라임
class slime : public enemy
{
public:
	slime();
	~slime();

	void update();
};

//수퇘지
class boar : public enemy
{
public:
	boar();
	~boar();

	void update();
};

//데몬
class demon : public enemy
{
public:
	demon();
	~demon();

	void update();
};

//스컬
class skull : public enemy
{
private:
	float firetime;
public:
	skull();
	~skull();

	void update();
};

//보스
class demonBoss : public enemy
{
public:
	demonBoss();
	~demonBoss();

	void update();
};