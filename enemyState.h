#pragma once
#include "stdafx.h"

class enemyState
{
protected:
	tagObject* _enemy;

	bool _isMove;
public:
	enemyState();
	~enemyState();

	virtual HRESULT init(tagObject* enemy);
	virtual void update();
	virtual void release();
	virtual void render();

	virtual void IdleImage();
	virtual void MoveImage();
	virtual void AttackImage();
	virtual void JumpImage();
};



class enemyIdle : public enemyState
{
public:
	enemyIdle(tagObject* enemy) { _enemy = enemy; }
	~enemyIdle() {}
	virtual void update();
};


class enemyMove : public enemyState
{
public:
	enemyMove(tagObject* enemy) { _enemy = enemy; }
	~enemyMove() {}
	virtual void update();
};

class enemyAttack : public enemyState
{
public:
	enemyAttack(tagObject* enemy) { _enemy = enemy; }
	~enemyAttack() {}
	virtual void update();
};

