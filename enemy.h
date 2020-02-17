#pragma once
#include "stdafx.h"
#include "enemy.h"
#include "enemyState.h"


class enemy
{
protected:
	enemyState* _enemyState;
	enemyIdle*     _enemyIdle;		//기본
	enemyMove*     _enemyMove;		//이동
	enemyAttack* _enemyAttack;		//공격

	tagObject _enemy;
	bool _StateTurn;
	bool _StateAttack;
public:
	enemy();
	~enemy();

	virtual HRESULT init(ENEMY enemy,const char* imageName,int x, int y);
	virtual void release();
	virtual void update();
	virtual void render();
	
	// 세팅 함수 
	virtual void setImage(const char* imageName) { _enemy.imageName = imageName; } 	//이미지 
	virtual void setAni(const char* imageName) { _enemy.ani = KEYANIMANAGER->findAnimation(imageName); _enemy.ani->start(); }
	virtual void setHp(int MaxHp, int hp) { _enemy.maxHp = MaxHp; _enemy.hp = hp; }  // 체력 

	tagObject* getEnemy() { return &_enemy; }
};

class slime : public enemy
{
public:
	slime();
	~slime();
};



