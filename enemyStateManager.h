#pragma once
#include "stdafx.h"
#include "enemyState.h"

class enemyStateManager
{
public:
	typedef map<string, enemyState*>			mapStateList;
	typedef map<string, enemyState*>::iterator	mapStateIter;

private:
	//static enemyState* _currentState;
	enemyState* _currentState;

	mapStateList			_mState;
	mapStateIter		   _miState;

public:
	enemyStateManager();
	~enemyStateManager();

	HRESULT init();
	void release();
	void update();
	void render();

	enemyState* addState(string stateName, enemyState* state);
	enemyState* getState() { return	_currentState;}
	HRESULT chanageState(string stateName);
};

