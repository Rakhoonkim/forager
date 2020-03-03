#pragma once
#include "stdafx.h"

class enemyStateManager;
class player;

class enemyState
{
protected:
	enemyStateManager* _enemyStateManager;

	tagObject* _enemy;
	tagPlayer* _player;
public:
	enemyState();
	~enemyState();
	virtual HRESULT init();
	virtual HRESULT init(tagObject* enemy);
	virtual void update();
	virtual void release();
	virtual void render();

	virtual void ChangeImage();		// 이미지 변환
	virtual void Enter();			// 상태 들어갈 시 적용해야 하는 

	virtual void direction();		// 방향값 정의
	virtual void Jump();			// 슬라임 : 점프

	//enemyStateManagerLink연결
	virtual void Set_enemyStateManager(enemyStateManager* enemyStateManager) { _enemyStateManager = enemyStateManager; }
	virtual void Set_PlayerLink(tagPlayer* player) { _player = player; }
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
	float _move;			 // 스컬
	int _movePattern;        // 스컬
	float _isAttackTime;     // Boss
public:
	enemyMove(enemyStateManager* enemyStateManager, tagObject* enemy);
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
	virtual void render();
};

class enemyJump : public enemyState
{
private:
	DIRECTION _direction;	// 슬라임 : 방향값

	float _jumpPower;		//점프 파워
	float _gravity;			//중력	

	bool _isJump;		    //점프중
	bool _isMove;			//이동
public:
	enemyJump(enemyStateManager* enemyStateManager, tagObject* enemy); //{ this->Set_enemyStateManager(enemyStateManager); _enemy = enemy; }
	~enemyJump() {}

	virtual void Enter();
	virtual void update();
	virtual void ChangeImage();
	virtual void direction();
	virtual void Jumping();
};