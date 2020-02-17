#pragma once
#include "stdafx.h"
#include "enemy.h"
#include "enemyState.h"


class enemy
{
protected:
	enemyState* _enemyState;
	enemyIdle*     _enemyIdle;		//�⺻
	enemyMove*     _enemyMove;		//�̵�
	enemyAttack* _enemyAttack;		//����

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
	
	// ���� �Լ� 
	virtual void setImage(const char* imageName) { _enemy.imageName = imageName; } 	//�̹��� 
	virtual void setAni(const char* imageName) { _enemy.ani = KEYANIMANAGER->findAnimation(imageName); _enemy.ani->start(); }
	virtual void setHp(int MaxHp, int hp) { _enemy.maxHp = MaxHp; _enemy.hp = hp; }  // ü�� 

	tagObject* getEnemy() { return &_enemy; }
};

class slime : public enemy
{
public:
	slime();
	~slime();
};



