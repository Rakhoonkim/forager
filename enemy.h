#pragma once
#include "stdafx.h"
#include "enemy.h"
#include "enemyState.h"


class enemy
{
private:
	enemyState* _enemyState;

	tagObject _enemy;
public:
	enemy();
	~enemy();

	HRESULT init(ENEMY enemy,const char* imageName,int x, int y);
	void release();
	void update();
	void render();
	
	void setImage(const char* imageName) { _enemy.imageName = imageName; }
	void setAni(const char* imageName) { _enemy.ani = KEYANIMANAGER->findAnimation(imageName); _enemy.ani->start(); }



	tagObject* getEnemy() { return &_enemy; }
	
};

class slime : public enemy
{
public:
	slime();
	~slime();
};



