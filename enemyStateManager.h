#pragma once
#include "stdafx.h"
#include "enemyState.h"

class enemyStateManager
{
public:
	typedef map<string, enemyState*>			mapStateList;
	typedef map<string, enemyState*>::iterator	mapStateIter;

private:
	enemyState*		  _currentState;  //애너미가 보여지는 현재상태

	mapStateList			_mState; //MAP
	mapStateIter		   _miState; //MAP iter

public:
	enemyStateManager();
	~enemyStateManager();

	HRESULT init();
	void release();
	void update();
	void render();

	enemyState* addState(string stateName, enemyState* state);

	HRESULT chanageState(string stateName);

	enemyState* getState()										 { return	_currentState;}
};

