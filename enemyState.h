#pragma once
#include "stdafx.h"

class enemyStateManager;

class enemyState
{
protected:
	tagObject* _enemy;

	enemyStateManager* _enemyStateManager;
public:
	enemyState();
	~enemyState();
	virtual HRESULT init();
	virtual HRESULT init(tagObject* enemy);
	virtual void update();
	virtual void release();
	virtual void render();

	virtual void ChangeImage();
	virtual void Enter();


	virtual void direction(); // 방향값 정의
	virtual void Jump();

	//enemyStateManagerLink연결
	virtual void Set_enemyStateManager(enemyStateManager* enemyStateManager) { _enemyStateManager = enemyStateManager; }
};



class enemyIdle : public enemyState
{
public:
	enemyIdle(enemyStateManager* enemyStateManager, tagObject* enemy) { this->Set_enemyStateManager(enemyStateManager); _enemy = enemy; }
	~enemyIdle() {}

	virtual void Enter();
	virtual void update();
	virtual void ChangeImage();
};


class enemyMove : public enemyState
{
public:
	enemyMove(enemyStateManager* enemyStateManager, tagObject* enemy) { this->Set_enemyStateManager(enemyStateManager); _enemy = enemy; }
	~enemyMove() {}
	virtual void Enter();
	virtual void update();
	virtual void ChangeImage();
};

class enemyAttack : public enemyState
{
public:
	enemyAttack(enemyStateManager* enemyStateManager, tagObject* enemy) { this->Set_enemyStateManager(enemyStateManager); _enemy = enemy; }
	~enemyAttack() {}

	virtual void Enter();
	virtual void update();
	virtual void ChangeImage();
};

class enemyJump : public enemyState
{
private:
	DIRECTION _direction;
	float _jumpPower;
	float _gravity;
public:
	enemyJump(enemyStateManager* enemyStateManager, tagObject* enemy) { this->Set_enemyStateManager(enemyStateManager); _enemy = enemy; }
	~enemyJump() {}

	virtual void Enter();
	virtual void update();
	virtual void ChangeImage();
	virtual void direction();
	virtual void JumpInit();
	virtual void Jump();
};